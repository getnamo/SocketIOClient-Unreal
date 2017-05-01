// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOClientComponent.h"
#include "SIOLambdaRunnable.h"
#include "SIOJConvert.h"

USocketIOClientComponent::USocketIOClientComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	bShouldAutoConnect = true;
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	NativeClient = nullptr;
	AddressAndPort = FString(TEXT("http://localhost:3000"));	//default to 127.0.0.1
	SessionId = FString(TEXT("invalid"));
}

void USocketIOClientComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (!NativeClient.IsValid())
	{
		UE_LOG(SocketIOLog, Log, TEXT("new FSocketIONative"));
		NativeClient = MakeShareable(new FSocketIONative);
	}
	else
	{
		//Ensure it's closed
		SyncDisconnect();
	}

	if (bShouldAutoConnect)
	{
		Connect(AddressAndPort);	//connect to default address
	}
}

void USocketIOClientComponent::UninitializeComponent()
{
	SyncDisconnect();

	UE_LOG(SocketIOLog, Log, TEXT("UninitializeComponent() call"));

	/*TSharedPtr<sio::client>& ClientToDisconnect = PrivateClient;
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([ClientToDisconnect]
	{
		//Only delete valid pointers
		if (ClientToDisconnect.IsValid())
		{
			UE_LOG(SocketIOLog, Log, TEXT("sync closing..."));
			ClientToDisconnect->sync_close();
		}
	});*/

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

void USocketIOClientComponent::Connect(const FString& InAddressAndPort, USIOJsonObject* Query /*= nullptr*/, USIOJsonObject* Headers /*= nullptr*/)
{
	TSharedPtr<FJsonObject> QueryFJson;
	TSharedPtr<FJsonObject> HeadersFJson;

	if (Query != nullptr)
	{
		QueryFJson = Query->GetRootObject();
	}

	if (Headers != nullptr)
	{
		HeadersFJson = Headers->GetRootObject();
	}
	
	ConnectNative(InAddressAndPort, QueryFJson, HeadersFJson);
}

void USocketIOClientComponent::ConnectNative(const FString& InAddressAndPort, const TSharedPtr<FJsonObject>& Query /*= nullptr*/, const TSharedPtr<FJsonObject>& Headers /*= nullptr*/)
{
	//Set native callback functions
	NativeClient->OnConnectedCallback = [this](const FString& SessionId)
	{
		OnConnected.Broadcast(SessionId);
	};

	NativeClient->OnDisconnectedCallback = [this](const ESIOConnectionCloseReason Reason)
	{
		OnDisconnected.Broadcast(Reason);
	};

	NativeClient->OnNamespaceConnectedCallback = [this](const FString& Namespace)
	{
		OnSocketNamespaceConnected.Broadcast(Namespace);
	};

	NativeClient->OnNamespaceDisconnectedCallback = [this](const FString& Namespace)
	{
		OnSocketNamespaceDisconnected.Broadcast(Namespace);
	};

	NativeClient->OnFailCallback = [this]()
	{
		OnFail.Broadcast();
	};

	NativeClient->Connect(InAddressAndPort, Query, Headers);
}

void USocketIOClientComponent::Disconnect()
{
	NativeClient->Disconnect();
}

void USocketIOClientComponent::SyncDisconnect()
{
	NativeClient->SyncDisconnect();
}

#if PLATFORM_WINDOWS
#pragma endregion Connect
#pragma region Emit
#endif

void USocketIOClientComponent::Emit(const FString& EventName, USIOJsonValue* Message, const FString& Namespace /*= FString(TEXT("/"))*/)
{
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

	NativeClient->Emit(EventName, JsonMessage, nullptr, Namespace);
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
	NativeClient->Emit(EventName, Message, CallbackFunction, Namespace);
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

#if PLATFORM_WINDOWS
#pragma endregion Emit
#pragma region OnEvents
#endif

void USocketIOClientComponent::BindEvent(const FString& EventName, const FString& Namespace)
{
	NativeClient->OnRawEvent(EventName, [&](const FString& Event, const sio::message::ptr& RawMessage) {
		USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
		auto Value = USIOMessageConvert::ToJsonValue(RawMessage);
		NewValue->SetRootValue(Value);
		OnEvent.Broadcast(Event, NewValue);

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
	NativeClient->OnEvent(EventName, CallbackFunction, Namespace);
}

#if PLATFORM_WINDOWS
#pragma endregion OnEvents
#endif