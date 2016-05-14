// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"


// Sets default values for this component's properties
USocketIOClientComponent::USocketIOClientComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

std::string StdString(FString UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));
}
FString FStringFromStd(std::string StdString)
{
	return FString(StdString.c_str());
}


// Called when the game starts
void USocketIOClientComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USocketIOClientComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USocketIOClientComponent::Connect(FString AddressAndPort)
{
	PrivateClient.connect(StdString(AddressAndPort));
}

void USocketIOClientComponent::Emit(FString Name, FString Data)
{
	PrivateClient.socket()->emit(StdString(Name), StdString(Data));
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


