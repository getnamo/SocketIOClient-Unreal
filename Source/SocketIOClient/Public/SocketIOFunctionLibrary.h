// Copyright 2019-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SocketIOClientComponent.h"
#include "SocketIOFunctionLibrary.generated.h"

/**
 * Static spawning support library
 */
UCLASS()
class SOCKETIOCLIENT_API USocketIOFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Static function to spawn a component that doesn't attach */
	UFUNCTION(BlueprintCallable, Category = "SocketIO Client Static", meta = (WorldContext = "WorldContextObject"))
	static USocketIOClientComponent* ConstructSocketIOComponent(UObject* WorldContextObject);

	/** Call a function by name with SIOJsonValue signature. Utility for RPC in BPs*/
	UFUNCTION(BlueprintCallable, Category = "SocketIO Utility", meta = (WorldContext = "WorldContextObject"))
	static bool CallFunctionByName(const FString& FunctionName, UObject* Target, UObject* WorldContextObject, USIOJsonValue* Param);
};
