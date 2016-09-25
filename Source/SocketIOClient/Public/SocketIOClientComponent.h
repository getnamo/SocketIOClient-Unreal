#pragma once

#include "sio_client.h"
#include "Components/ActorComponent.h"
#include "SocketIOClientComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIOCConnectedEventSignature);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIOCDisconnectedEventSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIOCOnEventSignature, FString, Name, FString, Action);

UCLASS(ClassGroup = "Networking", meta = (BlueprintSpawnableComponent))
class SOCKETIOCLIENT_API USocketIOClientComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	//Async events
	/*UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
		FSIOCConnectedEventSignature Connected;

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
		FSIOCDisconnectedEventSignature Disconnected;*/

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
		FSIOCOnEventSignature On;

	/**
	* Connect to a socket.io server
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
		void Connect(FString AddressAndPort);

	/**
	* Emit a string event with a string action
	*
	* @param Name	Event name
	* @param Data Data string
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
		void Emit(FString Name, FString Data, FString Namespace = FString(TEXT("/")));

	/**
	* Emit a string event with a string action
	*
	* @param Name	Event name
	* @param Action action string
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
		void Bind(FString Name, FString Namespace = FString(TEXT("/")));

protected:
	sio::client PrivateClient;

private:

	//sio::packet_manager manager;
	//std::mutex packetLock;
	sio::message::ptr getMessage(const std::string& json);
	std::string getJson(sio::message::ptr msg);
};