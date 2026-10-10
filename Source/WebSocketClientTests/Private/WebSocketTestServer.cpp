// Copyright 2026-current Getnamo. All Rights Reserved

#include "WebSocketTestServer.h"
#include "WebSocketTestIncludes.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

namespace WebSocketTestServer
{
	typedef websocketpp::server<websocketpp::config::asio> FPlainServer;
	typedef websocketpp::server<websocketpp::config::asio_tls> FTlsServer;

	static EVP_PKEY* MakeKey()
	{
		EVP_PKEY* Params = nullptr;
		EVP_PKEY* Key = nullptr;

		EVP_PKEY_CTX* ParamContext = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
		if (ParamContext &&
			EVP_PKEY_paramgen_init(ParamContext) > 0 &&
			EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ParamContext, NID_X9_62_prime256v1) > 0 &&
			EVP_PKEY_paramgen(ParamContext, &Params) > 0)
		{
			EVP_PKEY_CTX* KeyContext = EVP_PKEY_CTX_new(Params, nullptr);
			if (KeyContext && EVP_PKEY_keygen_init(KeyContext) > 0)
			{
				EVP_PKEY_keygen(KeyContext, &Key);
			}
			EVP_PKEY_CTX_free(KeyContext);
		}
		EVP_PKEY_free(Params);
		EVP_PKEY_CTX_free(ParamContext);
		return Key;
	}

	/** Issuer null makes a self-signed certificate */
	static X509* MakeCertificate(EVP_PKEY* Key, const char* CommonName, X509* Issuer, EVP_PKEY* IssuerKey, bool bIsCA, const char* SubjectAltName, long Serial)
	{
		X509* Certificate = X509_new();
		X509_set_version(Certificate, 2);
		ASN1_INTEGER_set(X509_get_serialNumber(Certificate), Serial);
		X509_gmtime_adj(X509_getm_notBefore(Certificate), -3600);
		X509_gmtime_adj(X509_getm_notAfter(Certificate), 24 * 3600);
		X509_set_pubkey(Certificate, Key);

		X509_NAME* Name = X509_get_subject_name(Certificate);
		X509_NAME_add_entry_by_txt(Name, "CN", MBSTRING_ASC, reinterpret_cast<const unsigned char*>(CommonName), -1, -1, 0);
		X509_set_issuer_name(Certificate, Issuer ? X509_get_subject_name(Issuer) : Name);

		X509V3_CTX ExtensionContext;
		X509V3_set_ctx_nodb(&ExtensionContext);
		X509V3_set_ctx(&ExtensionContext, Issuer ? Issuer : Certificate, Certificate, nullptr, nullptr, 0);
		auto AddExtension = [&](int Nid, const char* Value)
		{
			if (X509_EXTENSION* Extension = X509V3_EXT_conf_nid(nullptr, &ExtensionContext, Nid, const_cast<char*>(Value)))
			{
				X509_add_ext(Certificate, Extension, -1);
				X509_EXTENSION_free(Extension);
			}
		};
		AddExtension(NID_basic_constraints, bIsCA ? "critical,CA:TRUE" : "CA:FALSE");
		if (bIsCA)
		{
			AddExtension(NID_key_usage, "critical,keyCertSign,cRLSign");
		}
		if (SubjectAltName)
		{
			AddExtension(NID_subject_alt_name, SubjectAltName);
		}

		X509_sign(Certificate, IssuerKey ? IssuerKey : Key, EVP_sha256());
		return Certificate;
	}

	static std::string ToPem(X509* Certificate)
	{
		BIO* Bio = BIO_new(BIO_s_mem());
		PEM_write_bio_X509(Bio, Certificate);
		char* Data = nullptr;
		const long Length = BIO_get_mem_data(Bio, &Data);
		std::string Pem(Data, Length);
		BIO_free(Bio);
		return Pem;
	}

	/** A test CA and a "localhost" server certificate it signed */
	struct FCertificates
	{
		EVP_PKEY* CAKey = nullptr;
		X509* CACertificate = nullptr;
		EVP_PKEY* ServerKey = nullptr;
		X509* ServerCertificate = nullptr;
		std::string CAPem;

		~FCertificates()
		{
			X509_free(ServerCertificate);
			EVP_PKEY_free(ServerKey);
			X509_free(CACertificate);
			EVP_PKEY_free(CAKey);
		}

		bool Generate()
		{
			CAKey = MakeKey();
			ServerKey = MakeKey();
			if (!CAKey || !ServerKey)
			{
				return false;
			}
			CACertificate = MakeCertificate(CAKey, "WebSocketClient Test CA", nullptr, nullptr, true, nullptr, 1);
			ServerCertificate = MakeCertificate(ServerKey, "localhost", CACertificate, CAKey, false, "DNS:localhost", 2);
			CAPem = ToPem(CACertificate);
			return CACertificate && ServerCertificate;
		}
	};

	class IServer
	{
	public:
		virtual ~IServer() = default;
		virtual bool Start(FCertificates* Certificates) = 0;
		virtual void Stop() = 0;
		virtual int32 GetPort() const = 0;
	};

	template<typename ServerType>
	class TServer : public IServer
	{
		static constexpr bool bIsTls = std::is_same<ServerType, FTlsServer>::value;
		typedef typename ServerType::connection_ptr FConnectionPtr;
		typedef typename ServerType::message_ptr FMessagePtr;

	public:
		virtual ~TServer()
		{
			Stop();
		}

		virtual bool Start(FCertificates* InCertificates) override
		{
			Certificates = InCertificates;

			websocketpp::lib::error_code Error;
			Endpoint.clear_access_channels(websocketpp::log::alevel::all);
			Endpoint.clear_error_channels(websocketpp::log::elevel::all);
			Endpoint.init_asio(Error);
			if (Error)
			{
				return false;
			}

			Endpoint.set_reuse_addr(true);
			Endpoint.set_validate_handler([this](websocketpp::connection_hdl Hdl) { return Validate(Hdl); });
			Endpoint.set_message_handler([this](websocketpp::connection_hdl Hdl, FMessagePtr Message) { HandleMessage(Hdl, Message); });
			if constexpr (bIsTls)
			{
				Endpoint.set_tls_init_handler([this](websocketpp::connection_hdl) { return MakeTlsContext(); });
			}

			Endpoint.listen(asio_sockio::ip::tcp::endpoint(asio_sockio::ip::make_address("127.0.0.1"), 0), Error);
			if (Error)
			{
				return false;
			}
			Endpoint.start_accept(Error);
			if (Error)
			{
				return false;
			}

			asio_sockio::error_code EndpointError;
			Port = Endpoint.get_local_endpoint(EndpointError).port();
			Thread = std::thread([this]() { Endpoint.run(); });
			return true;
		}

		virtual void Stop() override
		{
			if (Thread.joinable())
			{
				Endpoint.stop();
				Thread.join();
			}
		}

		virtual int32 GetPort() const override
		{
			return Port;
		}

	private:
		bool Validate(websocketpp::connection_hdl Hdl)
		{
			websocketpp::lib::error_code Error;
			FConnectionPtr Connection = Endpoint.get_con_from_hdl(Hdl, Error);
			if (!Connection)
			{
				return false;
			}

			if (Connection->get_resource() == "/reject")
			{
				Connection->set_status(websocketpp::http::status_code::unauthorized);
				return false;
			}

			const std::vector<std::string>& Requested = Connection->get_requested_subprotocols();
			if (!Requested.empty())
			{
				Connection->select_subprotocol(Requested[0], Error);
			}
			return true;
		}

		void HandleMessage(websocketpp::connection_hdl Hdl, FMessagePtr Message)
		{
			websocketpp::lib::error_code Error;
			FConnectionPtr Connection = Endpoint.get_con_from_hdl(Hdl, Error);
			if (!Connection)
			{
				return;
			}

			const std::string& Payload = Message->get_payload();
			if (Message->get_opcode() == websocketpp::frame::opcode::text)
			{
				if (Payload.rfind("close:", 0) == 0)
				{
					const size_t Split = Payload.find(':', 6);
					const int Code = std::atoi(Payload.substr(6, Split == std::string::npos ? std::string::npos : Split - 6).c_str());
					const std::string Reason = Split == std::string::npos ? std::string() : Payload.substr(Split + 1);
					Connection->close((websocketpp::close::status::value)Code, Reason, Error);
					return;
				}
				if (Payload == "drop")
				{
					Connection->get_raw_socket().close(Error);
					return;
				}
				if (Payload.rfind("header:", 0) == 0)
				{
					Endpoint.send(Hdl, Connection->get_request_header(Payload.substr(7)), websocketpp::frame::opcode::text, Error);
					return;
				}
			}
			Endpoint.send(Hdl, Payload, Message->get_opcode(), Error);
		}

		std::shared_ptr<asio_sockio::ssl::context> MakeTlsContext()
		{
			std::shared_ptr<asio_sockio::ssl::context> Context = std::make_shared<asio_sockio::ssl::context>(asio_sockio::ssl::context::sslv23_server);
			SSL_CTX_use_certificate(Context->native_handle(), Certificates->ServerCertificate);
			SSL_CTX_use_PrivateKey(Context->native_handle(), Certificates->ServerKey);
			return Context;
		}

		FCertificates* Certificates = nullptr;
		int32 Port = 0;
		std::thread Thread;
		ServerType Endpoint;
	};
}

struct FWebSocketTestServer::FImpl
{
	WebSocketTestServer::FCertificates Certificates;
	TUniquePtr<WebSocketTestServer::IServer> Server;
	bool bTLS = false;
};

FWebSocketTestServer::FWebSocketTestServer()
	: Impl(MakeUnique<FImpl>())
{
}

FWebSocketTestServer::~FWebSocketTestServer()
{
	Stop();
}

bool FWebSocketTestServer::Start(bool bUseTLS)
{
	using namespace WebSocketTestServer;

	Stop();
	Impl->bTLS = bUseTLS;
	if (bUseTLS)
	{
		if (!Impl->Certificates.CACertificate && !Impl->Certificates.Generate())
		{
			return false;
		}
		Impl->Server = MakeUnique<TServer<FTlsServer>>();
	}
	else
	{
		Impl->Server = MakeUnique<TServer<FPlainServer>>();
	}
	return Impl->Server->Start(&Impl->Certificates);
}

void FWebSocketTestServer::Stop()
{
	Impl->Server.Reset();
}

int32 FWebSocketTestServer::GetPort() const
{
	return Impl->Server.IsValid() ? Impl->Server->GetPort() : 0;
}

FString FWebSocketTestServer::GetUrl(const FString& Host, const FString& Path) const
{
	return FString::Printf(TEXT("%s://%s:%d%s"), Impl->bTLS ? TEXT("wss") : TEXT("ws"), *Host, GetPort(), *Path);
}

FString FWebSocketTestServer::GetCACertificatePEM() const
{
	return UTF8_TO_TCHAR(Impl->Certificates.CAPem.c_str());
}
