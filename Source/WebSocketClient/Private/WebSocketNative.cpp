// Copyright 2026-current Getnamo. All Rights Reserved

#include "WebSocketNative.h"
#include "WebSocketClientModule.h"
#include "WebSocketLibClient.h"
#include "CULambdaRunnable.h"
#include "SIOJConvert.h"
#include "Misc/ScopeLock.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FWebSocketNative::FWebSocketNative()
	: Client(MakeUnique<FWebSocketLibClient>())
{
}

FWebSocketNative::~FWebSocketNative()
{
	//Closes in the background, without callbacks
	Client.Reset();
}

void FWebSocketNative::Connect(const FString& InUrl)
{
	if (!InUrl.IsEmpty())
	{
		Url = InUrl;
	}

	//Weak, a connection never keeps this alive
	TWeakPtr<FWebSocketNative> WeakSelf = AsShared();

	FWebSocketLibCallbacks Callbacks;
	Callbacks.OnOpen = [WeakSelf](const FString& InProtocol)
	{
		if (TSharedPtr<FWebSocketNative> Self = WeakSelf.Pin())
		{
			{
				FScopeLock Guard(&Self->ProtocolLock);
				Self->Protocol = InProtocol;
			}
			Self->Deliver([InProtocol](FWebSocketNative& Native)
			{
				if (Native.OnConnectedCallback)
				{
					Native.OnConnectedCallback(InProtocol);
				}
			});
		}
	};
	Callbacks.OnFail = [WeakSelf](const FString& Error, int32 HttpStatus)
	{
		if (TSharedPtr<FWebSocketNative> Self = WeakSelf.Pin())
		{
			Self->Deliver([Error](FWebSocketNative& Native)
			{
				if (Native.OnErrorCallback)
				{
					Native.OnErrorCallback(Error);
				}
			});
		}
	};
	Callbacks.OnClose = [WeakSelf](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		if (TSharedPtr<FWebSocketNative> Self = WeakSelf.Pin())
		{
			Self->Deliver([StatusCode, Reason, bWasClean](FWebSocketNative& Native)
			{
				if (Native.OnDisconnectedCallback)
				{
					Native.OnDisconnectedCallback(StatusCode, Reason, bWasClean);
				}
			});
		}
	};
	Callbacks.OnText = [WeakSelf](const FString& Message)
	{
		if (TSharedPtr<FWebSocketNative> Self = WeakSelf.Pin())
		{
			Self->Deliver([Message](FWebSocketNative& Native)
			{
				Native.HandleText(Message);
			});
		}
	};
	Callbacks.OnBinary = [WeakSelf](const TArray<uint8>& Bytes)
	{
		if (TSharedPtr<FWebSocketNative> Self = WeakSelf.Pin())
		{
			Self->Deliver([Bytes](FWebSocketNative& Native)
			{
				if (Native.OnBinaryMessageCallback)
				{
					Native.OnBinaryMessageCallback(Bytes);
				}
			});
		}
	};
	Client->SetCallbacks(Callbacks);

	FWebSocketLibConnectParams Params;
	Params.Url = Url;
	Params.Headers = Headers;
	Params.Protocols = Protocols;
	Params.bVerifyTLSCertificate = bVerifyTLSCertificate;
	Params.AdditionalCACertificatesPEM = AdditionalCACertificatesPEM;
	Params.MaxMessageSizeBytes = MaxMessageSizeBytes;

	{
		FScopeLock Guard(&ProtocolLock);
		Protocol.Empty();
	}

	FString Error;
	if (!Client->Connect(Params, Error))
	{
		UE_LOG(LogWebSocketClient, Warning, TEXT("Connect failed: %s"), *Error);
		Deliver([Error](FWebSocketNative& Native)
		{
			if (Native.OnErrorCallback)
			{
				Native.OnErrorCallback(Error);
			}
		});
	}
}

void FWebSocketNative::Disconnect(int32 StatusCode, const FString& Reason)
{
	Client->Close(StatusCode, Reason);
}

void FWebSocketNative::SyncDisconnect(int32 StatusCode, const FString& Reason, float TimeoutSeconds)
{
	Client->SyncClose(StatusCode, Reason, TimeoutSeconds);
}

bool FWebSocketNative::SendText(const FString& Message)
{
	return Client->SendText(Message);
}

bool FWebSocketNative::SendBinary(const TArray<uint8>& Bytes)
{
	return Client->SendBinary(Bytes);
}

bool FWebSocketNative::SendJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return Client->SendText(ToJsonText(JsonValue));
}

bool FWebSocketNative::SendJson(const TSharedPtr<FJsonObject>& JsonObject)
{
	return SendJson(MakeShared<FJsonValueObject>(JsonObject));
}

bool FWebSocketNative::SendStruct(UStruct* Struct, const void* StructPtr)
{
	if (!Struct || !StructPtr)
	{
		return false;
	}
	return SendJson(USIOJConvert::ToJsonObject(Struct, const_cast<void*>(StructPtr)));
}

bool FWebSocketNative::IsConnected() const
{
	return Client->IsConnected();
}

FString FWebSocketNative::GetProtocol() const
{
	FScopeLock Guard(&ProtocolLock);
	return Protocol;
}

void FWebSocketNative::ClearCallbacks()
{
	OnConnectedCallback = nullptr;
	OnDisconnectedCallback = nullptr;
	OnErrorCallback = nullptr;
	OnMessageCallback = nullptr;
	OnBinaryMessageCallback = nullptr;
	OnJsonMessageCallback = nullptr;
}

TSharedPtr<FJsonValue> FWebSocketNative::ParseJson(const FString& Message)
{
	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
	if (!FJsonSerializer::Deserialize(Reader, JsonValue))
	{
		return nullptr;
	}
	return JsonValue;
}

FString FWebSocketNative::ToJsonText(const TSharedPtr<FJsonValue>& JsonValue)
{
	if (!JsonValue.IsValid())
	{
		return TEXT("null");
	}

	FString Text;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Text);
	FJsonSerializer::Serialize(JsonValue, FString(), Writer);
	return Text;
}

void FWebSocketNative::Deliver(TFunction<void(FWebSocketNative&)>&& Callback)
{
	if (!bCallbackOnGameThread)
	{
		Callback(*this);
		return;
	}

	//Always queued, so callbacks keep their order and never run inside the call that caused them
	TWeakPtr<FWebSocketNative> WeakSelf = AsShared();
	FCULambdaRunnable::RunShortLambdaOnGameThread([WeakSelf, Callback = MoveTemp(Callback)]()
	{
		if (TSharedPtr<FWebSocketNative> Self = WeakSelf.Pin())
		{
			Callback(*Self);
		}
	});
}

void FWebSocketNative::HandleText(const FString& Message)
{
	if (OnMessageCallback)
	{
		OnMessageCallback(Message);
	}

	if (OnJsonMessageCallback)
	{
		if (TSharedPtr<FJsonValue> JsonValue = ParseJson(Message))
		{
			OnJsonMessageCallback(JsonValue);
		}
	}
}
