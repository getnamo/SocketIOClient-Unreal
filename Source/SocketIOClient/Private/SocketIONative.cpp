// Copyright 2018-current Getnamo. All Rights Reserved


#include "SocketIONative.h"
#include "SocketIOClientPrivatePCH.h"
#include "LambdaRunnable.h"
#include "SIOJConvert.h"

FSocketIONative::FSocketIONative()
{
	PrivateClient = nullptr;
	AddressAndPort = TEXT("http://localhost:3000");	//default to 127.0.0.1
	SessionId = TEXT("Invalid");
	LastSessionId = TEXT("None");
	bIsConnected = false;
	MaxReconnectionAttempts = -1;
	ReconnectionDelay = 5000;

	PrivateClient = MakeShareable(new sio::client);

	ClearCallbacks();
}

void FSocketIONative::Connect(const FString& InAddressAndPort, const TSharedPtr<FJsonObject>& Query /*= nullptr*/, const TSharedPtr<FJsonObject>& Headers /*= nullptr*/)
{
	std::string StdAddressString = USIOMessageConvert::StdString(InAddressAndPort);
	if (InAddressAndPort.IsEmpty())
	{
		StdAddressString = USIOMessageConvert::StdString(AddressAndPort);
	}

	//Connect to the server on a background thread so it never blocks
	FLambdaRunnable::RunLambdaOnBackGroundThread([&, Query, Headers]
	{
		std::map<std::string, std::string> QueryMap = {};
		std::map<std::string, std::string> HeadersMap = {};

		//fill the headers and query if they're not null
		if (Headers.IsValid())
		{
			HeadersMap = USIOMessageConvert::JsonObjectToStdStringMap(Headers);
		}

		if (Query.IsValid())
		{
			QueryMap = USIOMessageConvert::JsonObjectToStdStringMap(Query);
		}

		PrivateClient->set_reconnect_attempts(MaxReconnectionAttempts);
		PrivateClient->set_reconnect_delay(ReconnectionDelay);

		//Add  temporary workaround for android build of socket.io (doesn't have my fork changes so it won't have the 3 param connect function)
#if PLATFORM_ANDROID
		PrivateClient->connect(StdAddressString, QueryMap);// , HeadersMap);
#else
		PrivateClient->connect(StdAddressString, QueryMap, HeadersMap);
#endif

	});
}

void FSocketIONative::Connect(const FString& InAddressAndPort)
{
	TSharedPtr<FJsonObject> Query = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> Headers = MakeShareable(new FJsonObject);

	Connect(InAddressAndPort, Query, Headers);
}

void FSocketIONative::Disconnect()
{	
	if (OnDisconnectedCallback)
	{
		OnDisconnectedCallback(ESIOConnectionCloseReason::CLOSE_REASON_NORMAL);
	}
	bIsConnected = false;
	ClearCallbacks();
	PrivateClient->close();
}

void FSocketIONative::SyncDisconnect()
{
	if (OnDisconnectedCallback)
	{
		OnDisconnectedCallback(ESIOConnectionCloseReason::CLOSE_REASON_NORMAL);
	}
	bIsConnected = false;
	ClearCallbacks();
	PrivateClient->sync_close();
}

void FSocketIONative::ClearCallbacks()
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
}

void FSocketIONative::Emit(const FString& EventName, const TSharedPtr<FJsonValue>& Message /*= nullptr*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const auto SafeCallback = CallbackFunction;
	EmitRaw(
		EventName,
		USIOMessageConvert::ToSIOMessage(Message),
		[&, SafeCallback](const sio::message::list& MessageList)
	{
		TArray<TSharedPtr<FJsonValue>> ValueArray;

		for (uint32 i = 0; i < MessageList.size(); i++)
		{
			auto ItemMessagePtr = MessageList[i];
			ValueArray.Add(USIOMessageConvert::ToJsonValue(ItemMessagePtr));
		}
		if (SafeCallback)
		{
			SafeCallback(ValueArray);
		}
	}, Namespace);
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

void FSocketIONative::EmitRaw(const FString& EventName, const sio::message::list& MessageList /*= nullptr*/, TFunction<void(const sio::message::list&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction<void(const sio::message::list&)> SafeFunction = CallbackFunction;

	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->emit(
		USIOMessageConvert::StdString(EventName),
		MessageList,
		[&, SafeFunction](const sio::message::list& response)
	{
		if (SafeFunction != nullptr)
		{
			//Callback on game thread
			FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, response]
			{
				SafeFunction(response);
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		}
	});
}

void FSocketIONative::EmitRawBinary(const FString& EventName, uint8* Data, int32 DataLength, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->emit(USIOMessageConvert::StdString(EventName), std::make_shared<std::string>((char*)Data, DataLength));
}

void FSocketIONative::OnEvent(const FString& EventName, TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	//Keep track of all the bound functions
	EventFunctionMap.Add(EventName, CallbackFunction);

	OnRawEvent(EventName, [&, CallbackFunction](const FString& Event, const sio::message::ptr& RawMessage) {
		CallbackFunction(Event, USIOMessageConvert::ToJsonValue(RawMessage));
	}, Namespace);
}

void FSocketIONative::OnRawEvent(const FString& EventName, TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->on(
		USIOMessageConvert::StdString(EventName),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOMessageConvert::FStringFromStd(name);

		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, data]
		{
			SafeFunction(SafeName, data);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}

void FSocketIONative::OnBinaryEvent(const FString& EventName, TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient->socket(USIOMessageConvert::StdString(Namespace))->on(
		USIOMessageConvert::StdString(EventName),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOMessageConvert::FStringFromStd(name);

		//Construct raw buffer
		if (data->get_flag() == sio::message::flag_binary)
		{
			TArray<uint8> Buffer;
			int32 BufferSize = data->get_binary()->size();
			auto MessageBuffer = data->get_binary();
			Buffer.Append((uint8*)(MessageBuffer->data()), BufferSize);

			FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, Buffer]
			{
				SafeFunction(SafeName, Buffer);
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		}
		else
		{
			UE_LOG(SocketIOLog, Warning, TEXT("Non-binary message received to binary message lambda, check server message data!"));
		}
	}));
}

void FSocketIONative::UnbindEvent(const FString& EventName, const FString& Namespace /*= TEXT("/")*/)
{
	OnRawEvent(EventName, nullptr, Namespace);
}

void FSocketIONative::SetupInternalCallbacks()
{
	PrivateClient->set_open_listener(sio::client::con_listener([&]() {
		//too early to get session id here so we defer the connection event until we connect to a namespace
	}));

	PrivateClient->set_close_listener(sio::client::close_listener([&](sio::client::close_reason const& reason)
	{
		bIsConnected = false;

		ESIOConnectionCloseReason DisconnectReason = (ESIOConnectionCloseReason)reason;
		FString DisconnectReasonString = USIOJConvert::EnumToString(TEXT("ESIOConnectionCloseReason"), DisconnectReason);
		if (VerboseLog)
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO Disconnected %s reason: %s"), *SessionId, *DisconnectReasonString);
		}
		LastSessionId = SessionId;
		SessionId = TEXT("Invalid");

		if (OnDisconnectedCallback)
		{
			OnDisconnectedCallback(DisconnectReason);
		}
	}));

	PrivateClient->set_socket_open_listener(sio::client::socket_listener([&](std::string const& nsp)
	{
		//Special case, we have a latent connection after already having been disconnected
		if (!PrivateClient.IsValid())
		{
			return;
		}
		if (!bIsConnected)
		{
			bIsConnected = true;
			SessionId = USIOMessageConvert::FStringFromStd(PrivateClient->get_sessionid());

			if (VerboseLog)
			{
				UE_LOG(SocketIOLog, Log, TEXT("SocketIO Connected with session: %s"), *SessionId);
			}
			if (OnConnectedCallback)
			{
				OnConnectedCallback(SessionId);
			}
		}

		FString Namespace = USIOMessageConvert::FStringFromStd(nsp);

		if (VerboseLog)
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO %s connected to namespace: %s"), *SessionId, *Namespace);
		}
		if (OnNamespaceConnectedCallback)
		{
			OnNamespaceConnectedCallback(Namespace);
		}
	}));

	PrivateClient->set_socket_close_listener(sio::client::socket_listener([&](std::string const& nsp)
	{
		FString Namespace = USIOMessageConvert::FStringFromStd(nsp);
		FString NamespaceSession = SessionId;
		if (NamespaceSession.Equals(TEXT("Invalid")))
		{
			NamespaceSession = LastSessionId;
		}
		if (VerboseLog)
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO %s disconnected from namespace: %s"), *NamespaceSession, *Namespace);
		}
		if (OnNamespaceDisconnectedCallback)
		{
			OnNamespaceDisconnectedCallback(USIOMessageConvert::FStringFromStd(nsp));
		}
	}));

	PrivateClient->set_fail_listener(sio::client::con_listener([&]()
	{
		if (VerboseLog)
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO failed to connect."));
		}
		if (OnFailCallback)
		{
			OnFailCallback();
		}
	}));

	PrivateClient->set_reconnect_listener(sio::client::reconnect_listener([&](unsigned num, unsigned delay)
	{
		bIsConnected = false;

		if (VerboseLog)
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO %s appears to have lost connection, reconnecting attempt %d with delay %d"), *SessionId, num, delay);
		}
		if (OnReconnectionCallback)
		{
			OnReconnectionCallback(num, delay);
		}
	}));
}

