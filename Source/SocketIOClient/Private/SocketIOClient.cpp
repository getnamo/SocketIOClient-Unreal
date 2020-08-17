// Copyright 2018-current Getnamo. All Rights Reserved


#include "SocketIOClient.h"
#include "SocketIONative.h"
#include "SIOMessageConvert.h"
#include "CULambdaRunnable.h"
#include "Runtime/Core/Public/HAL/ThreadSafeBool.h"

#define LOCTEXT_NAMESPACE "FSocketIOClientModule"

//struct 

class FSocketIOClientModule : public ISocketIOClientModule
{
public:
	//virtual TSharedPtr<FSocketIONative> NewValidNativePointer() override;
	virtual TSharedPtr<FSocketIONative> NewValidNativePointer() override;
	virtual TSharedPtr<FSocketIONative> ValidSharedNativePointer(FString SharedId) override;
	void ReleaseNativePointer(TSharedPtr<FSocketIONative> PointerToRelease) override;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FCriticalSection DeleteSection;

	//All native pointers manages by the plugin
	TArray<TSharedPtr<FSocketIONative>> PluginNativePointers;

	//Shared pointers, these will typically be alive past game world lifecycles
	TMap<FString, TSharedPtr<FSocketIONative>> SharedNativePointers;
	TSet<TSharedPtr<FSocketIONative>> AllSharedPtrs;	//reverse lookup

	FThreadSafeBool bHasActiveNativePointers;
};


void FSocketIOClientModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	PluginNativePointers.Empty();
}

void FSocketIOClientModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	/*
	Ensure we call release pointers, this will catch all the plugin scoped 
	connections pointers which don't get auto-released between game worlds.
	*/
	auto AllActivePointers = PluginNativePointers;
	for (auto& Pointer : AllActivePointers)
	{
		ReleaseNativePointer(Pointer);
	}
	AllActivePointers.Empty();

	//Wait for all pointers to release
	float Elapsed = 0.f;
	while (bHasActiveNativePointers)
	{
		FPlatformProcess::Sleep(0.01f);
		Elapsed += 0.01f;

		//if it takes more than 5 seconds, just quit
		if (Elapsed > 5.f)
		{
			UE_LOG(SocketIO, Warning, TEXT("FSocketIOClientModule::ShutdownModule force quit due to long wait to quit."));
			break;
		}
	}

	//Native pointers will be automatically released by uninitialize components
	PluginNativePointers.Empty();
}

TSharedPtr<FSocketIONative> FSocketIOClientModule::NewValidNativePointer()
{
	TSharedPtr<FSocketIONative> NewPointer = MakeShareable(new FSocketIONative);
	
	PluginNativePointers.Add(NewPointer);
	
	bHasActiveNativePointers = true;

	return NewPointer;
}

TSharedPtr<FSocketIONative> FSocketIOClientModule::ValidSharedNativePointer(FString SharedId)
{
	//Found key? return it
	if (SharedNativePointers.Contains(SharedId))
	{
		return SharedNativePointers[SharedId];
	}
	//Otherwise request a new id and return it
	else
	{
		TSharedPtr<FSocketIONative> NewNativePtr = NewValidNativePointer();
		SharedNativePointers.Add(SharedId, NewNativePtr);
		AllSharedPtrs.Add(NewNativePtr);
		return NewNativePtr;
	}
}

void FSocketIOClientModule::ReleaseNativePointer(TSharedPtr<FSocketIONative> PointerToRelease)
{
	//Remove shared ptr references if any
	if (AllSharedPtrs.Contains(PointerToRelease))
	{
		AllSharedPtrs.Remove(PointerToRelease);
		for (auto& Pair : SharedNativePointers)
		{
			if (Pair.Value == PointerToRelease)
			{
				SharedNativePointers.Remove(Pair.Key);
				break;
			}
		}
	}

	//Release the pointer on the background thread pool, this can take ~ 1 sec per connection
	FCULambdaRunnable::RunLambdaOnBackGroundThreadPool([PointerToRelease, this]
	{
		if (PointerToRelease.IsValid())
		{
			//Ensure only one thread at a time removes from array 
			{
				FScopeLock Lock(&DeleteSection);
				PluginNativePointers.Remove(PointerToRelease);
			}

			//Disconnect, this can happen simultaneously
			if (PointerToRelease->bIsConnected)
			{
				PointerToRelease->SyncDisconnect();
			}

			//Update our active status
			bHasActiveNativePointers = PluginNativePointers.Num() > 0;
		}
	});
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSocketIOClientModule, SocketIOClient)
