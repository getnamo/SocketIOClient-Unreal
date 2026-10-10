// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SIOJsonValue.h"
#include "WebSocketNative.h"
#include "WebSocketClientComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSCConnectedSignature, FString, Protocol);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWSCDisconnectedSignature, int32, StatusCode, FString, Reason, bool, bWasClean);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSCErrorSignature, FString, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSCMessageSignature, FString, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSCBinaryMessageSignature, const TArray<uint8>&, Bytes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWSCJsonMessageSignature, USIOJsonValue*, Message);

/**
 * Plain websocket client for servers that don't use the socket.io protocol.
 * For socket.io servers use the SocketIOClientComponent instead.
 */
UCLASS(BlueprintType, ClassGroup = "Networking", meta = (BlueprintSpawnableComponent))
class WEBSOCKETCLIENT_API UWebSocketClientComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

	/** Connected. Protocol is the subprotocol the server picked, empty if none */
	UPROPERTY(BlueprintAssignable, Category = "WebSocket Events")
	FWSCConnectedSignature OnConnected;

	/** Connection closed. StatusCode 1006 with bWasClean false means it dropped without a close handshake */
	UPROPERTY(BlueprintAssignable, Category = "WebSocket Events")
	FWSCDisconnectedSignature OnDisconnected;

	/** Couldn't connect, e.g. refused, bad url, handshake rejected or certificate not trusted */
	UPROPERTY(BlueprintAssignable, Category = "WebSocket Events")
	FWSCErrorSignature OnConnectionError;

	/** Text message received */
	UPROPERTY(BlueprintAssignable, Category = "WebSocket Events")
	FWSCMessageSignature OnMessage;

	/** Binary message received */
	UPROPERTY(BlueprintAssignable, Category = "WebSocket Events")
	FWSCBinaryMessageSignature OnBinaryMessage;

	/** Text message that is a JSON object or array, fires after OnMessage. Messages are only parsed while this is bound. */
	UPROPERTY(BlueprintAssignable, Category = "WebSocket Events")
	FWSCJsonMessageSignature OnJsonMessage;

	/** ws:// or wss:// address, e.g. ws://localhost:3000/path */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket Connection Properties")
	FString Url;

	/** Extra headers for the upgrade request, e.g. Authorization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket Connection Properties")
	TMap<FString, FString> Headers;

	/** Requested subprotocols in order of preference, the server picks one */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket Connection Properties")
	TArray<FString> Protocols;

	/** wss only: check the server certificate against the engine's CA bundle and the url's host. Turn off for self-signed development servers. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket Connection Properties")
	bool bVerifyTLSCertificate;

	/** Connect to Url on BeginPlay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WebSocket Connection Properties")
	bool bShouldAutoConnect;

	UPROPERTY(BlueprintReadOnly, Category = "WebSocket Connection Properties")
	bool bIsConnected;

	/** Subprotocol the server picked, empty if none */
	UPROPERTY(BlueprintReadOnly, Category = "WebSocket Connection Properties")
	FString ConnectedProtocol;

	/**
	 * Connect, closing any previous connection.
	 * @param InUrl	ws:// or wss:// address, uses Url if empty
	 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket Functions")
	void Connect(const FString& InUrl = TEXT(""));

	/**
	 * Close the connection, OnDisconnected follows.
	 * @param StatusCode	1000 for a normal close, or an application code from 3000 to 4999
	 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket Functions")
	void Disconnect(int32 StatusCode = 1000, const FString& Reason = TEXT(""));

	/** Send a text message, false if not connected */
	UFUNCTION(BlueprintCallable, Category = "WebSocket Functions")
	bool Send(const FString& Message);

	/** Send a binary message, false if not connected */
	UFUNCTION(BlueprintCallable, Category = "WebSocket Functions")
	bool SendBinary(const TArray<uint8>& Bytes);

	/** Send a JSON value as a text message, false if not connected */
	UFUNCTION(BlueprintCallable, Category = "WebSocket Functions")
	bool SendJson(USIOJsonValue* Message);

	/** The C++ connection behind this component, created on initialize or first connect */
	TSharedPtr<FWebSocketNative> NativeClient;

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void BeginPlay() override;

protected:
	void EnsureNativeClient();
	void SetupCallbacks();
};
