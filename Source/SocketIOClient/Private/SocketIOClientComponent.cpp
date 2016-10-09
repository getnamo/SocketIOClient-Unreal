// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"
#include "SIOLambdaRunnable.h"


USocketIOClientComponent::USocketIOClientComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	ShouldAutoConnect = true;
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	AddressAndPort = FString(TEXT("http://localhost:3000"));	//default to 127.0.0.1
	SessionId = FString(TEXT("invalid"));
}

std::string StdString(FString UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));	//TCHAR_TO_ANSI try this string instead?
}
FString FStringFromStd(std::string StdString)
{
	return FString(StdString.c_str());
}


void USocketIOClientComponent::Connect(FString InAddressAndPort)
{
	std::string StdAddressString = StdString(InAddressAndPort);
	if (InAddressAndPort.IsEmpty())
	{
		StdAddressString = StdString(AddressAndPort);
	}

	//Connect to the server on a background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		//Attach the specific connection status events events

		PrivateClient.set_open_listener(sio::client::con_listener([&]() {
			SessionId = FStringFromStd(PrivateClient.get_sessionid());
			UE_LOG(LogTemp, Log, TEXT("SocketIO Connected with session: %s"), *SessionId);
			OnConnected.Broadcast(SessionId);
		}));

		PrivateClient.set_close_listener(sio::client::close_listener([&](sio::client::close_reason const& reason)
		{
			SessionId = FString(TEXT("invalid"));
			UE_LOG(LogTemp, Log, TEXT("SocketIO Disconnected"));
			OnDisconnected.Broadcast((EConnectionCloseReason)reason);
		}));

		PrivateClient.set_socket_open_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = FStringFromStd(nsp);
			UE_LOG(LogTemp, Log, TEXT("SocketIO connected to namespace: %s"), *Namespace);
			OnSocketNamespaceConnected.Broadcast(Namespace);
		}));

		PrivateClient.set_socket_close_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = FStringFromStd(nsp);
			UE_LOG(LogTemp, Log, TEXT("SocketIO disconnected from namespace: %s"), *Namespace);
			OnSocketNamespaceDisconnected.Broadcast(FStringFromStd(nsp));
		}));

		PrivateClient.set_fail_listener(sio::client::con_listener([&]()
		{
			UE_LOG(LogTemp, Log, TEXT("SocketIO failed to connect."));
			OnFail.Broadcast();
		}));
		
		PrivateClient.connect(StdAddressString);
	});
}


void USocketIOClientComponent::Disconnect()
{
	if (PrivateClient.opened())
	{
		PrivateClient.socket()->off_all();
		PrivateClient.socket()->off_error();
		PrivateClient.close();
	}
}

void USocketIOClientComponent::Emit(FString Name, FString Data, FString Namespace /* = FString(TEXT("/"))*/)
{
	PrivateClient.socket(StdString(Namespace))->emit(StdString(Name), StdString(Data));
	//UE_LOG(LogTemp, Log, TEXT("Emit %s with %s"), *Name, *Data);
}


void USocketIOClientComponent::EmitBuffer(FString Name, uint8* Data, int32 DataLength, FString Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(StdString(Namespace))->emit(StdString(Name), std::make_shared<std::string>((char*)Data, DataLength));
}

void USocketIOClientComponent::BindEvent(FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	BindDataLambdaToEvent([&](const FString& EventName, const FString& EventData)
	{
		On.Broadcast(EventName, EventData);
	}, Name, Namespace);
}


void USocketIOClientComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if (ShouldAutoConnect)
	{
		Connect(AddressAndPort);	//connect to default address
	}
}

void USocketIOClientComponent::UninitializeComponent()
{
	Disconnect();
	Super::UninitializeComponent();
}

void USocketIOClientComponent::BindLambdaToEvent(TFunction< void()> InFunction, FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void()> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(StdString(Namespace))->on(
		StdString(Name),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction]
		{
			SafeFunction();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}

void USocketIOClientComponent::BindDataLambdaToEvent(
	TFunction< void(const FString&, const FString&)> InFunction,
	FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const FString&)> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(StdString(Namespace))->on(
		StdString(Name),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = FStringFromStd(name);
		
		//Todo: modify data->get_string() to stringify if data is an object or binary
		const FString SafeData = (data != nullptr) ? FStringFromStd(data->get_string()) : FString(TEXT(""));

		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, SafeData]
		{
			SafeFunction(SafeName, SafeData);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}


void USocketIOClientComponent::BindRawMessageLambdaToEvent(TFunction< void(const FString&, const sio::message::ptr&)> InFunction, FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(StdString(Namespace))->on(
		StdString(Name),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = FStringFromStd(name);

		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, data]
		{
			SafeFunction(SafeName, data);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}


void USocketIOClientComponent::BindBinaryMessageLambdaToEvent(TFunction< void(const FString&, const TArray<uint8>&)> InFunction, FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(StdString(Namespace))->on(
		StdString(Name),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = FStringFromStd(name);

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
			UE_LOG(LogTemp, Warning, TEXT("Non-binary message received to binary message lambda, check server message data!"));
		}
	}));
}

//Todo: add object -> json conversion, or convert it to a UEJSON object that can stringify

sio::message::ptr USocketIOClientComponent::getMessage(const std::string& json)
{
	//std::lock_guard< std::mutex > guard(packetLock);
	sio::message::ptr message;
	/*manager.set_decode_callback([&](sio::packet const& p)
	{
		message = p.get_message();
	});

	// Magic message type / ID
	std::string payload = std::string("42") + json;
	manager.put_payload(payload);

	manager.reset();*/
	return message;
}

std::string USocketIOClientComponent::getJson(sio::message::ptr msg)
{
	//std::lock_guard< std::mutex > guard(packetLock);
	/*std::stringstream ss;
	sio::packet packet("/", msg);
	manager.encode(packet, [&](bool isBinary, std::shared_ptr<const std::string> const& json)
	{
		ss << *json;
		assert(!isBinary);
	});
	manager.reset();

	// Need to strip off the message type flags (typically '42',
	// but there are other possible combinations).
	std::string result = ss.str();
	std::size_t indexList = result.find('[');
	std::size_t indexObject = result.find('{');
	std::size_t indexString = result.find('"');
	std::size_t index = indexList;
	if (indexObject != std::string::npos && indexObject < index)
		index = indexObject;
	if (indexString != std::string::npos && indexString < index)
		index = indexString;

	if (index == std::string::npos) {
		UE_LOG(LogTemp, Log, TEXT("Error decoding json object\n Body: %s"), result);
		return "";
	}
	return result;//.substr(index);*/
	return std::string();
}
