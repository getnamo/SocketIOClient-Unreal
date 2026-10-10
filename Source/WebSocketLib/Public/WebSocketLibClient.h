// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"

WEBSOCKETLIB_API DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketLib, Log, All);

/** Settings for one connection, read by FWebSocketLibClient::Connect */
struct FWebSocketLibConnectParams
{
	/** ws:// or wss:// */
	FString Url;

	/** Extra headers for the upgrade request, e.g. Authorization */
	TMap<FString, FString> Headers;

	/** Requested subprotocols (Sec-WebSocket-Protocol) in order of preference */
	TArray<FString> Protocols;

	/** wss only: check the server certificate against the engine's CA bundle and the url's host */
	bool bVerifyTLSCertificate = true;

	/** wss only: extra trusted root certificates in PEM format, e.g. a private CA */
	FString AdditionalCACertificatesPEM;

	/** Largest incoming message, bigger ones close the connection with 1009 */
	int64 MaxMessageSizeBytes = 32000000;
};

/** Callbacks of a connection, all of them run on its network thread */
struct FWebSocketLibCallbacks
{
	/** Handshake done, Protocol is the subprotocol the server picked (empty if none) */
	TFunction<void(const FString& Protocol)> OnOpen;

	/** Connection could not be established. HttpStatus is set if the server refused the upgrade */
	TFunction<void(const FString& Error, int32 HttpStatus)> OnFail;

	/** An open connection closed, or one you closed while it was still connecting */
	TFunction<void(int32 StatusCode, const FString& Reason, bool bWasClean)> OnClose;

	TFunction<void(const FString& Message)> OnText;
	TFunction<void(const TArray<uint8>& Bytes)> OnBinary;
};

/**
 * Plain websocket client on websocketpp/asio. Each Connect() runs on its own network thread
 * and the callbacks run there. Methods can be called from any thread.
 * Connecting again or destroying the client closes the previous connection in the background,
 * without further callbacks.
 */
class WEBSOCKETLIB_API FWebSocketLibClient
{
public:
	FWebSocketLibClient();
	~FWebSocketLibClient();

	FWebSocketLibClient(const FWebSocketLibClient&) = delete;
	FWebSocketLibClient& operator=(const FWebSocketLibClient&) = delete;

	/** Used from the next Connect() on, a running connection keeps the callbacks it started with */
	void SetCallbacks(const FWebSocketLibCallbacks& InCallbacks);

	/** Start connecting. False with OutError if it can't start (e.g. bad url), no callbacks follow then. */
	bool Connect(const FWebSocketLibConnectParams& Params, FString& OutError);

	/** Start the close handshake, or abort a pending connect. OnClose follows. */
	void Close(int32 StatusCode = 1000, const FString& Reason = FString());

	/** Close() and wait for the network thread to finish, at most TimeoutSeconds. Doesn't wait on the network thread itself. */
	void SyncClose(int32 StatusCode = 1000, const FString& Reason = FString(), float TimeoutSeconds = 5.f);

	/** Queue a message, false if not connected */
	bool SendText(const FString& Message);
	bool SendBinary(const uint8* Data, int64 NumBytes);
	bool SendBinary(const TArray<uint8>& Bytes) { return SendBinary(Bytes.GetData(), Bytes.Num()); }

	bool IsConnected() const;

private:
	struct FImpl;
	TUniquePtr<FImpl> Impl;
};
