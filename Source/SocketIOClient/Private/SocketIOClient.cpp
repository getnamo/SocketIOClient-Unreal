#include "SocketIOClientPrivatePCH.h"
#include "SocketIONative.h"
#include "SIOLambdaRunnable.h"

#define LOCTEXT_NAMESPACE "FSocketIOClientModule"

class FSocketIOClientModule : public ISocketIOClientModule
{
public:
	virtual FSocketIONative* NewValidNativePointer() override;
	void ReleaseNativePointer(FSocketIONative* PointerToRelease) override;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FCriticalSection DeleteSection;
	TArray<FSocketIONative*> PluginNativePointers;
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

	//Wait for all pointers to release
	float Elapsed = 0.f;
	while (bHasActiveNativePointers)
	{
		FPlatformProcess::Sleep(0.01f);
		Elapsed += 0.01f;

		//if it takes more than 5 seconds, just quit
		if (Elapsed > 5.f)
		{
			UE_LOG(SocketIOLog, Warning, TEXT("FSocketIOClientModule::ShutdownModule force quit due to long quit."));
			break;
		}
	}

	//Native pointers will be automatically released by uninitialize components
	PluginNativePointers.Empty();
}

FSocketIONative* FSocketIOClientModule::NewValidNativePointer()
{
	FSocketIONative* NewPointer = new FSocketIONative;
	PluginNativePointers.Add(NewPointer);
	bHasActiveNativePointers = true;

	return NewPointer;
}

void FSocketIOClientModule::ReleaseNativePointer(FSocketIONative* PointerToRelease)
{
	//Release the pointer on the background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([PointerToRelease, this]
	{
		if (PointerToRelease)
		{
			//Disconnect
			if (PointerToRelease->bIsConnected)
			{
				PointerToRelease->SyncDisconnect();
			}

			//Delete pointer ensure this get's hit safely
			if (PointerToRelease)
			{
				FScopeLock Lock(&DeleteSection);

				PluginNativePointers.Remove(PointerToRelease);
				delete PointerToRelease;
				bHasActiveNativePointers = PluginNativePointers.Num() > 0;
			}
		}
	});
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSocketIOClientModule, SocketIOClient)