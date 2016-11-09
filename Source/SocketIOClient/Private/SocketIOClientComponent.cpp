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

void USocketIOClientComponent::EmitString(FString Name, FString Data, FString Namespace /* = FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(USIOJsonConverter::StdString(Name), USIOJsonConverter::StdString(Data));
	//UE_LOG(LogTemp, Log, TEXT("Emit %s with %s"), *Name, *Data);
}


void USocketIOClientComponent::Emit(FString Name, UVaRestJsonValue* Data, FString Namespace /*= FString(TEXT("/"))*/)
{
	//Todo: convert va json to FJsonValue and emit
	//PrivateClient.socket(StdString(Namespace))->emit(StdString(Name), StdString(Data));
}

void USocketIOClientComponent::EmitBuffer(FString Name, uint8* Data, int32 DataLength, FString Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(USIOJsonConverter::StdString(Name), std::make_shared<std::string>((char*)Data, DataLength));
}

void USocketIOClientComponent::EmitRaw(FString Name, const sio::message::list& MessageList, FString Namespace)
{
	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->emit(USIOJsonConverter::StdString(Name), MessageList);
}

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

/*void USocketIOClientComponent::BindEvent(FString Name, FString Namespace )
{
BindStringMessageLambdaToEvent([&](const FString& EventName, const FString& EventData)
{
On.Broadcast(EventName, EventData);
}, Name, Namespace);
}*/


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



void USocketIOClientComponent::OnEvent(FString Event, TFunction< void(const FString&, const FJsonValue&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	OnRawEvent(Event, [&](const FString& EventName, const sio::message::ptr& RawMessage) {

	}, Namespace);
}

/*
void USocketIOClientComponent::OnEvent(FString Event, FSIOCEventSignature CallbackEvent)
{

}
*/

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

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->on(
		USIOJsonConverter::StdString(Name),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction]
		{
			SafeFunction();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}

void USocketIOClientComponent::BindStringMessageLambdaToEvent(
	TFunction< void(const FString&, const FString&)> InFunction,
	FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const FString&)> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->on(
		USIOJsonConverter::StdString(Name),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOJsonConverter::FStringFromStd(name);
		FString TempData;
		
		//Convert number messages into strings, only supported bypass for now
		if (data->get_flag() == data->flag_string)
		{
			TempData = USIOJsonConverter::FStringFromStd(data->get_string());
		}
		else if (data->get_flag() == data->flag_integer)
		{
			TempData = USIOJsonConverter::FStringFromStd(std::to_string(data->get_int()));
		}
		else if (data->get_flag() == data->flag_double)
		{
			TempData = USIOJsonConverter::FStringFromStd(std::to_string(data->get_double()));
		}
		else if (data->get_flag() == data->flag_boolean)
		{
			TempData = USIOJsonConverter::FStringFromStd(std::to_string(data->get_bool()));
		}
		else
		{
			TempData = FString(TEXT(""));
			UE_LOG(LogTemp, Warning, TEXT("SocketIOClientComponent Unsupported data type for BindStringMessageLambdaToEvent, use C++ events for now."));
		}

		//Todo: modify data->get_string() to stringify if data is an object or binary
		const FString& SafeData = TempData;

		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, SafeData]
		{
			SafeFunction(SafeName, SafeData);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}


void USocketIOClientComponent::BindRawMessageLambdaToEvent(TFunction< void(const FString&, const sio::message::ptr&)> InFunction, FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->on(
		USIOJsonConverter::StdString(Name),
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


void USocketIOClientComponent::BindBinaryMessageLambdaToEvent(TFunction< void(const FString&, const TArray<uint8>&)> InFunction, FString Name, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = InFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJsonConverter::StdString(Namespace))->on(
		USIOJsonConverter::StdString(Name),
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