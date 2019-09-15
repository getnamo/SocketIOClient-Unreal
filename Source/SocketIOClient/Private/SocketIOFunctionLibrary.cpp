// Copyright 2019-current Getnamo. All Rights Reserved

#include "SocketIOFunctionLibrary.h"
#include "CULambdaRunnable.h"
#include "Engine/Engine.h"

USocketIOClientComponent* USocketIOFunctionLibrary::ConstructSocketIOComponent(UObject* WorldContextObject)
{
	USocketIOClientComponent* SpawnedComponent = NewObject<USocketIOClientComponent>(WorldContextObject, TEXT("SocketIOClientComponent"));

	if (SpawnedComponent)
	{
		//Check if we got spawned by an object with an owner context (e.g. game mode) or not (e.g. game instance)
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
		AActor* MyOwner = SpawnedComponent->GetOwner();
		bool bOwnerHasValidWorld = (MyOwner ? MyOwner->GetWorld() : nullptr) != nullptr;

		SpawnedComponent->StaticInitialization(WorldContextObject, bOwnerHasValidWorld);

		//Register component if it was spawned by world owning context object, e.g. game mode
		if (bOwnerHasValidWorld)
		{
			//Delay by 1 tick so that we can adjust bShouldAutoConnect/etc
			FCULambdaRunnable::RunShortLambdaOnGameThread([SpawnedComponent]()
			{
				if (SpawnedComponent->IsValidLowLevel())
				{
					SpawnedComponent->RegisterComponent();
				}
			});
		}

		//Otherwise we don't need to register our component for the networking logic to work.
	}
	return SpawnedComponent;
}
