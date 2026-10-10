// Copyright 2026-current Getnamo. All Rights Reserved

#include "WebSocketClientComponent.h"
#include "WebSocketClientModule.h"

UWebSocketClientComponent::UWebSocketClientComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;

	Url = TEXT("ws://localhost:3000");
	bVerifyTLSCertificate = true;
	bShouldAutoConnect = true;
	bIsConnected = false;
}

void UWebSocketClientComponent::InitializeComponent()
{
	Super::InitializeComponent();
	EnsureNativeClient();
}

void UWebSocketClientComponent::UninitializeComponent()
{
	//The connection closes in the background, without callbacks
	if (NativeClient.IsValid())
	{
		NativeClient->ClearCallbacks();
		NativeClient.Reset();
	}
	bIsConnected = false;

	Super::UninitializeComponent();
}

void UWebSocketClientComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bShouldAutoConnect)
	{
		Connect();
	}
}

void UWebSocketClientComponent::Connect(const FString& InUrl)
{
	EnsureNativeClient();

	if (!InUrl.IsEmpty())
	{
		Url = InUrl;
	}

	//A previous connection closes without callbacks
	bIsConnected = false;
	ConnectedProtocol.Empty();

	NativeClient->Headers = Headers;
	NativeClient->Protocols = Protocols;
	NativeClient->bVerifyTLSCertificate = bVerifyTLSCertificate;
	NativeClient->Connect(Url);
}

void UWebSocketClientComponent::Disconnect(int32 StatusCode, const FString& Reason)
{
	if (NativeClient.IsValid())
	{
		NativeClient->Disconnect(StatusCode, Reason);
	}
}

bool UWebSocketClientComponent::Send(const FString& Message)
{
	return NativeClient.IsValid() && NativeClient->SendText(Message);
}

bool UWebSocketClientComponent::SendBinary(const TArray<uint8>& Bytes)
{
	return NativeClient.IsValid() && NativeClient->SendBinary(Bytes);
}

bool UWebSocketClientComponent::SendJson(USIOJsonValue* Message)
{
	if (!Message)
	{
		UE_LOG(LogWebSocketClient, Warning, TEXT("SendJson called without a message"));
		return false;
	}
	return NativeClient.IsValid() && NativeClient->SendJson(Message->GetRootValue());
}

void UWebSocketClientComponent::EnsureNativeClient()
{
	if (NativeClient.IsValid())
	{
		return;
	}
	NativeClient = MakeShared<FWebSocketNative>();
	SetupCallbacks();
}

void UWebSocketClientComponent::SetupCallbacks()
{
	//Callbacks arrive on the game thread, the component may be gone by then
	TWeakObjectPtr<UWebSocketClientComponent> WeakThis(this);

	NativeClient->OnConnectedCallback = [WeakThis](const FString& Protocol)
	{
		if (UWebSocketClientComponent* Self = WeakThis.Get())
		{
			Self->bIsConnected = true;
			Self->ConnectedProtocol = Protocol;
			Self->OnConnected.Broadcast(Protocol);
		}
	};

	NativeClient->OnDisconnectedCallback = [WeakThis](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		if (UWebSocketClientComponent* Self = WeakThis.Get())
		{
			Self->bIsConnected = false;
			Self->ConnectedProtocol.Empty();
			Self->OnDisconnected.Broadcast(StatusCode, Reason, bWasClean);
		}
	};

	NativeClient->OnErrorCallback = [WeakThis](const FString& Error)
	{
		if (UWebSocketClientComponent* Self = WeakThis.Get())
		{
			UE_LOG(LogWebSocketClient, Warning, TEXT("Connection to %s failed: %s"), *Self->Url, *Error);
			Self->bIsConnected = false;
			Self->OnConnectionError.Broadcast(Error);
		}
	};

	NativeClient->OnMessageCallback = [WeakThis](const FString& Message)
	{
		if (UWebSocketClientComponent* Self = WeakThis.Get())
		{
			Self->OnMessage.Broadcast(Message);

			//Parse only if something listens, OnMessage may have changed that
			if (Self->OnJsonMessage.IsBound())
			{
				if (TSharedPtr<FJsonValue> JsonValue = FWebSocketNative::ParseJson(Message))
				{
					Self->OnJsonMessage.Broadcast(USIOJsonValue::ConstructJsonValue(Self, JsonValue));
				}
			}
		}
	};

	NativeClient->OnBinaryMessageCallback = [WeakThis](const TArray<uint8>& Bytes)
	{
		if (UWebSocketClientComponent* Self = WeakThis.Get())
		{
			Self->OnBinaryMessage.Broadcast(Bytes);
		}
	};
}
