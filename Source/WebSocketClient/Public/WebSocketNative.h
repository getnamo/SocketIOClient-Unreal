// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

class FWebSocketLibClient;

/**
 * Plain websocket connection for C++ (no socket.io protocol). Create it with MakeShared.
 * Settings are read on Connect(). Callbacks run on the game thread unless bCallbackOnGameThread is false.
 * Destroying it closes the connection in the background without further callbacks.
 */
class WEBSOCKETCLIENT_API FWebSocketNative : public TSharedFromThis<FWebSocketNative>
{
public:
	FWebSocketNative();
	~FWebSocketNative();

	/** ws:// or wss:// address, used when Connect() isn't given one */
	FString Url;

	/** Extra headers for the upgrade request, e.g. Authorization */
	TMap<FString, FString> Headers;

	/** Requested subprotocols in order of preference, the server picks one */
	TArray<FString> Protocols;

	/** wss only: check the server certificate against the engine's CA bundle and the url's host */
	bool bVerifyTLSCertificate = true;

	/** wss only: extra trusted root certificates in PEM format, e.g. a private CA */
	FString AdditionalCACertificatesPEM;

	/** Largest incoming message, bigger ones close the connection with 1009 */
	int64 MaxMessageSizeBytes = 32000000;

	/** If false, callbacks run on the network thread. Set them before connecting then. */
	bool bCallbackOnGameThread = true;

	/** Connect, closing any previous connection without callbacks. Uses Url if InUrl is empty. */
	void Connect(const FString& InUrl = FString());

	/** Close with a status code (1000 or 3000-4999) and reason, OnDisconnected follows */
	void Disconnect(int32 StatusCode = 1000, const FString& Reason = FString());

	/** Disconnect and wait for the connection to close, at most TimeoutSeconds */
	void SyncDisconnect(int32 StatusCode = 1000, const FString& Reason = FString(), float TimeoutSeconds = 5.f);

	/** Queue a message, false if not connected */
	bool SendText(const FString& Message);
	bool SendBinary(const TArray<uint8>& Bytes);
	bool SendJson(const TSharedPtr<FJsonValue>& JsonValue);
	bool SendJson(const TSharedPtr<FJsonObject>& JsonObject);

	/** Send a struct as a JSON object text message */
	bool SendStruct(UStruct* Struct, const void* StructPtr);

	template<typename StructType>
	bool SendStruct(const StructType& Struct)
	{
		return SendStruct(StructType::StaticStruct(), &Struct);
	}

	bool IsConnected() const;

	/** Subprotocol the server picked, empty if none */
	FString GetProtocol() const;

	TFunction<void(const FString& Protocol)> OnConnectedCallback;
	TFunction<void(int32 StatusCode, const FString& Reason, bool bWasClean)> OnDisconnectedCallback;
	TFunction<void(const FString& Error)> OnErrorCallback;
	TFunction<void(const FString& Message)> OnMessageCallback;
	TFunction<void(const TArray<uint8>& Bytes)> OnBinaryMessageCallback;

	/** Text messages that are a JSON object or array, after OnMessageCallback. Only parsed while this is set. */
	TFunction<void(const TSharedPtr<FJsonValue>& JsonValue)> OnJsonMessageCallback;

	void ClearCallbacks();

	/** Parse a text message, null unless it is a JSON object or array */
	static TSharedPtr<FJsonValue> ParseJson(const FString& Message);

	/** Encode a value as JSON text */
	static FString ToJsonText(const TSharedPtr<FJsonValue>& JsonValue);

private:
	void Deliver(TFunction<void(FWebSocketNative&)>&& Callback);
	void HandleText(const FString& Message);

	TUniquePtr<FWebSocketLibClient> Client;

	mutable FCriticalSection ProtocolLock;
	FString Protocol;
};
