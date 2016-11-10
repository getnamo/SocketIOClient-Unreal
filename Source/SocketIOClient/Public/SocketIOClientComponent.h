#pragma once

#include "sio_client.h"
#include "SIOJsonValue.h"
#include "Components/ActorComponent.h"
#include "SocketIOClientComponent.generated.h"

UENUM(BlueprintType)
enum EMessageTypeFlag
{
	FLAG_INTEGER,
	FLAG_DOUBLE,
	FLAG_STRING,
	FLAG_BINARY,
	FLAG_ARRAY,
	FLAG_OBJECT,
	FLAG_BOOLEAN,
	FLAG_NULL
};

//TODO: convert sio::message to UE struct for more flexible use
USTRUCT()
struct FSIOMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "SocketIO Message Properties")
	TEnumAsByte<EMessageTypeFlag> MessageFlag;

	//Internal UE storage
	FJsonObject Object;
};

UENUM(BlueprintType)
enum EConnectionCloseReason
{
	CLOSE_REASON_NORMAL,
	CLOSE_REASON_DROP
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIOCEventSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIOCSocketEventSignature, FString, Namespace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIOCOpenEventSignature, FString, SessionId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIOCCloseEventSignature, TEnumAsByte<EConnectionCloseReason>, Reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIOCEventJsonSignature, FString, Event, class USIOJsonValue*, MessageJson);

UCLASS(ClassGroup = "Networking", meta = (BlueprintSpawnableComponent))
class SOCKETIOCLIENT_API USocketIOClientComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	//Async events
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCOpenEventSignature OnConnected;

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCCloseEventSignature OnDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCSocketEventSignature OnSocketNamespaceConnected;

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCSocketEventSignature OnSocketNamespaceDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCEventSignature OnFail;

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCEventJsonSignature On;

	//Default properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Properties")
	FString AddressAndPort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Properties")
	bool ShouldAutoConnect;

	UPROPERTY(BlueprintReadWrite, Category = "SocketIO Properties")
	FString SessionId;

	/**
	* Connect to a socket.io server, optional if auto-connect is set
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Connect(FString InAddressAndPort);

	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Disconnect();

	/**
	* Emit an event with a Json message value
	*
	* @param Name		Event name
	* @param Message	SIOJJsonValue
	* @param Namespace	Namespace within socket.io
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Emit(FString EventName, USIOJsonValue* Message = nullptr, FString Namespace = FString(TEXT("/")));


	/**
	* Emit an event with a Json message value
	*
	* @param Name					Event name
	* @param Message				SIOJsonValue
	* @param CallbackFunctionName	Name of the optional callback function with signature (String, SIOJsonValue)
	* @param Target					CallbackFunction target object, typically self where this is called.
	* @param Namespace				Namespace within socket.io
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void EmitWithCallBack(	FString EventName,
							USIOJsonValue* Message = nullptr,
							FString CallbackFunctionName = FString(""),
							UObject* Target = nullptr,
							FString Namespace = FString(TEXT("/")));

	//Emit Json value object with callback. C++ only convenience emit event.
	void EmitNative(FString EventName,
					const TSharedPtr<FJsonValue>& Message = nullptr,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					FString Namespace = FString(TEXT("/")));

	//Raw sio::message emit, only available in C++
	void EmitRawWithCallback(	FString EventName,
								const sio::message::list& MessageList = nullptr,
								TFunction<void(const sio::message::list&)> ResponseFunction = nullptr, 
								FString Namespace = FString(TEXT("/")));

	//Binary data version, only available in C++
	void EmitBinary(FString EventName, uint8* Data, int32 DataLength, FString Namespace = FString(TEXT("/")));
	
	

	/**
	* Bind an event, then respond to it with 'On' multicast delegate
	*
	* @param EventName	Event name
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void BindEvent(FString EventName, FString Namespace = FString(TEXT("/")));


	/**
	* Bind an event to a function with the given name. 
	* Expects a String message signature which can be decoded from JSON into SIOJsonObject
	*
	* @param EventName		Event name
	* @param FunctionName	The function that gets called when the event is received
	* @param Target			Optional, defaults to owner. Change to delegate to another class.
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void BindEventToFunction(	const FString& EventName, 
								const FString& FunctionName, 
								UObject* Target, 
								const FString& Namespace = FString(TEXT("/")));

	/**
	* Call function callback on receiving socket event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, JSONValue
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnNativeEvent(	FString EventName,
						TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction,
						FString Namespace = FString(TEXT("/")));

	/**
	* Call function callback on receiving raw event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, raw flavor
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnRawEvent(FString EventName,
		TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction,
		FString Namespace = FString(TEXT("/")));
	/**
	* Call function callback on receiving binary event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, raw flavor
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnBinaryEvent(FString EventName,
		TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction,
		FString Namespace = FString(TEXT("/")));

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

protected:

	sio::client PrivateClient;
};