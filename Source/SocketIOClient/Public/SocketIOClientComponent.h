#pragma once

#include "sio_client.h"
#include "SIOJsonObject.h"
#include "SIOJsonValue.h"
#include "SIOJConvert.h"
//#include "SIOLambdaRunnable.h"
#include "Components/ActorComponent.h"
#include "SocketIOClientComponent.generated.h"

UENUM(BlueprintType)
enum ESIOMessageTypeFlag
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
	TEnumAsByte<ESIOMessageTypeFlag> MessageFlag;

	//Internal UE storage
	FJsonObject Object;
};

UENUM(BlueprintType)
enum ESIOConnectionCloseReason
{
	CLOSE_REASON_NORMAL,
	CLOSE_REASON_DROP
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIOCEventSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIOCSocketEventSignature, FString, Namespace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIOCOpenEventSignature, FString, SessionId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIOCCloseEventSignature, TEnumAsByte<ESIOConnectionCloseReason>, Reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIOCEventJsonSignature, FString, Event, class USIOJsonValue*, MessageJson);

UCLASS(ClassGroup = "Networking", meta = (BlueprintSpawnableComponent))
class SOCKETIOCLIENT_API USocketIOClientComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	//Async events

	/** Event received on socket.io connection established. */
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCOpenEventSignature OnConnected;

	/** Event received on socket.io connection disconnected. */
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCCloseEventSignature OnDisconnected;

	/** Event received on having joined namespace. */
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCSocketEventSignature OnSocketNamespaceConnected;

	/** Event received on having left namespace. */
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCSocketEventSignature OnSocketNamespaceDisconnected;

	/** Event received on connection failure. */
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCEventSignature OnFail;

	/** On bound event received. */
	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCEventJsonSignature On;

	/** Default connection address string in form e.g. http://localhost:80. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Properties")
	FString AddressAndPort;

	/** If true will auto-connect on begin play to address specified in AddressAndPort. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SocketIO Properties")
	bool bShouldAutoConnect;

	UPROPERTY(BlueprintReadOnly, Category = "SocketIO Properties")
	bool bIsConnected;

	/** When connected this session id will be valid and contain a unique Id. */
	UPROPERTY(BlueprintReadWrite, Category = "SocketIO Properties")
	FString SessionId;

	/**
	* Connect to a socket.io server, optional method if auto-connect is set to true.
	* Query and headers are defined by a {'stringKey':'stringValue'} SIOJson Object
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Connect(const FString& InAddressAndPort, USIOJsonObject* Query = nullptr, USIOJsonObject* Headers = nullptr);

	/**
	* Disconnect from current socket.io server, optional method.
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Disconnect();

	void SyncDisconnect();

	//
	//Blueprint Functions
	//

	/**
	* Emit an event with a JsonValue message
	*
	* @param Name		Event name
	* @param Message	SIOJJsonValue
	* @param Namespace	Namespace within socket.io
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Emit(const FString& EventName, USIOJsonValue* Message = nullptr, const FString& Namespace = FString(TEXT("/")));

	/**
	* Emit an event with a JsonValue message with a callback function defined by CallBackFunctionName
	*
	* @param Name					Event name
	* @param Message				SIOJsonValue
	* @param CallbackFunctionName	Name of the optional callback function with signature (String, SIOJsonValue)
	* @param Target					CallbackFunction target object, typically self where this is called.
	* @param Namespace				Namespace within socket.io
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void EmitWithCallBack(	const FString& EventName,
							USIOJsonValue* Message = nullptr,
							const FString& CallbackFunctionName = FString(""),
							UObject* Target = nullptr,
							const FString& Namespace = FString(TEXT("/")));

	/**
	* Bind an event, then respond to it with 'On' multi-cast delegate
	*
	* @param EventName	Event name
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void BindEvent(const FString& EventName, const FString& Namespace = FString(TEXT("/")));


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
	//
	//C++ functions
	//

	/**
	* Emit an event with a JsonValue message 
	*
	* @param EventName				Event name
	* @param Message				FJsonValue
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					const TSharedPtr<FJsonValue>& Message = nullptr,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with a Json Object message
	*
	* @param EventName				Event name
	* @param ObjectMessage			FJsonObject
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					const TSharedPtr<FJsonObject>& ObjectMessage = nullptr,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with a string message
	*
	* @param EventName				Event name
	* @param StringMessage			Message in string format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					const FString& StringMessage = FString(),
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with a number (double) message
	*
	* @param EventName				Event name
	* @param NumberMessage			Message in double format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					double NumberMessage,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with a bool message
	*
	* @param EventName				Event name
	* @param BooleanMessage			Message in bool format
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					bool BooleanMessage,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with a binary message
	*
	* @param EventName				Event name
	* @param BinaryMessage			Message in an TArray of uint8
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					const TArray<uint8>& BinaryMessage,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with an array message
	*
	* @param EventName				Event name
	* @param ArrayMessage			Message in an TArray of FJsonValues
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					const TArray<TSharedPtr<FJsonValue>>& ArrayMessage,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* (Overloaded) Emit an event with an UStruct message
	*
	* @param EventName				Event name
	* @param Struct					UStruct type usually obtained via e.g. FMyStructType::StaticStruct()
	* @param StructPtr				Pointer to the actual struct memory e.g. &MyStruct
	* @param CallbackFunction		Optional callback TFunction
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitNative(const FString& EventName,
					UStruct* Struct,
					const void* StructPtr,
					TFunction< void(const TArray<TSharedPtr<FJsonValue>>&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* Emit a raw sio::message event
	*
	* @param EventName				Event name
	* @param MessageList			Message in sio::message::list format
	* @param CallbackFunction		Optional callback TFunction with raw signature
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitRaw(	const FString& EventName,
					const sio::message::list& MessageList = nullptr,
					TFunction<void(const sio::message::list&)> CallbackFunction = nullptr,
					const FString& Namespace = FString(TEXT("/")));

	/**
	* Emit an optimized binary message
	*
	* @param EventName				Event name
	* @param Data					Buffer Pointer
	* @param DataLength				Buffer size
	* @param Namespace				Optional Namespace within socket.io
	*/
	void EmitRawBinary(const FString& EventName, uint8* Data, int32 DataLength, const FString& Namespace = FString(TEXT("/")));
	

	/**
	* Call function callback on receiving socket event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, JSONValue
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnNativeEvent(	const FString& EventName,
						TFunction< void(const FString&, const TSharedPtr<FJsonValue>&)> CallbackFunction,
						const FString& Namespace = FString(TEXT("/")));

	/**
	* Call function callback on receiving raw event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, raw flavor
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnRawEvent(const FString& EventName,
					TFunction< void(const FString&, const sio::message::ptr&)> CallbackFunction,
					const FString& Namespace = FString(TEXT("/")));
	/**
	* Call function callback on receiving binary event. C++ only.
	*
	* @param EventName	Event name
	* @param TFunction	Lambda callback, raw flavor
	* @param Namespace	Optional namespace, defaults to default namespace
	*/
	void OnBinaryEvent(	const FString& EventName,
						TFunction< void(const FString&, const TArray<uint8>&)> CallbackFunction,
						const FString& Namespace = FString(TEXT("/")));

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

protected:

	bool CallBPFunctionWithResponse(UObject* Target, const FString& FunctionName, TArray<TSharedPtr<FJsonValue>> Response);
	bool CallBPFunctionWithMessage(UObject* Target, const FString& FunctionName, TSharedPtr<FJsonValue> Message);

	sio::client* PrivateClient;
	class FSIOLambdaRunnable* ConnectionThread;
};