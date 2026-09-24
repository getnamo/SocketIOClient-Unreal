// Copyright 2018-current Getnamo. All Rights Reserved


#include "SocketIONative.h"
#include "SIOMessageConvert.h"
#include "CULambdaRunnable.h"
#include "SIOJConvert.h"
#include "sio_client.h"
#include "sio_message.h"
#include "sio_socket.h"

FSocketIONative::FSocketIONative(const bool bForceTLS, const bool bShouldVerifyTLSCertificate)
{
	PrivateClient = nullptr;
	SessionId = TEXT("Invalid");
	LastSessionId = TEXT("None");
	bIsConnected = false;
	//sio compares `m_reconn_made < m_reconn_attempts` on an unsigned, so the "unlimited"
	//value is the all-ones one, not 0 — 0 means zero attempts. Spelled out rather than
	//left as a -1 that happens to wrap, so nobody "corrects" it to 0 and silently turns
	//reconnection off.
	MaxReconnectionAttempts = kUnlimitedReconnectionAttempts;
	ReconnectionDelay = 5000;
	bCallbackOnGameThread = true;
	bUnbindEventsOnDisconnect = false;
	bForceTLSUse = bForceTLS;
	InitPrivateClient(bForceTLS, bShouldVerifyTLSCertificate);

	ClearAllCallbacks();
}


void FSocketIONative::InitPrivateClient(const bool bShouldUseTlsLibraries /*= false*/, const bool bShouldVerifyTLSCertificate /*= false*/)
{
	bIsSetupForTLS = bShouldUseTlsLibraries;
	bUsingTLSCertVerification = bShouldVerifyTLSCertificate;
	PrivateClient = MakeShareable(new sio::client(bShouldUseTlsLibraries, bUsingTLSCertVerification));
}

void FSocketIONative::Connect(const FSIOConnectParams& InConnectParams)
{
	//Special case: reconnect on current settings if address is empty
	if (!InConnectParams.AddressAndPort.IsEmpty())
	{
		URLParams = InConnectParams;
	}

	SyncPrivateClientToTLSMode(URLParams.AddressAndPort);

	//Belt and braces for the listener install. The client is normally handed out by
	//FSocketIOClientModule::NewValidNativePointer(), which sets the listeners up once the shared
	//pointer exists — but FSocketIONative is public API, so a caller can own one it built itself
	//and never go through the factory. Redoing it here costs a few assignments and makes the
	//object correct however it was created. Idempotent: sio just overwrites each listener slot,
	//and this touches none of the user callbacks or the event map.
	SetupInternalCallbacks();
	
	//Fill std types before going to background thread.

	std::string StdAddressString = USIOMessageConvert::StdString(URLParams.AddressAndPort);
	std::string StdPathString = USIOMessageConvert::StdString(URLParams.Path);
	std::map<std::string, std::string> QueryMap = {};
	std::map<std::string, std::string> HeadersMap = {};
	sio::message::ptr AuthMessage = sio::object_message::create();
	if (!URLParams.AuthToken.IsEmpty())
	{
		AuthMessage->get_map()["token"] = sio::string_message::create(USIOMessageConvert::StdString(URLParams.AuthToken));
	}
	if (URLParams.ExtraAuth.Num() > 0)
	{
		TArray<FString> Keys;
		URLParams.ExtraAuth.GetKeys(Keys);

		for (const FString& Key : Keys)
		{
			std::string StdKey = USIOMessageConvert::StdString(Key);
			std::string StdValue = USIOMessageConvert::StdString(URLParams.ExtraAuth[Key]);
			AuthMessage->get_map()[StdKey] = sio::string_message::create(StdValue);
		}
	}

	QueryMap = USIOMessageConvert::FStringMapToStdStringMap(URLParams.Query);
	HeadersMap = USIOMessageConvert::FStringMapToStdStringMap(URLParams.Headers);

	//Connect to the server on a background thread so it never blocks. Weak self rather than
	//a captured `this`: connect() can block for the length of a TCP timeout, and a caller that
	//connects and then tears down (a level transition is the usual way) releases this object
	//while the pool thread is still inside the body.
	TWeakPtr<FSocketIONative> WeakSelf = AsShared();
	FCULambdaRunnable::RunLambdaOnBackGroundThread([WeakSelf, StdAddressString, StdPathString, QueryMap, HeadersMap, AuthMessage]
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid() || !Self->PrivateClient.IsValid())
		{
			return;
		}

		Self->PrivateClient->set_reconnect_attempts(Self->MaxReconnectionAttempts);
		Self->PrivateClient->set_reconnect_delay(Self->ReconnectionDelay);
		Self->PrivateClient->set_path(StdPathString);

		//close and reconnect if different url
		if(Self->PrivateClient->opened())
		{
			if (Self->PrivateClient->get_url() != StdAddressString)
			{
				//sync close to re-open
				Self->PrivateClient->sync_close();
			}
			else
			{
				//we're already connected to the correct endpoint, ignore request
				UE_LOG(SocketIO, Warning, TEXT("Attempted to connect to %s when we're already connected. Request ignored."), UTF8_TO_TCHAR(StdAddressString.c_str()));
				return;
			}
		}
		Self->PrivateClient->connect(StdAddressString, QueryMap, HeadersMap, AuthMessage);
	});
}

void FSocketIONative::Connect(const FString& InAddressAndPort)
{
	if (!InAddressAndPort.IsEmpty())
	{
		URLParams.AddressAndPort = InAddressAndPort;
	}

	Connect(URLParams);
}

void FSocketIONative::JoinNamespace(const FString& Namespace)
{
	//just referencing the namespace will join it
	PrivateClient->socket(USIOMessageConvert::StdString(Namespace));
}

void FSocketIONative::LeaveNamespace(const FString& Namespace)
{
	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->close();
}

void FSocketIONative::Disconnect()
{
	// OnDisconnectedCallback is fired asynchronously by the close_listener registered in
	// SetupInternalCallbacks, after PrivateClient->close() completes. Firing it
	// synchronously here would run while opened() is still true, so any handler that
	// tries to reconnect would be rejected by Connect()'s !opened() guard.
	bIsConnected = false;

	if (bUnbindEventsOnDisconnect)
	{
		ClearAllCallbacks();
		PrivateClient->close();
	}
	else
	{
		//Clear and re-init map
		ClearInternalCallbacks();
		PrivateClient->close();
		RebindCurrentEventMap();
	}
}

void FSocketIONative::SyncDisconnect()
{
	//Ensure disconnected callback is called first because we 
	//clear all callbacks for stability.
	if (OnDisconnectedCallback)
	{
		OnDisconnectedCallback(ESIOConnectionCloseReason::CLOSE_REASON_NORMAL);
	}
	bIsConnected = false;

	if (bUnbindEventsOnDisconnect)
	{
		ClearAllCallbacks();
		PrivateClient->sync_close();
	}
	else
	{
		//Clear and re-init map
		ClearInternalCallbacks();
		PrivateClient->sync_close();
		RebindCurrentEventMap();
	}
}

void FSocketIONative::ClearAllCallbacks()
{
	PrivateClient->clear_socket_listeners();
	SetupInternalCallbacks();					//if clear socket listeners cleared our internal callbacks. reset them
	EventFunctionMap.Empty();

	OnConnectedCallback = nullptr;
	OnDisconnectedCallback = nullptr;
	OnNamespaceConnectedCallback = nullptr;
	OnNamespaceDisconnectedCallback = nullptr;
	OnReconnectionCallback = nullptr;
	OnFailCallback = nullptr;
	OnErrorCallback = nullptr;
}

void FSocketIONative::Emit(const FString& EventName, const TSharedPtr<FJsonValue>& Message /*= nullptr*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	TFunction<void(const sio::message::list&)> RawCallback = nullptr;

	//Only bind the raw callback if we pass in a callback ourselves;
	if (CallbackFunction)
	{
		RawCallback = [CallbackFunction](const sio::message::list& MessageList)
		{
			TArray<TSharedPtr<FJsonValue>> ValueArray;

			for (uint32 i = 0; i < MessageList.size(); i++)
			{
				auto ItemMessagePtr = MessageList[i];
				ValueArray.Add(USIOMessageConvert::ToJsonValue(ItemMessagePtr));
			}
			if (CallbackFunction)
			{
				CallbackFunction(ValueArray);
			}
		};
	}

	EmitRaw(
		EventName,
		USIOMessageConvert::ToSIOMessage(Message),
		RawCallback,
		Namespace);
}

void FSocketIONative::Emit(const FString& EventName, const TSharedPtr<FJsonObject>& ObjectMessage /*= nullptr*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, MakeShareable(new FJsonValueObject(ObjectMessage)), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, const FString& StringMessage /*= FString()*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, MakeShareable(new FJsonValueString(StringMessage)), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, double NumberMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, MakeShareable(new FJsonValueNumber(NumberMessage)), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, bool BooleanMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, MakeShareable(new FJsonValueBoolean(BooleanMessage)), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, const TArray<uint8>& BinaryMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, MakeShareable(new FJsonValueBinary(BinaryMessage)), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, const TArray<TSharedPtr<FJsonValue>>& ArrayMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, MakeShareable(new FJsonValueArray(ArrayMessage)), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, UStruct* Struct, const void* StructPtr, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	Emit(EventName, USIOJConvert::ToJsonObject(Struct, (void*)StructPtr), CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= TEXT("/")*/)
{
	TSharedPtr<FJsonValue> NoneValue;
	Emit(EventName, NoneValue, CallbackFunction, Namespace);
}

void FSocketIONative::Emit(const FString& EventName, const SIO_TEXT_TYPE StringMessage /*= TEXT("")*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= TEXT("/")*/)
{
	Emit(EventName, MakeShareable(new FJsonValueString(FString(StringMessage))), CallbackFunction, Namespace);
}

void FSocketIONative::EmitRaw(const FString& EventName, const sio::message::list& MessageList /*= nullptr*/, TFunction<void(const sio::message::list&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	std::function<void(sio::message::list const&)> RawCallback = nullptr;

	//Only have non-null raw callback if we pass in a callback function
	if (CallbackFunction)
	{
		//Weak self: the ack arrives on the asio thread, and reading bCallbackOnGameThread off
		//a captured `this` is a read of freed memory if the socket was released meanwhile.
		TWeakPtr<FSocketIONative> WeakSelf = AsShared();
		RawCallback = [WeakSelf, CallbackFunction](const sio::message::list& response)
		{
			TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
			if (!Self.IsValid())
			{
				return;
			}

			if (CallbackFunction != nullptr)
			{
				//Callback on game thread
				if (Self->bCallbackOnGameThread)
				{
					FCULambdaRunnable::RunShortLambdaOnGameThread([CallbackFunction, response]
					{
						if (CallbackFunction)
						{
							CallbackFunction(response);
						}
					});
				}
				else
				{
					CallbackFunction(response);
				}
			}
		};
	}

	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->emit(
		USIOMessageConvert::StdString(EventName),
		MessageList,
		RawCallback);
}

void FSocketIONative::EmitRawBinary(const FString& EventName, uint8* Data, int32 DataLength, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->emit(USIOMessageConvert::StdString(EventName), std::make_shared<std::string>((char*)Data, DataLength));
}

void FSocketIONative::OnEvent(const FString& EventName, 
	TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction, 
	const FString& Namespace /*= FString(TEXT("/"))*/,
	ESIOThreadOverrideOption CallbackThread /*= USE_DEFAULT*/)
{
	//Keep track of all the bound native JsonValue functions
	FSIOBoundEvent BoundEvent;
	BoundEvent.Function = CallbackFunction;
	BoundEvent.Namespace = Namespace;
	BoundEvent.ThreadOption = CallbackThread;
	EventFunctionMap.Add(EventName, BoundEvent);

	OnRawEvent(EventName, [CallbackFunction](const FString& Event, const sio::message::ptr& RawMessage) {
		CallbackFunction(Event, USIOMessageConvert::ToJsonValue(RawMessage));
	}, Namespace, CallbackThread);
}

void FSocketIONative::OnRawEvent(const FString& EventName, 
	TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction, 
	const FString& Namespace /*= FString(TEXT("/"))*/,
	ESIOThreadOverrideOption CallbackThread /*= USE_DEFAULT*/)
{
	if (CallbackFunction == nullptr)
	{
		PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->off(USIOMessageConvert::StdString(EventName));
	}
	else
	{
		//determine thread override option
		bool bCallbackThisEventOnGameThread = bCallbackOnGameThread;
		switch (CallbackThread)
		{
		case USE_DEFAULT:
			break;
		case USE_GAME_THREAD:
			bCallbackThisEventOnGameThread = true;
			break;
		case USE_NETWORK_THREAD:
			bCallbackThisEventOnGameThread = false;
			break;
		default:
			break;
		}

		const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

		PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->on(
			USIOMessageConvert::StdString(EventName),
			sio::socket::event_listener_aux(
			[SafeFunction, bCallbackThisEventOnGameThread](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
			{
				if (SafeFunction != nullptr)
				{
					const FString SafeName = USIOMessageConvert::FStringFromStd(name);

					if (bCallbackThisEventOnGameThread)
					{
						FCULambdaRunnable::RunShortLambdaOnGameThread([SafeFunction, SafeName, data]
							{
								SafeFunction(SafeName, data);
							});
					}
					else
					{
						SafeFunction(SafeName, data);
					}
				}
			}));
	}
}

void FSocketIONative::OnError(TFunction< void(const FString&)> CallbackFunction,
	const FString& Namespace /*= FString(TEXT("/"))*/,
	ESIOThreadOverrideOption CallbackThread /*= USE_DEFAULT*/)
{
	//Keep track of all the bound native JsonValue functions
	OnErrorCallback = CallbackFunction;

	OnRawError([CallbackFunction](const sio::message::ptr& ErrorRaw) {
		CallbackFunction(USIOMessageConvert::FStringFromStd(ErrorRaw.get()->get_string()));
		}, Namespace, CallbackThread);
}

void FSocketIONative::OnRawError(TFunction< void(const sio::message::ptr&)> CallbackFunction,
	const FString& Namespace /*= FString(TEXT("/"))*/,
	ESIOThreadOverrideOption CallbackThread /*= USE_DEFAULT*/)
{
	if (CallbackFunction == nullptr)
	{
		PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->off_error();
	}
	else
	{
		//determine thread override option
		bool bCallbackThisEventOnGameThread = bCallbackOnGameThread;
		switch (CallbackThread)
		{
		case USE_DEFAULT:
			break;
		case USE_GAME_THREAD:
			bCallbackThisEventOnGameThread = true;
			break;
		case USE_NETWORK_THREAD:
			bCallbackThisEventOnGameThread = false;
			break;
		default:
			break;
		}

		const TFunction< void(const sio::message::ptr&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

		PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->on_error(
			sio::socket::error_listener(
				[SafeFunction, bCallbackThisEventOnGameThread](sio::message::ptr const& error)
				{
					if (SafeFunction != nullptr)
					{
						if (bCallbackThisEventOnGameThread)
						{
							FCULambdaRunnable::RunShortLambdaOnGameThread([SafeFunction, error]
								{
									SafeFunction(error);
								});
						}
						else
						{
							SafeFunction(error);
						}
					}
				}));
	}
}

void FSocketIONative::OnRawBinaryEvent(const FString& EventName, TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	//Weak self for the same reason as the other listeners: the body reads
	//bCallbackOnGameThread on the asio thread, before any hop to the game thread.
	TWeakPtr<FSocketIONative> WeakSelf = AsShared();

	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->on(
		USIOMessageConvert::StdString(EventName),
		sio::socket::event_listener_aux(
			[WeakSelf, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid())
		{
			return;
		}

		const FString SafeName = USIOMessageConvert::FStringFromStd(name);

		//Construct raw buffer
		if (data->get_flag() == sio::message::flag_binary)
		{
			TArray<uint8> Buffer;
			int32 BufferSize = data->get_binary()->size();
			auto MessageBuffer = data->get_binary();
			Buffer.Append((uint8*)(MessageBuffer->data()), BufferSize);

			if (Self->bCallbackOnGameThread)
			{
				FCULambdaRunnable::RunShortLambdaOnGameThread([SafeFunction, SafeName, Buffer]
				{
					SafeFunction(SafeName, Buffer);
				});
			}
			else
			{
				SafeFunction(SafeName, Buffer);
			}
		}
		else
		{
			UE_LOG(SocketIO, Warning, TEXT("Non-binary message received to binary message lambda, check server message data!"));
		}
	}));
}

void FSocketIONative::UnbindEvent(const FString& EventName, const FString& Namespace /*= TEXT("/")*/)
{
	OnRawEvent(EventName, nullptr, Namespace);
	EventFunctionMap.Remove(EventName);
}

void FSocketIONative::ClearInternalCallbacks()
{
	PrivateClient->clear_socket_listeners();
}

void FSocketIONative::SetupInternalCallbacks()
{
	//These listeners are invoked from the asio network thread and outlive nothing: sio holds
	//them for as long as the client exists, and the client is destroyed from whichever thread
	//releases the FSocketIONative. So the listener body itself — not just the game-thread hop
	//inside it — can be running while this object is going away.
	//
	//The hops were already fixed to Pin a weak self; the code that ran BEFORE them still read
	//members off a captured `this`. One weak ref taken here, pinned at the top of each body,
	//covers both: nothing in the listener touches a member until Pin() has succeeded, and the
	//pin then keeps the object alive for the rest of the body.
	//
	//AsShared() needs this object to already be owned by a TSharedPtr, and one caller runs
	//before that is true: the constructor calls ClearAllCallbacks(), which lands here while
	//MakeShareable() has not yet wrapped the object — AsShared() would assert on
	//DoesSharedInstanceExist(). Bail out on that pass; FSocketIOClientModule::NewValidNativePointer()
	//calls ClearAllCallbacks() again the moment the shared pointer exists, which installs the
	//listeners for real. Every other caller (ClearAllCallbacks and RebindCurrentEventMap after
	//construction) proceeds normally.
	if (!DoesSharedInstanceExist())
	{
		return;
	}

	TWeakPtr<FSocketIONative> WeakSelf = AsShared();

	PrivateClient->set_open_listener(sio::client::con_listener([]()
	{
		//too early to get session id here so we defer the connection event until we connect to a namespace
	}));

	PrivateClient->set_close_listener(sio::client::close_listener([WeakSelf](sio::client::close_reason const& reason)
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid())
		{
			return;
		}

		Self->bIsConnected = false;

		const ESIOConnectionCloseReason DisconnectReason = static_cast<ESIOConnectionCloseReason>(reason);
		//UE 5.8: StaticEnum<>() is deleted for this namespaced UENUM, so map the close
		//reason to a string directly for the diagnostic log below.
		FString DisconnectReasonString = (DisconnectReason == CLOSE_REASON_NORMAL) ? TEXT("CLOSE_REASON_NORMAL") : TEXT("CLOSE_REASON_DROP");
		if (Self->VerboseLog)
		{
			UE_LOG(SocketIO, Log, TEXT("SocketIO Disconnected %s reason: %s"), *Self->SessionId, *DisconnectReasonString);
		}
		Self->LastSessionId = Self->SessionId;
		Self->SessionId = TEXT("Invalid");

		if (Self->OnDisconnectedCallback)
		{
			if (Self->bCallbackOnGameThread)
			{
				FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf, DisconnectReason]
				{
					if (TSharedPtr<FSocketIONative> HopSelf = WeakSelf.Pin())
					{
						if (HopSelf->OnDisconnectedCallback)
						{
							HopSelf->OnDisconnectedCallback(DisconnectReason);
						}
					}
				});
			}
			else
			{
				Self->OnDisconnectedCallback(DisconnectReason);
			}
		}
	}));

	PrivateClient->set_socket_open_listener(sio::client::socket_listener([WeakSelf](std::string const& nsp)
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid())
		{
			return;
		}

		//Special case, we have a latent connection after already having been disconnected
		if (!Self->PrivateClient.IsValid())
		{
			return;
		}
		if (!Self->bIsConnected)
		{
			Self->bIsConnected = true;
			Self->SessionId = USIOMessageConvert::FStringFromStd(Self->PrivateClient->get_sessionid());
			Self->SocketId = USIOMessageConvert::FStringFromStd(Self->PrivateClient->socket(nsp)->get_socket_id());

			if (Self->VerboseLog)
			{
				UE_LOG(SocketIO, Log, TEXT("SocketIO Connected with session: %s"), *Self->SessionId);
			}
			if (Self->OnConnectedCallback)
			{
				if (Self->bCallbackOnGameThread)
				{
					FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf]
					{
						if (TSharedPtr<FSocketIONative> HopSelf = WeakSelf.Pin())
						{
							if (HopSelf->OnConnectedCallback)
							{
								HopSelf->OnConnectedCallback(HopSelf->SocketId, HopSelf->SessionId);
							}
						}
					});
				}
				else
				{
					Self->OnConnectedCallback(Self->SocketId, Self->SessionId);
				}
			}
		}

		const FString Namespace = USIOMessageConvert::FStringFromStd(nsp);

		if (Self->VerboseLog)
		{
			UE_LOG(SocketIO, Log, TEXT("SocketIO %s connected to namespace: %s"), *Self->SessionId, *Namespace);
		}
		if (Self->OnNamespaceConnectedCallback)
		{
			if (Self->bCallbackOnGameThread)
			{
				FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf, Namespace]
				{
					if (TSharedPtr<FSocketIONative> HopSelf = WeakSelf.Pin())
					{
						if (HopSelf->OnNamespaceConnectedCallback)
						{
							HopSelf->OnNamespaceConnectedCallback(Namespace);
						}
					}
				});
			}
			else
			{
				Self->OnNamespaceConnectedCallback(Namespace);
			}
		}
	}));

	PrivateClient->set_socket_close_listener(sio::client::socket_listener([WeakSelf](std::string const& nsp)
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid())
		{
			return;
		}

		const FString Namespace = USIOMessageConvert::FStringFromStd(nsp);
		FString NamespaceSession = Self->SessionId;
		if (NamespaceSession.Equals(TEXT("Invalid")))
		{
			NamespaceSession = Self->LastSessionId;
		}
		if (Self->VerboseLog)
		{
			UE_LOG(SocketIO, Log, TEXT("SocketIO %s disconnected from namespace: %s"), *NamespaceSession, *Namespace);
		}
		if (Self->OnNamespaceDisconnectedCallback)
		{
			if (Self->bCallbackOnGameThread)
			{
				FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf, Namespace]
				{
					if (TSharedPtr<FSocketIONative> HopSelf = WeakSelf.Pin())
					{
						if (HopSelf->OnNamespaceDisconnectedCallback)
						{
							HopSelf->OnNamespaceDisconnectedCallback(Namespace);
						}
					}
				});
			}
			else
			{
				Self->OnNamespaceDisconnectedCallback(Namespace);
			}
		}
	}));

	PrivateClient->set_fail_listener(sio::client::con_listener([WeakSelf]()
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid())
		{
			return;
		}

		if (Self->VerboseLog)
		{
			UE_LOG(SocketIO, Log, TEXT("SocketIO failed to connect."));
		}
		if (Self->OnFailCallback)
		{
			if (Self->bCallbackOnGameThread)
			{
				FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf]
				{
					if (TSharedPtr<FSocketIONative> HopSelf = WeakSelf.Pin())
					{
						if (HopSelf->OnFailCallback)
						{
							HopSelf->OnFailCallback();
						}
					}
				});
			}
			else
			{
				Self->OnFailCallback();
			}
		}
	}));

	PrivateClient->set_reconnect_listener(sio::client::reconnect_listener([WeakSelf](unsigned num, unsigned delay)
	{
		TSharedPtr<FSocketIONative> Self = WeakSelf.Pin();
		if (!Self.IsValid())
		{
			return;
		}

		Self->bIsConnected = false;

		if (Self->VerboseLog)
		{
			UE_LOG(SocketIO, Log, TEXT("SocketIO %s appears to have lost connection, reconnecting attempt %d with delay %d"), *Self->SessionId, num, delay);
		}
		if (Self->OnReconnectionCallback)
		{
			if (Self->bCallbackOnGameThread)
			{
				FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf, num, delay]
				{
					if (TSharedPtr<FSocketIONative> HopSelf = WeakSelf.Pin())
					{
						if (HopSelf->OnReconnectionCallback)
						{
							HopSelf->OnReconnectionCallback(num, delay);
						}
					}
				});
			}
			else
			{
				Self->OnReconnectionCallback(num, delay);
			}
		}
	}));
}

void FSocketIONative::RebindCurrentEventMap()
{
	ClearInternalCallbacks();

	for (auto& EventPair : EventFunctionMap)
	{
		const FString& EventName = EventPair.Key;
		const FSIOBoundEvent EventBind = EventPair.Value;

		OnRawEvent(EventName, [EventBind](const FString& Event, const sio::message::ptr& RawMessage) {
			EventBind.Function(Event, USIOMessageConvert::ToJsonValue(RawMessage));
		}, EventBind.Namespace, EventBind.ThreadOption);
	}

	SetupInternalCallbacks();
}

bool FSocketIONative::IsTLSURL(const FString& URL)
{
	return URL.StartsWith(TEXT("https://")) || URL.StartsWith(TEXT("wss://"));
}

void FSocketIONative::SyncPrivateClientToTLSMode(const FString& URL)
{
	//Should be in TLS mode?
	if (IsTLSURL(URL) || bForceTLSUse)
	{
		//needs to swap to TLS
		if (!bIsSetupForTLS)
		{
			if (PrivateClient->opened())
			{
				PrivateClient->sync_close();
			}
			ClearInternalCallbacks();
			InitPrivateClient(true, bUsingTLSCertVerification);
			RebindCurrentEventMap();
		}
	}
	//Should not be in TLS mode
	else
	{
		//URL is not TLS, but we are setup for it
		if (bIsSetupForTLS)
		{
			if (PrivateClient->opened())
			{
				PrivateClient->sync_close();
			}
			ClearInternalCallbacks();
			InitPrivateClient(false, bUsingTLSCertVerification);
			RebindCurrentEventMap();
		}
	}
}

