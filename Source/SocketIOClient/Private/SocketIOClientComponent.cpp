#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"
#include "sio_client.h"
#include "sio_message.h"
#include <string>

USocketIOClientComponent::USocketIOClientComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;


}

/*void USocketIOClientComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void USocketIOClientComponent::UninitializeComponent()
{
	//Disconnect?

	Super::UninitializeComponent();


}*/

std::string StdString(FString UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));
}
FString FStringFromStd(std::string StdString)
{
	return FString(StdString.c_str());
}

void USocketIOClientComponent::Emit(FString Name, FString Action)
{
	PrivateClient.socket()->emit(StdString(Name), StdString(Action));
	UE_LOG(LogTemp, Log, TEXT("Emit %s with %s"), *Name, *Action);
}

void USocketIOClientComponent::Bind(FString Name)
{
	//Passthrough hookups
	PrivateClient.socket()->on(StdString(Name), sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		On.Broadcast(FStringFromStd(name), FStringFromStd(data->get_string()));
	}));
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
	UE_LOG(LogTemp, Log, TEXT("Connecting to %s"), *AddressAndPort);
}