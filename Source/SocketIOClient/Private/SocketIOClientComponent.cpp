
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
	bAsyncQuitDisconnect = true;
	AddressAndPort = FString(TEXT("http://localhost:3000"));	//default to 127.0.0.1
	SessionId = FString(TEXT("invalid"));
}

void USocketIOClientComponent::InitializeComponent()
{
	Super::InitializeComponent();
	{
		FScopeLock lock(&AllocationSection);
		NativeClient = MakeShareable(new FSocketIONative);
	}

}

void USocketIOClientComponent::BeginPlay()
{
	Super::BeginPlay();
	if (bShouldAutoConnect)
	{
		Connect(AddressAndPort);	//connect to default address
	}
}

void USocketIOClientComponent::UninitializeComponent()
{
	//This may lock up so run it on a background thread
	if (bAsyncQuitDisconnect)
	{
		if (bIsConnected)
		{
			FSIOLambdaRunnable::RunLambdaOnBackGroundThread([&]
			{
				FScopeLock lock(&AllocationSection);
				NativeClient = nullptr;
			});
		}
	}
	else
	{
		FScopeLock lock(&AllocationSection);
		NativeClient = nullptr;;
	}

	//UE_LOG(SocketIOLog, Log, TEXT("UninitializeComponent() call"));
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

	//Check function signature
	TFieldIterator<UProperty> Iterator(Function);

	TArray<UProperty*> Properties;
	while (Iterator && (Iterator->PropertyFlags & CPF_Parm))
	{
		UProperty* Prop = *Iterator;
		Properties.Add(Prop);
		++Iterator;
	}

	auto ResponseJsonValue = USIOJConvert::ToSIOJsonValue(Response);

	bool bResponseNumNotZero = Response.Num() > 0;
	bool bNoFunctionParams = Properties.Num() == 0;
	bool bNullResponse = ResponseJsonValue->IsNull();

	if (bNullResponse && bNoFunctionParams)
	{
		Target->ProcessEvent(Function, nullptr);
		return true;
	}
	else if (bResponseNumNotZero)
	{
		//function has too few params
		if (bNoFunctionParams)
		{
			UE_LOG(SocketIOLog, Warning, TEXT("CallFunctionByNameWithArguments: Function '%s' has too few parameters, callback parameters ignored : <%s>"), *FunctionName, *ResponseJsonValue->EncodeJson());
			Target->ProcessEvent(Function, nullptr);
			return true;
		}
		struct FDynamicArgs
		{
			void* Arg01 = nullptr;
			USIOJsonValue* Arg02 = nullptr;
		};
		//create the container
		FDynamicArgs Args = FDynamicArgs();

		//add the full response array as second param
		Args.Arg02 = ResponseJsonValue;
		const FString& FirstParam = Properties[0]->GetCPPType();
		auto FirstFJsonValue = Response[0];

		//Is first param...
		//SIOJsonValue?
		if (FirstParam.Equals("USIOJsonValue*"))
		{
			//convenience wrapper, response is a single object
			USIOJsonValue* Value = NewObject<USIOJsonValue>();
			Value->SetRootValue(FirstFJsonValue);
			Args.Arg01 = Value;
			Target->ProcessEvent(Function, &Args);
			return true;
		}
		//SIOJsonObject?
		else if (FirstParam.Equals("USIOJsonObject*"))
		{
			//convenience wrapper, response is a single object
			USIOJsonObject* ObjectValue = NewObject<USIOJsonObject>();
			ObjectValue->SetRootObject(FirstFJsonValue->AsObject());
			Args.Arg01 = ObjectValue;
			Target->ProcessEvent(Function, &Args);
			return true;
		}
		//String?
		else if (FirstParam.Equals("FString"))
		{
			FString	StringValue = USIOJConvert::ToJsonString(FirstFJsonValue);
			
			Target->ProcessEvent(Function, &StringValue);
			return true;
		}
		//Float?
		else if (FirstParam.Equals("float"))
		{
			float NumberValue = (float)FirstFJsonValue->AsNumber();
			Target->ProcessEvent(Function, &NumberValue);
			return true;
		}
		//Int?
		else if (FirstParam.Equals("int32"))
		{
			int NumberValue = (int)FirstFJsonValue->AsNumber();
			Target->ProcessEvent(Function, &NumberValue);
			return true;
		}
		//bool?
		else if (FirstParam.Equals("bool"))
		{
			bool BoolValue = FirstFJsonValue->AsBool();
			Target->ProcessEvent(Function, &BoolValue);
			return true;
		}
		//array?
		else if (FirstParam.Equals("TArray"))
		{
			UArrayProperty* ArrayProp = Cast<UArrayProperty>(Properties[0]);

			FString Inner;
			ArrayProp->GetCPPMacroType(Inner);

			//byte array is the only supported version
			if (Inner.Equals("uint8"))
			{
				TArray<uint8> Bytes = ResponseJsonValue->AsArray()[0]->AsBinary();
				Target->ProcessEvent(Function, &Bytes);
				return true;
			}
		}
	}

	UE_LOG(SocketIOLog, Warning, TEXT("CallFunctionByNameWithArguments: Function '%s' signature not supported expected <%s>"), *FunctionName, *ResponseJsonValue->EncodeJson());
	return false;
}

bool USocketIOClientComponent::CallBPFunctionWithMessage(UObject* Target, const FString& FunctionName, TSharedPtr<FJsonValue> Message)
{
	TArray<TSharedPtr<FJsonValue>> Response;
	Response.Add(Message);

	return CallBPFunctionWithResponse(Target, FunctionName, Response);
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
	NativeClient->OnConnectedCallback = [this](const FString& InSessionId)
	{
		FSIOLambdaRunnable::RunShortLambdaOnGameThread([this, InSessionId]
		{
			if (this)
			{
				bIsConnected = true;
				SessionId = InSessionId;
				OnConnected.Broadcast(SessionId);
			}
		});
	};
	const FSIOCCloseEventSignature OnDisconnectedSafe = OnDisconnected;

	NativeClient->OnDisconnectedCallback = [OnDisconnectedSafe, this](const ESIOConnectionCloseReason Reason)
	{
		FSIOLambdaRunnable::RunShortLambdaOnGameThread([OnDisconnectedSafe, this, Reason]
		{
			if (this && OnDisconnectedSafe.IsBound())
			{
				bIsConnected = false;
				OnDisconnectedSafe.Broadcast(Reason);
			}
		});
	};

	NativeClient->OnNamespaceConnectedCallback = [this](const FString& Namespace)
	{
		FSIOLambdaRunnable::RunShortLambdaOnGameThread([this, Namespace]
		{
			if (this)
			{
				OnSocketNamespaceConnected.Broadcast(Namespace);
			}
		});
	};

	const FSIOCSocketEventSignature OnSocketNamespaceDisconnectedSafe = OnSocketNamespaceDisconnected;

	NativeClient->OnNamespaceDisconnectedCallback = [this, OnSocketNamespaceDisconnectedSafe](const FString& Namespace)
	{
		FSIOLambdaRunnable::RunShortLambdaOnGameThread([OnSocketNamespaceDisconnectedSafe, this, Namespace]
		{
			if (this && OnSocketNamespaceDisconnectedSafe.IsBound())
			{
				OnSocketNamespaceDisconnectedSafe.Broadcast(Namespace);
			}
		});
	};

	NativeClient->OnFailCallback = [this]()
	{
		FSIOLambdaRunnable::RunShortLambdaOnGameThread([this]
		{
			OnFail.Broadcast();
		});
	};

	{
		NativeClient->Connect(InAddressAndPort, Query, Headers);
	}
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