// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"


USocketIOClientComponent::USocketIOClientComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
}

std::string StdString(FString UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));
}
FString FStringFromStd(std::string StdString)
{
	return FString(StdString.c_str());
}


void USocketIOClientComponent::Connect(FString AddressAndPort)
{
	if (!AddressAndPort.IsEmpty())
	{
		PrivateClient.connect(StdString(AddressAndPort));
	}
	else
	{
		PrivateClient.connect("http://localhost:3000");
	}
}

void USocketIOClientComponent::Emit(FString Name, FString Data)
{
	PrivateClient.socket()->emit(StdString(Name), StdString(Data));
	//UE_LOG(LogTemp, Log, TEXT("Emit %s with %s"), *Name, *Data);
}

void USocketIOClientComponent::Bind(FString Name)
{
	PrivateClient.socket()->on(StdString(Name), sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp) {

		const FString SafeName = FStringFromStd(name);
		const FString SafeData = FStringFromStd(data->get_string());
		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeName, SafeData]
		{
			On.Broadcast(SafeName, SafeData);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}


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
	std::string result;// = ss.str();
	//std::lock_guard< std::mutex > guard(packetLock);
	//std::stringstream ss;
	//sio::packet packet("/", msg);
	/*manager.encode(packet, [&](bool isBinary, std::shared_ptr<const std::string> const& json)
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
		std::cerr << "Error decoding json object" << std::endl << " Body: " << result << std::endl;
		return "";
	}*/
	return result;//.substr(index);
}