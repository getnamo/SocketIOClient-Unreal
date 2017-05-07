
#include "SocketIOClientPrivatePCH.h"
#include "SIOLambdaRunnable.h"
#include "SIOJConvert.h"
#include "SocketIONative.h"

FSocketIONative::FSocketIONative()
{
	ConnectionThread = nullptr;
	PrivateClient = nullptr;
	AddressAndPort = FString(TEXT("http://localhost:3000"));	//default to 127.0.0.1
	SessionId = FString(TEXT("invalid"));
	bIsConnected = false;

	ClearCallbacks();

	PrivateClient = MakeShareable(new sio::client);
}

void FSocketIONative::Connect(const FString& InAddressAndPort, const TSharedPtr<FJsonObject>& Query /*= nullptr*/, const TSharedPtr<FJsonObject>& Headers /*= nullptr*/)
{
	std::string StdAddressString = USIOMessageConvert::StdString(InAddressAndPort);
	if (InAddressAndPort.IsEmpty())
	{
		StdAddressString = USIOMessageConvert::StdString(AddressAndPort);
	}

	//Connect to the server on a background thread so it never blocks
	ConnectionThread = FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&, Query, Headers]
	{
		//Attach the specific connection status events events

		PrivateClient->set_open_listener(sio::client::con_listener([&]() {
			//too early to get session id here so we defer the connection event until we connect to a namespace
		}));

		PrivateClient->set_close_listener(sio::client::close_listener([&](sio::client::close_reason const& reason)
		{
			bIsConnected = false;
			SessionId = FString(TEXT("invalid"));
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO Disconnected: %d"), (int32)reason);

			if (OnDisconnectedCallback)
			{
				OnDisconnectedCallback((ESIOConnectionCloseReason)reason);
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

				UE_LOG(SocketIOLog, Log, TEXT("SocketIO Connected with session: %s"), *SessionId);

				if (OnConnectedCallback)
				{
					OnConnectedCallback(SessionId);
				}
			}

			FString Namespace = USIOMessageConvert::FStringFromStd(nsp);
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO connected to namespace: %s"), *Namespace);

			if (OnNamespaceConnectedCallback)
			{
				OnNamespaceConnectedCallback(Namespace);
			}
		}));

		PrivateClient->set_socket_close_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = USIOMessageConvert::FStringFromStd(nsp);
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO disconnected from namespace: %s"), *Namespace);

			if (OnNamespaceDisconnectedCallback)
			{
				OnNamespaceDisconnectedCallback(USIOMessageConvert::FStringFromStd(nsp));
			}
		}));

		PrivateClient->set_fail_listener(sio::client::con_listener([&]()
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO failed to connect."));
			if (OnFailCallback)
			{
				OnFailCallback();
			}
		}));

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

		PrivateClient->connect(StdAddressString, QueryMap, HeadersMap);
	});
}

void FSocketIONative::Disconnect()
{	
	PrivateClient->close();
}

void FSocketIONative::SyncDisconnect()
{
	OnDisconnectedCallback(ESIOConnectionCloseReason::CLOSE_REASON_NORMAL);
	ClearCallbacks();
	PrivateClient->sync_close();
}

void FSocketIONative::ClearCallbacks()
{
	OnConnectedCallback = nullptr;
	OnDisconnectedCallback = nullptr;
	OnNamespaceConnectedCallback = nullptr;
	OnNamespaceDisconnectedCallback = nullptr;
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

		for (int i = 0; i < MessageList.size(); i++)
		{
			auto ItemMessagePtr = MessageList[i];
			ValueArray.Add(USIOMessageConvert::ToJsonValue(ItemMessagePtr));
		}

		SafeCallback(ValueArray);
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

