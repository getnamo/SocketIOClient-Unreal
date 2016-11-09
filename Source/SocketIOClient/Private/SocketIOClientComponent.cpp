// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"
#include "SIOLambdaRunnable.h"
#include "SIOJsonConverter.h"


USocketIOClientComponent::USocketIOClientComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	ShouldAutoConnect = true;
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	AddressAndPort = FString(TEXT("http://localhost:3000"));	//default to 127.0.0.1
	SessionId = FString(TEXT("invalid"));
}

void USocketIOClientComponent::Connect(FString InAddressAndPort)
{
	std::string StdAddressString = USIOJsonConverter::StdString(InAddressAndPort);
	if (InAddressAndPort.IsEmpty())
	{
		StdAddressString = USIOJsonConverter::StdString(AddressAndPort);
	}

	//Connect to the server on a background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		//Attach the specific connection status events events

		PrivateClient.set_open_listener(sio::client::con_listener([&]() {
			SessionId = USIOJsonConverter::FStringFromStd(PrivateClient.get_sessionid());
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
			FString Namespace = USIOJsonConverter::FStringFromStd(nsp);
			UE_LOG(LogTemp, Log, TEXT("SocketIO connected to namespace: %s"), *Namespace);
			OnSocketNamespaceConnected.Broadcast(Namespace);
		}));

		PrivateClient.set_socket_close_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = USIOJsonConverter::FStringFromStd(nsp);
			UE_LOG(LogTemp, Log, TEXT("SocketIO disconnected from namespace: %s"), *Namespace);
			OnSocketNamespaceDisconnected.Broadcast(USIOJsonConverter::FStringFromStd(nsp));
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
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		if (PrivateClient.opened())
		{
			PrivateClient.socket()->off_all();
			PrivateClient.socket()->off_error();
			PrivateClient.close();
		}
	});
}

#pragma 

void USocketIOClientComponent::Emit(FString Name, UVaRestJsonValue* Data, FString Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(
		USIOJsonConverter::StdString(Name),
		USIOJsonConverter::ToSIOMessage(Data->GetRootValue()));
}

void USocketIOClientComponent::EmitBinary(FString Name, uint8* Data, int32 DataLength, FString Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(USIOJsonConverter::StdString(Name), std::make_shared<std::string>((char*)Data, DataLength));
}

/*void USocketIOClientComponent::EmitRaw(FString Name, const sio::message::list& MessageList, FString Namespace)
{
	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(USIOJsonConverter::StdString(Name), MessageList);
}*/

//todo: collapse all of this into a single usable Emit
void USocketIOClientComponent::EmitRawWithCallback(FString Name, const sio::message::list& MessageList, TFunction<void(const sio::message::list&)> ResponseFunction, FString Namespace)
{
	const TFunction<void(const sio::message::list&)> SafeFunction = ResponseFunction;

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(USIOJsonConverter::StdString(Name), MessageList, [&, SafeFunction](const sio::message::list& response) {
		//Call on gamethread
		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, response]
		{
			SafeFunction(response);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	});
}


void USocketIOClientComponent::OnEvent(FString Event, TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	OnRawEvent(Event, [&](const FString& EventName, const sio::message::ptr& RawMessage) {

	}, Namespace);
}

void USocketIOClientComponent::OnRawEvent(FString Event, TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->on(
		USIOJsonConverter::StdString(Event),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOJsonConverter::FStringFromStd(name);

		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, data]
		{
			SafeFunction(SafeName, data);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}


void USocketIOClientComponent::OnBinaryEvent(FString Event, TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->on(
		USIOJsonConverter::StdString(Event),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOJsonConverter::FStringFromStd(name);

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

void USocketIOClientComponent::BindEvent(FString Event, FString Namespace)
{
	UE_LOG(LogTemp, Log, TEXT("Bound event %s"), *Event);
	
	OnRawEvent(Event, [&](const FString& EventName, const sio::message::ptr& RawMessage) {
		UVaRestJsonValue* NewValue = NewObject<UVaRestJsonValue>();
		auto Value = USIOJsonConverter::ToJsonValue(RawMessage);
		NewValue->SetRootValue(Value);
		On.Broadcast(EventName, NewValue);

	}, Namespace);
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