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
}

std::string StdString(FString UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));
}
FString FStringFromStd(std::string StdString)
{
	return FString(StdString.c_str());
}


void USocketIOClientComponent::Connect(FString InAddressAndPort)
{
	std::string StdAddressString = StdString(InAddressAndPort);
	if (AddressAndPort.IsEmpty())
	{
		StdAddressString = StdString(AddressAndPort);
	}

	//Connect to the server on a background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		//Attach the specific events
		BindLambdaToEvent([&]
		{
			UE_LOG(LogTemp, Log, TEXT("SocketIO Connected"));
			OnConnected.Broadcast();
		}, FString(TEXT("connected")), FString(TEXT("/")));	//you need to emit this on the server to receive the event

		BindLambdaToEvent([&]
		{
			UE_LOG(LogTemp, Log, TEXT("SocketIO Disconnected"));
			OnDisconnected.Broadcast();
		}, FString(TEXT("disconnect")), FString(TEXT("/")));	//doesn't get called atm, unsure how to get it called

		PrivateClient.connect(StdAddressString);
	});
}


void USocketIOClientComponent::Disconnect()
{
	PrivateClient.close();
}

void USocketIOClientComponent::Emit(FString Name, FString Data, FString Namespace /* = FString(TEXT("/"))*/)
{
	PrivateClient.socket(StdString(Namespace))->emit(StdString(Name), StdString(Data));
	//UE_LOG(LogTemp, Log, TEXT("Emit %s with %s"), *Name, *Data);
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