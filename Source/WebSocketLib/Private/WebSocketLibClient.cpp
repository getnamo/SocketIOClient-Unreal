// Copyright 2026-current Getnamo. All Rights Reserved

#include "WebSocketLibClient.h"
#include "WebSocketLibIncludes.h"
#include "WebSocketLibInternal.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Misc/ScopeLock.h"
#include "Modules/ModuleManager.h"
#include "SslModule.h"
#include "Interfaces/ISslCertificateManager.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <type_traits>
#include <vector>

DEFINE_LOG_CATEGORY(LogWebSocketLib);

namespace WebSocketLib
{
	/**
	 * asio_tls_client, but waits at most a second for the server's TLS close_notify after the close handshake.
	 * Some servers never send one, and the close callback only runs once the socket is shut down (default 5s).
	 */
	struct FTlsClientConfig : public websocketpp::config::asio_tls_client
	{
		typedef FTlsClientConfig type;
		typedef websocketpp::config::asio_tls_client base;

		struct transport_config : public base::transport_config
		{
			static const long timeout_socket_shutdown = 1000;
		};

		typedef websocketpp::transport::asio::endpoint<transport_config> transport_type;
	};

	typedef websocketpp::client<websocketpp::config::asio_client> FPlainClient;
	typedef websocketpp::client<FTlsClientConfig> FTlsClient;

	//Close frames carry at most 123 bytes of reason
	static const size_t MaxCloseReasonBytes = 123;

	static std::string ToStd(const FString& In)
	{
		FTCHARToUTF8 Converted(*In);
		return std::string(Converted.Get(), Converted.Length());
	}

	static FString ToFString(const std::string& In)
	{
		return FString::ConstructFromPtrSize(reinterpret_cast<const UTF8CHAR*>(In.data()), (int32)In.size());
	}

	/** The callbacks of one connection. Disable() waits for a running callback, none runs after it returns. */
	class FCallbackHolder
	{
	public:
		explicit FCallbackHolder(const FWebSocketLibCallbacks& InCallbacks)
			: Callbacks(InCallbacks)
		{
		}

		void Disable()
		{
			FScopeLock Guard(&Lock);
			bEnabled = false;
		}

		template<typename MemberType, typename... ArgTypes>
		void Call(MemberType FWebSocketLibCallbacks::* Member, ArgTypes&&... Args)
		{
			//FCriticalSection is recursive, a callback may reconnect or destroy its own client
			FScopeLock Guard(&Lock);
			const MemberType& Callback = Callbacks.*Member;
			if (bEnabled && Callback)
			{
				Callback(Forward<ArgTypes>(Args)...);
			}
		}

	private:
		FWebSocketLibCallbacks Callbacks;
		FCriticalSection Lock;
		bool bEnabled = true;
	};

	typedef TSharedRef<FCallbackHolder, ESPMode::ThreadSafe> FCallbackHolderRef;

	class IConnection
	{
	public:
		virtual ~IConnection() = default;

		virtual bool Start(const FWebSocketLibConnectParams& Params, FString& OutError) = 0;
		virtual void Close(uint16 Code, const std::string& Reason) = 0;
		virtual bool Send(std::shared_ptr<const std::string> Payload, bool bBinary) = 0;

		/** False on timeout */
		virtual bool WaitUntilFinished(float TimeoutSeconds) = 0;

		/** Stop the network thread without closing gracefully */
		virtual void Stop() = 0;

		virtual bool IsOpen() const = 0;
		virtual bool IsNetworkThread() const = 0;
		virtual void DisableCallbacks() = 0;
	};

	/** Every started connection, for module shutdown */
	struct FConnectionRegistry
	{
		std::mutex Mutex;
		std::vector<std::weak_ptr<IConnection>> Connections;
		std::atomic<int32> RunningThreads{ 0 };

		void Add(const std::shared_ptr<IConnection>& Connection)
		{
			std::lock_guard<std::mutex> Guard(Mutex);
			Connections.erase(std::remove_if(Connections.begin(), Connections.end(),
				[](const std::weak_ptr<IConnection>& Weak) { return Weak.expired(); }), Connections.end());
			Connections.push_back(Connection);
		}
	};

	static FConnectionRegistry& GetRegistry()
	{
		static FConnectionRegistry Registry;
		return Registry;
	}

	/** Add PEM certificates as trusted roots, returns how many were added */
	static int32 AddPemCertificates(SSL_CTX* Context, const std::string& Pem)
	{
		if (Pem.empty())
		{
			return 0;
		}

		int32 Added = 0;
		BIO* Bio = BIO_new_mem_buf(Pem.data(), (int)Pem.size());
		X509_STORE* Store = SSL_CTX_get_cert_store(Context);
		while (X509* Certificate = PEM_read_bio_X509(Bio, nullptr, nullptr, nullptr))
		{
			if (X509_STORE_add_cert(Store, Certificate) == 1)
			{
				Added++;
			}
			X509_free(Certificate);
		}
		BIO_free(Bio);

		//Reading until the end of the PEM leaves an error on the queue
		ERR_clear_error();
		return Added;
	}

	/** wss certificate check: the chain against the trusted roots, then the server's certificate against the host and the engine's pinning */
	struct FCertificateVerifier
	{
		asio_sockio::ssl::rfc2818_verification HostCheck;
		std::string Host;
		const ISslCertificateManager* CertificateManager;
		std::string* OutError;

		bool operator()(bool bPreverified, asio_sockio::ssl::verify_context& Context)
		{
			X509_STORE_CTX* Store = Context.native_handle();
			if (!bPreverified)
			{
				if (OutError->empty())
				{
					*OutError = X509_verify_cert_error_string(X509_STORE_CTX_get_error(Store));
				}
				return false;
			}

			//The rest only applies to the server's own certificate
			if (X509_STORE_CTX_get_error_depth(Store) > 0)
			{
				return true;
			}

			if (!HostCheck(bPreverified, Context))
			{
				*OutError = "certificate does not match host " + Host;
				return false;
			}

			if (CertificateManager && !CertificateManager->VerifySslCertificates(Store, ToFString(Host)))
			{
				*OutError = "certificate rejected by the engine's certificate pinning";
				return false;
			}
			return true;
		}
	};

	template<typename ClientType>
	class TConnection : public IConnection, public std::enable_shared_from_this<TConnection<ClientType>>
	{
		static constexpr bool bIsTls = std::is_same<ClientType, FTlsClient>::value;

		typedef typename ClientType::connection_ptr FConnectionPtr;
		typedef typename ClientType::message_ptr FMessagePtr;

		enum class EState : uint8
		{
			Idle,
			Connecting,
			Open,
			Closed
		};

	public:
		TConnection(const FCallbackHolderRef& InCallbacks, const ISslCertificateManager* InCertificateManager)
			: Callbacks(InCallbacks)
			, CertificateManager(InCertificateManager)
		{
		}

		virtual bool Start(const FWebSocketLibConnectParams& Params, FString& OutError) override
		{
			bVerifyCertificate = Params.bVerifyTLSCertificate;
			AdditionalCACertificates = ToStd(Params.AdditionalCACertificatesPEM);

			websocketpp::lib::error_code Error;

			//No access log. Transport errors only show up in the error log, keep it for readable failures.
			Endpoint.clear_access_channels(websocketpp::log::alevel::all);
			Endpoint.set_error_channels(websocketpp::log::elevel::info | websocketpp::log::elevel::warn |
				websocketpp::log::elevel::rerror | websocketpp::log::elevel::fatal);
			Endpoint.get_elog().set_ostream(&ErrorLog);

			Endpoint.init_asio(Error);
			if (Error)
			{
				OutError = FString::Printf(TEXT("Could not initialize the network: %s"), *ToFString(Error.message()));
				return false;
			}

			Endpoint.set_max_message_size((size_t)FMath::Max<int64>(Params.MaxMessageSizeBytes, 1));

			//After the close handshake the client leaves the socket for the server to close, some servers never do.
			//This timer bounds that wait (and waiting for the close reply), websocketpp's default is 5s.
			Endpoint.set_close_handshake_timeout(2000);
			Endpoint.set_open_handler([this](websocketpp::connection_hdl Hdl) { HandleOpen(Hdl); });
			Endpoint.set_fail_handler([this](websocketpp::connection_hdl Hdl) { HandleFail(Hdl); });
			Endpoint.set_close_handler([this](websocketpp::connection_hdl Hdl) { HandleClose(Hdl); });
			Endpoint.set_message_handler([this](websocketpp::connection_hdl Hdl, FMessagePtr Message) { HandleMessage(Message); });
			if constexpr (bIsTls)
			{
				Endpoint.set_tls_init_handler([this](websocketpp::connection_hdl) { return MakeTlsContext(); });
			}

			//get_connection already runs the tls init handler, which needs the host
			const std::string Url = ToStd(Params.Url);
			Host = websocketpp::uri(Url).get_host();

			FConnectionPtr Connection = Endpoint.get_connection(Url, Error);
			if (Error)
			{
				OutError = FString::Printf(TEXT("Invalid url '%s': %s"), *Params.Url, *ToFString(Error.message()));
				return false;
			}

			for (const TPair<FString, FString>& Header : Params.Headers)
			{
				Connection->replace_header(ToStd(Header.Key), ToStd(Header.Value));
			}
			for (const FString& Protocol : Params.Protocols)
			{
				Connection->add_subprotocol(ToStd(Protocol), Error);
				if (Error)
				{
					OutError = FString::Printf(TEXT("Invalid subprotocol '%s': %s"), *Protocol, *ToFString(Error.message()));
					return false;
				}
			}

			Handle = Connection->get_handle();
			Endpoint.connect(Connection);
			State = EState::Connecting;

			//The thread holds this connection until its run loop ends, so it can finish closing on its own
			FConnectionRegistry& Registry = GetRegistry();
			Registry.Add(this->shared_from_this());
			Registry.RunningThreads++;
			std::thread([Self = this->shared_from_this()]() mutable
			{
				Self->RunLoop();
				Self.reset();
				GetRegistry().RunningThreads--;
			}).detach();

			return true;
		}

		virtual void Close(uint16 Code, const std::string& Reason) override
		{
			{
				std::lock_guard<std::mutex> Guard(CloseMutex);
				if (bCloseRequested)
				{
					return;
				}
				bCloseRequested = true;
				CloseCode = Code;
				CloseReason = Reason.substr(0, MaxCloseReasonBytes);
			}

			Endpoint.get_io_service().post([this]()
			{
				websocketpp::lib::error_code Error;
				FConnectionPtr Connection = Endpoint.get_con_from_hdl(Handle, Error);
				if (!Connection)
				{
					return;
				}

				const websocketpp::session::state::value SessionState = Connection->get_state();
				if (SessionState == websocketpp::session::state::open)
				{
					Connection->close(CloseCode, CloseReason, Error);
					if (Error)
					{
						UE_LOG(LogWebSocketLib, Warning, TEXT("Close with code %d failed (%s), closing with 1000"), CloseCode, *ToFString(Error.message()));
						Connection->close(websocketpp::close::status::normal, std::string(), Error);
					}
				}
				else if (SessionState == websocketpp::session::state::connecting)
				{
					//Not open yet: report the close and drop everything, this endpoint only serves this connection
					State = EState::Closed;
					Callbacks->Call(&FWebSocketLibCallbacks::OnClose, (int32)CloseCode, ToFString(CloseReason), false);
					Endpoint.stop();
				}
			});
		}

		virtual bool Send(std::shared_ptr<const std::string> Payload, bool bBinary) override
		{
			if (State != EState::Open)
			{
				return false;
			}

			Endpoint.get_io_service().post([this, Payload, bBinary]()
			{
				websocketpp::lib::error_code Error;
				Endpoint.send(Handle, *Payload, bBinary ? websocketpp::frame::opcode::binary : websocketpp::frame::opcode::text, Error);
				if (Error)
				{
					UE_LOG(LogWebSocketLib, Warning, TEXT("Send failed: %s"), *ToFString(Error.message()));
				}
			});
			return true;
		}

		virtual bool WaitUntilFinished(float TimeoutSeconds) override
		{
			if (IsNetworkThread())
			{
				return false;
			}
			std::unique_lock<std::mutex> Lock(FinishedMutex);
			return FinishedCondition.wait_for(Lock, std::chrono::duration<float>(TimeoutSeconds), [this]() { return bFinished; });
		}

		virtual void Stop() override
		{
			Endpoint.stop();
		}

		virtual bool IsOpen() const override
		{
			return State == EState::Open;
		}

		virtual bool IsNetworkThread() const override
		{
			return NetworkThreadId.load() == std::this_thread::get_id();
		}

		virtual void DisableCallbacks() override
		{
			Callbacks->Disable();
		}

	private:
		void RunLoop()
		{
			NetworkThreadId = std::this_thread::get_id();
			try
			{
				Endpoint.run();
			}
			catch (const std::exception& Exception)
			{
				UE_LOG(LogWebSocketLib, Error, TEXT("Network thread stopped on an exception: %s"), *ToFString(Exception.what()));
			}
			State = EState::Closed;

			{
				std::lock_guard<std::mutex> Guard(FinishedMutex);
				bFinished = true;
			}
			FinishedCondition.notify_all();
		}

		bool IsCloseRequested()
		{
			std::lock_guard<std::mutex> Guard(CloseMutex);
			return bCloseRequested;
		}

		void HandleOpen(websocketpp::connection_hdl Hdl)
		{
			State = EState::Open;
			TakeLoggedError();

			//Closed while connecting, the pending close reports it
			if (IsCloseRequested())
			{
				return;
			}

			//websocketpp only fills get_subprotocol() on the server side, read the client's from the response
			websocketpp::lib::error_code Error;
			FConnectionPtr Connection = Endpoint.get_con_from_hdl(Hdl, Error);
			const FString Protocol = Connection ? ToFString(Connection->get_response_header("Sec-WebSocket-Protocol")) : FString();
			Callbacks->Call(&FWebSocketLibCallbacks::OnOpen, Protocol);
		}

		void HandleFail(websocketpp::connection_hdl Hdl)
		{
			State = EState::Closed;

			{
				std::unique_lock<std::mutex> Guard(CloseMutex);
				if (bCloseRequested)
				{
					//We asked for the close before it opened, report what was asked for
					const int32 Code = CloseCode;
					const FString Reason = ToFString(CloseReason);
					Guard.unlock();
					Callbacks->Call(&FWebSocketLibCallbacks::OnClose, Code, Reason, false);
					return;
				}
			}

			websocketpp::lib::error_code Error;
			FConnectionPtr Connection = Endpoint.get_con_from_hdl(Hdl, Error);

			if (!Connection)
			{
				Callbacks->Call(&FWebSocketLibCallbacks::OnFail, FString(TEXT("Connection failed")), 0);
				return;
			}

			const websocketpp::lib::error_code FailCode = Connection->get_ec();
			FString Message = ToFString(FailCode.message());
			int32 HttpStatus = 0;
			const int32 ResponseCode = (int32)Connection->get_response_code();
			if (ResponseCode != 0 && ResponseCode != 101)
			{
				HttpStatus = ResponseCode;
				Message += FString::Printf(TEXT(" (HTTP %d %s)"), ResponseCode, *ToFString(Connection->get_response_msg()));
			}

			//System errors already say what happened. websocketpp's own codes are generic, the detail is in the log.
			const FString LoggedError = TakeLoggedError();
			if (!VerifyError.empty())
			{
				Message += TEXT(": ") + ToFString(VerifyError);
			}
			else if (HttpStatus == 0 && std::string(FailCode.category().name()).rfind("websocketpp", 0) == 0 && !LoggedError.IsEmpty())
			{
				Message += TEXT(": ") + LoggedError;
			}
			Callbacks->Call(&FWebSocketLibCallbacks::OnFail, Message, HttpStatus);
		}

		void HandleClose(websocketpp::connection_hdl Hdl)
		{
			State = EState::Closed;

			websocketpp::lib::error_code Error;
			FConnectionPtr Connection = Endpoint.get_con_from_hdl(Hdl, Error);

			int32 Code = websocketpp::close::status::abnormal_close;
			FString Reason;
			if (Connection)
			{
				Code = Connection->get_remote_close_code();
				Reason = ToFString(Connection->get_remote_close_reason());
			}

			//1006 means the connection dropped without a close frame
			const bool bWasClean = Code != websocketpp::close::status::abnormal_close;
			if (!bWasClean && Reason.IsEmpty())
			{
				Reason = TakeLoggedError();
			}
			Callbacks->Call(&FWebSocketLibCallbacks::OnClose, Code, Reason, bWasClean);
		}

		void HandleMessage(const FMessagePtr& Message)
		{
			const std::string& Payload = Message->get_payload();
			if (Message->get_opcode() == websocketpp::frame::opcode::text)
			{
				Callbacks->Call(&FWebSocketLibCallbacks::OnText, ToFString(Payload));
			}
			else
			{
				Callbacks->Call(&FWebSocketLibCallbacks::OnBinary, TArray<uint8>(reinterpret_cast<const uint8*>(Payload.data()), (int32)Payload.size()));
			}
		}

		/** Last line of the error log ("[time] [level] text" -> "text"), clears the log */
		FString TakeLoggedError()
		{
			std::string Log = ErrorLog.str();
			ErrorLog.str(std::string());
			ErrorLog.clear();

			const size_t End = Log.find_last_not_of("\r\n");
			if (End == std::string::npos)
			{
				return FString();
			}
			const size_t LineStart = Log.find_last_of('\n', End);
			std::string Line = Log.substr(LineStart == std::string::npos ? 0 : LineStart + 1, End + 1 - (LineStart == std::string::npos ? 0 : LineStart + 1));

			const size_t LevelStart = Line.find("] [");
			const size_t TextStart = LevelStart == std::string::npos ? std::string::npos : Line.find("] ", LevelStart + 2);
			if (TextStart != std::string::npos)
			{
				Line = Line.substr(TextStart + 2);
			}
			return ToFString(Line);
		}

		std::shared_ptr<asio_sockio::ssl::context> MakeTlsContext()
		{
			std::shared_ptr<asio_sockio::ssl::context> Context = std::make_shared<asio_sockio::ssl::context>(asio_sockio::ssl::context::sslv23_client);
			asio_sockio::error_code Error;

			//TLS 1.2 and up
			Context->set_options(asio_sockio::ssl::context::default_workarounds |
				asio_sockio::ssl::context::no_sslv2 |
				asio_sockio::ssl::context::no_sslv3 |
				asio_sockio::ssl::context::no_tlsv1 |
				asio_sockio::ssl::context::no_tlsv1_1, Error);

			if (!bVerifyCertificate)
			{
				Context->set_verify_mode(asio_sockio::ssl::verify_none, Error);
				return Context;
			}

			if (CertificateManager)
			{
				CertificateManager->AddCertificatesToSslContext(Context->native_handle());
			}
			else
			{
				UE_LOG(LogWebSocketLib, Warning, TEXT("SSL module isn't loaded, only AdditionalCACertificatesPEM are trusted"));
			}

			if (!AdditionalCACertificates.empty() && AddPemCertificates(Context->native_handle(), AdditionalCACertificates) == 0)
			{
				UE_LOG(LogWebSocketLib, Warning, TEXT("AdditionalCACertificatesPEM didn't contain a usable certificate"));
			}

			Context->set_verify_mode(asio_sockio::ssl::verify_peer, Error);
			Context->set_verify_callback(FCertificateVerifier{ asio_sockio::ssl::rfc2818_verification(Host), Host, CertificateManager, &VerifyError }, Error);
			return Context;
		}

		//Declared before Endpoint so they outlive it, its logger and handlers use them
		FCallbackHolderRef Callbacks;
		const ISslCertificateManager* CertificateManager;
		std::ostringstream ErrorLog;
		std::string VerifyError;
		std::string Host;
		std::string AdditionalCACertificates;
		bool bVerifyCertificate = true;

		std::atomic<EState> State{ EState::Idle };
		std::atomic<std::thread::id> NetworkThreadId;

		std::mutex CloseMutex;
		bool bCloseRequested = false;
		uint16 CloseCode = websocketpp::close::status::normal;
		std::string CloseReason;

		std::mutex FinishedMutex;
		std::condition_variable FinishedCondition;
		bool bFinished = false;

		websocketpp::connection_hdl Handle;
		ClientType Endpoint;
	};

	void StopAllConnections(float TimeoutSeconds)
	{
		FConnectionRegistry& Registry = GetRegistry();

		auto WaitForThreads = [&Registry](double Seconds)
		{
			const double End = FPlatformTime::Seconds() + Seconds;
			while (Registry.RunningThreads.load() > 0 && FPlatformTime::Seconds() < End)
			{
				FPlatformProcess::Sleep(0.01f);
			}
			return Registry.RunningThreads.load() == 0;
		};

		//Connections that are already closing usually finish within a moment
		if (WaitForThreads(TimeoutSeconds * 0.5))
		{
			return;
		}

		std::vector<std::shared_ptr<IConnection>> Remaining;
		{
			std::lock_guard<std::mutex> Guard(Registry.Mutex);
			for (const std::weak_ptr<IConnection>& Weak : Registry.Connections)
			{
				if (std::shared_ptr<IConnection> Connection = Weak.lock())
				{
					Remaining.push_back(Connection);
				}
			}
		}
		for (const std::shared_ptr<IConnection>& Connection : Remaining)
		{
			Connection->DisableCallbacks();
			Connection->Stop();
		}
		Remaining.clear();

		if (!WaitForThreads(TimeoutSeconds * 0.5))
		{
			UE_LOG(LogWebSocketLib, Warning, TEXT("%d websocket network threads still running at shutdown"), Registry.RunningThreads.load());
		}
	}
}

struct FWebSocketLibClient::FImpl
{
	FCriticalSection Lock;
	FWebSocketLibCallbacks Callbacks;
	std::shared_ptr<WebSocketLib::IConnection> Connection;

	std::shared_ptr<WebSocketLib::IConnection> GetConnection()
	{
		FScopeLock Guard(&Lock);
		return Connection;
	}

	/** Swap the connection, the old one finishes closing on its own thread without callbacks */
	void Replace(const std::shared_ptr<WebSocketLib::IConnection>& NewConnection, const char* Reason)
	{
		std::shared_ptr<WebSocketLib::IConnection> Old;
		{
			FScopeLock Guard(&Lock);
			Old = Connection;
			Connection = NewConnection;
		}
		if (Old)
		{
			Old->DisableCallbacks();
			Old->Close(websocketpp::close::status::going_away, Reason);
		}
	}
};

FWebSocketLibClient::FWebSocketLibClient()
	: Impl(MakeUnique<FImpl>())
{
}

FWebSocketLibClient::~FWebSocketLibClient()
{
	Impl->Replace(nullptr, "Client destroyed");
}

void FWebSocketLibClient::SetCallbacks(const FWebSocketLibCallbacks& InCallbacks)
{
	FScopeLock Guard(&Impl->Lock);
	Impl->Callbacks = InCallbacks;
}

bool FWebSocketLibClient::Connect(const FWebSocketLibConnectParams& Params, FString& OutError)
{
	using namespace WebSocketLib;

	const bool bTls = Params.Url.StartsWith(TEXT("wss://"), ESearchCase::IgnoreCase);
	if (!bTls && !Params.Url.StartsWith(TEXT("ws://"), ESearchCase::IgnoreCase))
	{
		OutError = FString::Printf(TEXT("Url '%s' has to start with ws:// or wss://"), *Params.Url);
		return false;
	}

	FCallbackHolderRef Holder = [this]()
	{
		FScopeLock Guard(&Impl->Lock);
		return MakeShared<FCallbackHolder, ESPMode::ThreadSafe>(Impl->Callbacks);
	}();

	std::shared_ptr<IConnection> Connection;
	if (bTls)
	{
		const ISslCertificateManager* CertificateManager = nullptr;
#if WITH_SSL
		if (FSslModule* SslModule = FModuleManager::GetModulePtr<FSslModule>(TEXT("SSL")))
		{
			CertificateManager = &SslModule->GetCertificateManager();
		}
#endif
		Connection = std::make_shared<TConnection<FTlsClient>>(Holder, CertificateManager);
	}
	else
	{
		Connection = std::make_shared<TConnection<FPlainClient>>(Holder, nullptr);
	}

	//The previous connection goes first, even if this one fails to start
	Impl->Replace(nullptr, "Reconnecting");

	if (!Connection->Start(Params, OutError))
	{
		return false;
	}

	FScopeLock Guard(&Impl->Lock);
	Impl->Connection = Connection;
	return true;
}

void FWebSocketLibClient::Close(int32 StatusCode, const FString& Reason)
{
	if (std::shared_ptr<WebSocketLib::IConnection> Connection = Impl->GetConnection())
	{
		Connection->Close((uint16)StatusCode, WebSocketLib::ToStd(Reason));
	}
}

void FWebSocketLibClient::SyncClose(int32 StatusCode, const FString& Reason, float TimeoutSeconds)
{
	std::shared_ptr<WebSocketLib::IConnection> Connection = Impl->GetConnection();
	if (!Connection)
	{
		return;
	}

	Connection->Close((uint16)StatusCode, WebSocketLib::ToStd(Reason));
	if (Connection->IsNetworkThread())
	{
		return;
	}
	if (!Connection->WaitUntilFinished(TimeoutSeconds))
	{
		UE_LOG(LogWebSocketLib, Warning, TEXT("Close didn't finish within %.1fs, stopping the connection"), TimeoutSeconds);
		Connection->Stop();
		Connection->WaitUntilFinished(1.f);
	}
}

bool FWebSocketLibClient::SendText(const FString& Message)
{
	std::shared_ptr<WebSocketLib::IConnection> Connection = Impl->GetConnection();
	return Connection && Connection->Send(std::make_shared<const std::string>(WebSocketLib::ToStd(Message)), false);
}

bool FWebSocketLibClient::SendBinary(const uint8* Data, int64 NumBytes)
{
	std::shared_ptr<WebSocketLib::IConnection> Connection = Impl->GetConnection();
	if (!Connection)
	{
		return false;
	}
	std::shared_ptr<const std::string> Payload = (Data && NumBytes > 0) ?
		std::make_shared<const std::string>(reinterpret_cast<const char*>(Data), (size_t)NumBytes) :
		std::make_shared<const std::string>();
	return Connection->Send(Payload, true);
}

bool FWebSocketLibClient::IsConnected() const
{
	std::shared_ptr<WebSocketLib::IConnection> Connection = Impl->GetConnection();
	return Connection && Connection->IsOpen();
}
