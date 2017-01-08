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
	SyncDisconnect();
	Super::UninitializeComponent();
}

bool USocketIOClientComponent::CallBPFunctionWithResponse(UObject* Target, const FString& FunctionName, TArray<TSharedPtr<FJsonValue>> Response)
{
	UFunction* Function = Target->FindFunction(FName(*FunctionName));
	if (nullptr == Function)
	{
		UE_LOG(SocketIOLog, Warning, TEXT("CallFunctionByNameWithArguments: Function not found '%s'"), *FunctionName);
		return false;
	}

	auto ResponseJsonValue = USIOJConvert::ToSIOJsonValue(Response);

	struct FDynamicArgs
	{
		USIOJsonValue* Arg01 = NULL;
		USIOJsonValue* Arg02 = NULL;
	};

	//create the container
	FDynamicArgs Args = FDynamicArgs();

	//convenience wrapper, response is a single object
	Args.Arg01 = NewObject<USIOJsonValue>();	
	Args.Arg01->SetRootValue(Response[0]);

	//add the full response array as second param
	Args.Arg02 = ResponseJsonValue;

	//Call the function
	Target->ProcessEvent(Function, &Args);

	return true;
}

bool USocketIOClientComponent::CallBPFunctionWithMessage(UObject* Target, const FString& FunctionName, TSharedPtr<FJsonValue> Message)
{
	UFunction* Function = Target->FindFunction(FName(*FunctionName));
	if (nullptr == Function)
	{
		UE_LOG(SocketIOLog, Warning, TEXT("CallFunctionByNameWithArguments: Function not found '%s'"), *FunctionName);
		return false;
	}

	struct FDynamicArgs
	{
		USIOJsonValue* Arg01 = NULL;
	};
	FDynamicArgs Args = FDynamicArgs();

	Args.Arg01 = NewObject<USIOJsonValue>();
	Args.Arg01->SetRootValue(Message);

	//Call the function
	Target->ProcessEvent(Function, &Args);

	return true;
}

#if PLATFORM_WINDOWS
#pragma region Connect
#endif

void USocketIOClientComponent::Connect(const FString& InAddressAndPort)
{
	std::string StdAddressString = USIOMessageConvert::StdString(InAddressAndPort);
	if (InAddressAndPort.IsEmpty())
	{
		StdAddressString = USIOMessageConvert::StdString(AddressAndPort);
	}

	//Connect to the server on a background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		//Attach the specific connection status events events

		PrivateClient.set_open_listener(sio::client::con_listener([&]() {
			SessionId = USIOMessageConvert::FStringFromStd(PrivateClient.get_sessionid());
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO Connected with session: %s"), *SessionId);
			OnConnected.Broadcast(SessionId);
		}));

		PrivateClient.set_close_listener(sio::client::close_listener([&](sio::client::close_reason const& reason)
		{
			SessionId = FString(TEXT("invalid"));
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO Disconnected"));
			OnDisconnected.Broadcast((ESIOConnectionCloseReason)reason);
		}));

		PrivateClient.set_socket_open_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = USIOMessageConvert::FStringFromStd(nsp);
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO connected to namespace: %s"), *Namespace);
			OnSocketNamespaceConnected.Broadcast(Namespace);
		}));

		PrivateClient.set_socket_close_listener(sio::client::socket_listener([&](std::string const& nsp)
		{
			FString Namespace = USIOMessageConvert::FStringFromStd(nsp);
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO disconnected from namespace: %s"), *Namespace);
			OnSocketNamespaceDisconnected.Broadcast(USIOMessageConvert::FStringFromStd(nsp));
		}));

		PrivateClient.set_fail_listener(sio::client::con_listener([&]()
		{
			UE_LOG(SocketIOLog, Log, TEXT("SocketIO failed to connect."));
			OnFail.Broadcast();
		}));
		
		PrivateClient.connect(StdAddressString);
	});
}


void USocketIOClientComponent::Disconnect()
{
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
	{
		SyncDisconnect();
	});
}

void USocketIOClientComponent::SyncDisconnect()
{
	if (PrivateClient.opened())
	{
		PrivateClient.socket()->off_all();
		PrivateClient.socket()->off_error();
		PrivateClient.close();
	}
}

#if PLATFORM_WINDOWS
#pragma endregion Connect
#pragma region Emit
#endif

void USocketIOClientComponent::Emit(const FString& EventName, USIOJsonValue* Message, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOMessageConvert::StdString(Namespace))->emit(
		USIOMessageConvert::StdString(EventName),
		USIOMessageConvert::ToSIOMessage(Message->GetRootValue()));
}

void USocketIOClientComponent::EmitWithCallBack(const FString& EventName, USIOJsonValue* Message /*= nullptr*/, const FString& CallbackFunctionName /*= FString(TEXT(""))*/, UObject* Target /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	if (!CallbackFunctionName.IsEmpty())
	{
		if (Target == nullptr)
		{
			Target = GetOwner();
		}

		//Set the message is not null
		TSharedPtr<FJsonValue> JsonMessage = nullptr;
		if (Message != nullptr)
		{
			JsonMessage = Message->GetRootValue();
		}
		else
		{
			JsonMessage = MakeShareable(new FJsonValueNull);
		}

		EmitNative(EventName, JsonMessage, [&, Target, CallbackFunctionName, this](const TArray<TSharedPtr<FJsonValue>>& Response)
		{
			CallBPFunctionWithResponse(Target, CallbackFunctionName, Response);
		}, Namespace);
	}
	else 
	{
		EmitNative(EventName, Message->GetRootValue(),nullptr,Namespace);
	}
}

void USocketIOClientComponent::EmitNative(const FString& EventName, const TSharedPtr<FJsonValue>& Message /*= nullptr*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
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

void USocketIOClientComponent::EmitNative(const FString& EventName, const TSharedPtr<FJsonObject>& ObjectMessage /*= nullptr*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, MakeShareable(new FJsonValueObject(ObjectMessage)), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitNative(const FString& EventName, const FString& StringMessage /*= FString()*/, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, MakeShareable(new FJsonValueString(StringMessage)), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitNative(const FString& EventName, double NumberMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, MakeShareable(new FJsonValueNumber(NumberMessage)), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitNative(const FString& EventName, const TArray<uint8>& BinaryMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, MakeShareable(new FJsonValueBinary(BinaryMessage)), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitNative(const FString& EventName, const TArray<TSharedPtr<FJsonValue>>& ArrayMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, MakeShareable(new FJsonValueArray(ArrayMessage)), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitNative(const FString& EventName, bool BooleanMessage, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, MakeShareable(new FJsonValueBoolean(BooleanMessage)), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitNative(const FString& EventName, UStruct* Struct, const void* StructPtr, TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction /*= nullptr*/, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	EmitNative(EventName, USIOJConvert::ToJsonObject(Struct, (void*)StructPtr), CallbackFunction, Namespace);
}

void USocketIOClientComponent::EmitRaw(const FString& EventName, const sio::message::list& MessageList, TFunction<void(const sio::message::list&)> ResponseFunction, const FString& Namespace)
{
	const TFunction<void(const sio::message::list&)> SafeFunction = ResponseFunction;

	PrivateClient.socket(USIOMessageConvert::StdString(Namespace))->emit(
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

void USocketIOClientComponent::EmitRawBinary(const FString& EventName, uint8* Data, int32 DataLength, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	PrivateClient.socket(USIOMessageConvert::StdString(Namespace))->emit(USIOMessageConvert::StdString(EventName), std::make_shared<std::string>((char*)Data, DataLength));
}

#if PLATFORM_WINDOWS
#pragma endregion Emit
#pragma region OnEvents
#endif

void USocketIOClientComponent::BindEvent(const FString& EventName, const FString& Namespace)
{
	OnRawEvent(EventName, [&](const FString& Event, const sio::message::ptr& RawMessage) {
		USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
		auto Value = USIOMessageConvert::ToJsonValue(RawMessage);
		NewValue->SetRootValue(Value);
		On.Broadcast(Event, NewValue);

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
		OnNativeEvent(EventName, [&, FunctionName, Target](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			CallBPFunctionWithMessage(Target, FunctionName, Message);
		}, Namespace);
	}
	else
	{
		//if we forgot our function name, fallback to regular bind event
		BindEvent(EventName, Namespace);
	}
}

void USocketIOClientComponent::OnNativeEvent(const FString& EventName, TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	OnRawEvent(EventName, [&, CallbackFunction](const FString& Event, const sio::message::ptr& RawMessage) {
		CallbackFunction(Event, USIOMessageConvert::ToJsonValue(RawMessage));
	}, Namespace);
}

void USocketIOClientComponent::OnRawEvent(const FString& EventName, TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const sio::message::ptr&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOMessageConvert::StdString(Namespace))->on(
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


void USocketIOClientComponent::OnBinaryEvent(const FString& EventName, TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction, const FString& Namespace /*= FString(TEXT("/"))*/)
{
	const TFunction< void(const FString&, const TArray<uint8>&)> SafeFunction = CallbackFunction;	//copy the function so it remains in context

	PrivateClient.socket(USIOMessageConvert::StdString(Namespace))->on(
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

#if PLATFORM_WINDOWS
#pragma endregion OnEvents
#endif