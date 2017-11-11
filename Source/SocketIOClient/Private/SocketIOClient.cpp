#include "SocketIOClientPrivatePCH.h"
#include "SocketIONative.h"
#include "SIOLambdaRunnable.h"

#define LOCTEXT_NAMESPACE "FSocketIOClientModule"

//struct 

class FSocketIOClientModule : public ISocketIOClientModule
{
public:
	virtual TSharedPtr<FSocketIONative> NewValidNativePointer() override;
	void ReleaseNativePointer(TSharedPtr<FSocketIONative> PointerToRelease) override;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FCriticalSection DeleteSection;
	TArray<TSharedPtr<FSocketIONative>> PluginNativePointers;
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
			UE_LOG(SocketIOLog, Warning, TEXT("FSocketIOClientModule::ShutdownModule force quit due to long wait to quit."));
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

void FSocketIOClientModule::ReleaseNativePointer(TSharedPtr<FSocketIONative> PointerToRelease)
{
	//Release the pointer on the background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([PointerToRelease, this]
	{
		if (PointerToRelease.IsValid())
		{
			//Disconnect
			if (PointerToRelease->bIsConnected)
			{
				PointerToRelease->SyncDisconnect();
			}

			//Last operation took a while, ensure it's still true
			if (PointerToRelease.IsValid())
			{
				//Ensure only one thread at a time removes from array 
				FScopeLock Lock(&DeleteSection);
				PluginNativePointers.Remove(PointerToRelease);
				
				//Update our active status
				bHasActiveNativePointers = PluginNativePointers.Num() > 0;
			}
		}
	});
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSocketIOClientModule, SocketIOClient)