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
	TArray<FSocketIONative*> ModulePointers;
};


void FSocketIOClientModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	ModulePointers.Empty();
}

void FSocketIOClientModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FScopeLock Lock(&DeleteSection);


	/*for (auto& Pointer : ModulePointers)
	{
	if (Pointer)
	{
	delete Pointer;
	Pointer = nullptr;
	}
	}*/

	ModulePointers.Empty();
}

FSocketIONative* FSocketIOClientModule::NewValidNativePointer()
{
	FSocketIONative* NewPointer = new FSocketIONative;
	ModulePointers.Add(NewPointer);

	return NewPointer;
}

void FSocketIOClientModule::ReleaseNativePointer(FSocketIONative* PointerToRelease)
{
	//Release the pointer on the background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([PointerToRelease, this]
	{
		FScopeLock Lock(&DeleteSection);
		
		if (PointerToRelease)
		{
			//Disconnect
			if (PointerToRelease->bIsConnected)
			{
				PointerToRelease->SyncDisconnect();
			}

			//Delete pointer
			if (PointerToRelease)
			{
				ModulePointers.Remove(PointerToRelease);
				delete PointerToRelease;
			}
		}
	});
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSocketIOClientModule, SocketIOClient)