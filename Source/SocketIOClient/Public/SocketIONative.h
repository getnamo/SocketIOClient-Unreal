// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "sio_client.h"
#include "SIOJsonObject.h"
#include "SIOJsonValue.h"
#include "SIOJConvert.h"
#include "SIOMessageConvert.h"
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ESIOConnectionCloseReason
{
	CLOSE_REASON_NORMAL,
	CLOSE_REASON_DROP
};

UENUM(BlueprintType)
enum ESIOThreadOverrideOption
{
	USE_DEFAULT,
	USE_GAME_THREAD,
	USE_NETWORK_THREAD
};

//Used in early (pre-connection) binds and maintaining map if re-setting connection type
struct FSIOBoundEvent
{
	TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> Function;
	FString Namespace;
	ESIOThreadOverrideOption ThreadOption;

	FSIOBoundEvent()
	{
		Namespace = TEXT("/");
		ThreadOption = USE_DEFAULT;
	}
};

class SOCKETIOCLIENT_API FSocketIONative
{
public:
	/** By default TLS verification is off. TLS mode will be set by URL on connect.*/
	FSocketIONative(const bool bForceTLSMode = false, const bool bShouldVerifyTLSCertificate = false);

	//Native Callbacks
	TFunction<void(const FString& SocketId, const FString& SessionId)> OnConnectedCallback;					//TFunction<void(const FString& SessionId)>
	TFunction<void(const ESIOConnectionCloseReason Reason)> OnDisconnectedCallback;	//TFunction<void(const ESIOConnectionCloseReason Reason)>
	TFunction<void(const FString& Namespace)> OnNamespaceConnectedCallback;			//TFunction<void(const FString& Namespace)>
	TFunction<void(const FString& Namespace)> OnNamespaceDisconnectedCallback;		//TFunction<void(const FString& Namespace)>
	TFunction<void(const uint32 AttemptCount, const uint32 DelayInMs)> OnReconnectionCallback;
	TFunction<void()> OnFailCallback;			

	//Map for all native functions bound to this socket
	TMap<FString, FSIOBoundEvent> EventFunctionMap;

	/** Address& Port, Path, Query, Headers, & Auth message */
	FSIOConnectParams URLParams;

	/** The number of attempts before giving up. 0 = infinity. Set before connecting*/
	uint32 MaxReconnectionAttempts;

	/** in milliseconds, default is 5000 */
	uint32 ReconnectionDelay;

	/** Whether this instance has a currently live connection to the server. */
	bool bIsConnected;

	/** When connected this session id will be valid and contain a unique Id. */
	FString SessionId;

	/** Each new connection is assigned a random 20-characters identifier. This identifier is synced with the value on the client-side. */
	FString SocketId;

	//This will remain valid even after we disconnect. Replaced on disconnect.
	FString LastSessionId;

	/** If set to true, each state change callback will log to console*/
	bool VerboseLog;

	/** If true, all callbacks and events will occur on game thread. Default true. */
	bool bCallbackOnGameThread;

	/** Set true if connection currently configured for TLS */
	bool bIsSetupForTLS;

	/** If at initialization forcing is set true, it will use TLS despite URL used */
	bool bForceTLSUse;

	/** If true will attempt to verify certificate (NB: this currently doesn't work) */
	bool bUsingTLSCertVerification;

	/** If true all events are unbound on disconnect */
	bool bUnbindEventsOnDisconnect;

	/**
	* Connect to a socket.io server, optional method if auto-connect is set to true.
	* Overloaded function where you don't care about query and headers
	*
	* @param AddressAndPort	the address in URL format with port
	*
	*/
	void Connect(const FString& InAddressAndPort = TEXT(""));

	/**
	* Connect to a socket.io server, optional method if auto-connect is set to true.
	* Query and headers are defined by a {'stringKey':'stringValue'} SIOJson Object
	*
	* @param AddressAndPort	the address in URL format with port
	* @param Query http query as a SIOJsonObject with string keys and values
	* @param Headers http header as a SIOJsonObject with string keys and values
	*
	*/
	void Connect(const FSIOConnectParams& ConnectParams);

	/** 
	* Join a desired namespace. Keep in mind that emitting to a namespace will auto-join it
	*/
	void JoinNamespace(const FString& Namespace);

	/**
	* Leave a specified namespace.
	*/
	void LeaveNamespace(const FString& Namespace);

	/**
	* Disconnect from current socket.io server, optional method.
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	void Disconnect();

	void SyncDisconnect();

	void ClearAllCallbacks();

	/**
	* Emit an event with a JsonValue message
	*
	* @param EventName				Event name
	* @param Message				FJsonValue
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		const TSharedPtr<FJsonValue>& Message = nullptr,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with a Json Object message
	*
	* @param EventName				Event name
	* @param ObjectMessage			FJsonObject
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		const TSharedPtr<FJsonObject>& ObjectMessage = nullptr,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with a string message
	*
	* @param EventName				Event name
	* @param StringMessage			Message in string format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		const FString& StringMessage = FString(),
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));


//flexible type allowing TEXT() passed as second param for overloaded emit
#if !defined(SIO_TEXT_TYPE)
	#if PLATFORM_TCHAR_IS_CHAR16
		#define SIO_TEXT_TYPE char16_t*
	#else
		#define SIO_TEXT_TYPE wchar_t*
	#endif
#endif

	/**
	* (Overloaded) Emit an event with a string literal message
	*
	* @param EventName				Event name
	* @param StringMessage			Message in string format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		const SIO_TEXT_TYPE StringMessage = TEXT(""),
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with a number (double) message
	*
	* @param EventName				Event name
	* @param NumberMessage			Message in double format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		double NumberMessage,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with a bool message
	*
	* @param EventName				Event name
	* @param BooleanMessage			Message in bool format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		bool BooleanMessage,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with a binary message
	*
	* @param EventName				Event name
	* @param BinaryMessage			Message in an TArray of uint8
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit
	(const FString& EventName,
		const TArray<uint8>& BinaryMessage,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with an array message
	*
	* @param EventName				Event name
	* @param ArrayMessage			Message in an TArray of FJsonValues
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		const TArray<TSharedPtr<FJsonValue>>& ArrayMessage,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event with an UStruct message
	*
	* @param EventName				Event name
	* @param Struct					UStruct type usually obtained via e.g. FMyStructType::StaticStruct()
	* @param StructPtr				Pointer to the actual struct memory e.g. &MyStruct
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		UStruct* Struct,
		const void* StructPtr,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* (Overloaded) Emit an event without a message
	*
	* @param EventName				Event name
	* @param Struct					UStruct type usually obtained via e.g. FMyStructType::StaticStruct()
	* @param StructPtr				Pointer to the actual struct memory e.g. &MyStruct
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void Emit(
		const FString& EventName,
		TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* Emit a raw sio::message event
	*
	* @param EventName				Event name
	* @param MessageList			Message in sio::message::list format
	* @param CallbackFunction		Optional callback TFunction with raw signature
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitRaw(
		const FString& EventName,
		const sio::message::list& MessageList = nullptr,
		TFunction<void(const sio::message::list&)> CallbackFunction = nullptr,
		const FString& Namespace = TEXT("/"));

	/**
	* Emit an optimized binary message
	*
	* @param EventName				Event name
	* @param Data					Buffer Pointer
	* @param DataLength				Buffer size
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitRawBinary(
		const FString& EventName,
		uint8* Data,
		int32 DataLength,
		const FString& Namespace = TEXT("/"));


	/**
	* Call function callback on receiving socket event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, JSONValue
	* @param Namespace	Optional namespace, defaults to default namespace
	* @param CallbackThread Override default bCallbackOnGameThread option to specified option for this event
	*/
	void OnEvent(
		const FString& EventName,
		TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction,
		const FString& Namespace = TEXT("/"),
		ESIOThreadOverrideOption CallbackThread = USE_DEFAULT);

	/**
	* Call function callback on receiving raw event. C++ only. 
	* NB: Does not get added to FSocketIONative event map (use OnEvent)!
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, raw flavor
	* @param Namespace	Optional namespace, defaults to default namespace
	* @param CallbackThread Override default bCallbackOnGameThread option to specified option for this event
	*/
	void OnRawEvent(
		const FString& EventName,
		TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction,
		const FString& Namespace = TEXT("/"),
		ESIOThreadOverrideOption CallbackThread = USE_DEFAULT);

	/**
	* Call function callback on receiving binary event. C++ only.
	* NB: Does not get added to FSocketIONative event map (use OnEvent)!
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, raw flavor
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnRawBinaryEvent(
		const FString& EventName,
		TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction,
		const FString& Namespace = TEXT("/"));

	/**
	* Unbinds currently bound callback from given event.
	*
	* @param EventName	Event name
	*/
	void UnbindEvent(const FString& EventName, const FString& Namespace = TEXT("/"));

protected:

	/** On disconnect or mode change bound events become invalid */
	void ClearInternalCallbacks();

	/** Linkup PrivateClient callbacks to FSocketIONative */
	void SetupInternalCallbacks();

	void RebindCurrentEventMap();

	/** Checks for https prepend */
	bool IsTLSURL(const FString& URL);

	/** If non-matching mode, this will:
	- close the connection
	- clear and re-link internal callbacks
	- re-construct PrivateClient in the correct mode
	NB: URL preference overwritten if bForceTLSUse is true*/
	void SyncPrivateClientToTLSMode(const FString& URL);

	void InitPrivateClient(const bool bShouldUseTlsLibraries = false, const bool bShouldVerifyTLSCertificate = false);

	TSharedPtr<sio::client> PrivateClient;
};
