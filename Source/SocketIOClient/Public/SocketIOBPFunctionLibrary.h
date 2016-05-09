#pragma once

#include "SocketIOBPFunctionLibrary.generated.h"

UCLASS()
class USocketIOBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Connect to a socket.io server
	*
	* @param AddressAndPort	the address in URL format with port
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Client Functions")
	static void Connect(FString AddressAndPort);

	/**
	* Emit a string event with a string action
	*
	* @param Name	Event name
	* @param Action action string
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Client Functions")
	static void Emit(FString Name, FString Action);
};