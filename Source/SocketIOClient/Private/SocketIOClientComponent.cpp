// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"
#include "SIOLambdaRunnable.h"
#include "SIOJConvert.h"


USocketIOClientComponent::USocketIOClientComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	ShouldAutoConnect = true;
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	AddressAndPort = FString(TEXT("http://localhost:3000"));	//default to 127.0.0.1
	SessionId = FString(TEXT("invalid"));
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

#pragma region Connect

void USocketIOClientComponent::Connect(FString InAddressAndPort)
{
	std::string StdAddressString = USIOJConvert::StdString(InAddressAndPort);
	if (InAddressAndPort.IsEmpty())
	{
		StdAddressString = USIOJConvert::StdString(AddressAndPort);
	}

	//Connect to the server on a background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		//Attach the specific connection status events events

		PrivateClient.set_open_listener(sio::client::con_listener([&]() {
			SessionId = USIOJConvert::FStringFromStd(PrivateClient.get_sessionid());
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
			FString Namespace = USIOJConvert::FStringFromStd(nsp);
			UE_LOG(LogTemp, Log, TEXT("SocketIO connected to namespace: %s"), *Namespace);
			OnSocketNamespaceConnected.Broadcast(Namespace);
		}));

		PrivateClient.set_socket_close_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = USIOJConvert::FStringFromStd(nsp);
			UE_LOG(LogTemp, Log, TEXT("SocketIO disconnected from namespace: %s"), *Namespace);
			OnSocketNamespaceDisconnected.Broadcast(USIOJConvert::FStringFromStd(nsp));
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

#pragma endregion Connect

#pragma region Emit

void USocketIOClientComponent::Emit(FString Name, USIOJsonValue* Message, FString Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOJConvert::StdString(Namespace))->emit(
		USIOJConvert::StdString(Name),
		USIOJConvert::ToSIOMessage(Message->GetRootValue()));
}

void USocketIOClientComponent::EmitWithCallBack(FString EventName, USIOJsonValue* Message /*= nullptr*/, FString CallbackFunctionName /*= FString(TEXT(""))*/, UObject* Target /*= nullptr*/, FString Namespace /*= FString(TEXT("/"))*/)
{
	if (!CallbackFunctionName.IsEmpty())
	{
		if (Target == nullptr)
		{
			Target = GetOwner();
		}
		EmitNative(EventName, Message->GetRootValue(), [&, Target, CallbackFunctionName](auto Response)
		{
			//if we have a callback, call it

				//Convert our results into a JSON string that can be decoded on the receiving end, not a perfect workaround...
			FOutputDeviceNull ar;
			const FString command = FString::Printf(TEXT("%s %s"), *CallbackFunctionName, *USIOJConvert::ToJsonString(Response));
			Target->CallFunctionByNameWithArguments(*command, ar, NULL, true);
		}, Namespace);
	}
	else 
	{
		EmitNative(EventName, Message->GetRootValue(),nullptr,Namespace);
	}
}

void USocketIOClientComponent::EmitNative(FString EventName, const TSharedPtr<FJsonValue>& Message /*= nullptr*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, FString Namespace /*= FString(TEXT("/"))*/)
{
	const auto SafeCallback = CallbackFunction;
	EmitRawWithCallback(
		EventName,
		USIOJConvert::ToSIOMessage(Message),
		[&, SafeCallback](const sio::message::list& MessageList)
	{
		TArray<TSharedPtr<FJsonValue>> ValueArray;

		for (int i = 0; i < MessageList.size(); i++)
		{
			auto ItemMessagePtr = MessageList[i];
			ValueArray.Add(USIOJConvert::ToJsonValue(ItemMessagePtr));
		}

		SafeCallback(ValueArray);
	}, Namespace);
}

void USocketIOClientComponent::EmitRawWithCallback(FString Name, const sio::message::list& MessageList, TFunction<void(const sio::message::list&)> ResponseFunction, FString Namespace)
{
	const TFunction<void(const sio::message::list&)> SafeFunction = ResponseFunction;

	PrivateClient.socket(USIOJConvert::StdString(Namespace))->emit(
		USIOJConvert::StdString(Name), 
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

void USocketIOClientComponent::EmitBinary(FString Name, uint8* Data, int32 DataLength, FString Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOJConvert::StdString(Namespace))->emit(USIOJConvert::StdString(Name), std::make_shared<std::string>((char*)Data, DataLength));
}

#pragma endregion Emit

#pragma region OnEvents

void USocketIOClientComponent::BindEvent(FString Event, FString Namespace)
{
	OnRawEvent(Event, [&](const FString& EventName, const sio::message::ptr& RawMessage) {
		USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
		auto Value = USIOJConvert::ToJsonValue(RawMessage);
		NewValue->SetRootValue(Value);
		On.Broadcast(EventName, NewValue);

	}, Namespace);
}

void USocketIOClientComponent::BindEventToFunction(const FString& EventName, const FString& FunctionName, UObject* Target, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	if (!FunctionName.IsEmpty())
	{
		if (Target == nullptr)
		{
			Target = GetOwner();
		}
		OnNativeEvent(EventName, [&, FunctionName](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			FOutputDeviceNull ar;
			const FString command = FString::Printf(TEXT("%s %s"), *FunctionName, *USIOJConvert::ToJsonString(Message));
			Target->CallFunctionByNameWithArguments(*command, ar, NULL, true);
		}, Namespace);
	}
	else
	{
		//if we forgot our function name, fallback to regular bind event
		BindEvent(EventName, Namespace);
	}
}

void USocketIOClientComponent::OnNativeEvent(FString Event, TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	OnRawEvent(Event, [&](const FString& EventName, const sio::message::ptr& RawMessage) {
		CallbackFunction(EventName, USIOJConvert::ToJsonValue(RawMessage));
	}, Namespace);
}

void USocketIOClientComponent::OnRawEvent(FString Event, TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJConvert::StdString(Namespace))->on(
		USIOJConvert::StdString(Event),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOJConvert::FStringFromStd(name);

		FFunctionGraphTask::CreateAndDispatchWhenReady([&, SafeFunction, SafeName, data]
		{
			SafeFunction(SafeName, data);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	}));
}


void USocketIOClientComponent::OnBinaryEvent(FString Event, TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction, FString Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOJConvert::StdString(Namespace))->on(
		USIOJConvert::StdString(Event),
		sio::socket::event_listener_aux(
			[&, SafeFunction](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
	{
		const FString SafeName = USIOJConvert::FStringFromStd(name);

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

#pragma endregion OnEvents