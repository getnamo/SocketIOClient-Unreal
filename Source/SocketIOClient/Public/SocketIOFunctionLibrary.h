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
};
