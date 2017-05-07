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

	ModulePointers.Empty();
	
	/*for (auto& Pointer : ModulePointers)
	{
		if (Pointer)
		{
			delete Pointer;
			Pointer = nullptr;
		}
	}*/
}

FSocketIONative* FSocketIOClientModule::NewValidNativePointer()
{
	FSocketIONative* NewPointer = new FSocketIONative;
	ModulePointers.Add(NewPointer);

	return NewPointer;
}

void FSocketIOClientModule::ReleaseNativePointer(FSocketIONative* PointerToRelease)
{
	PointerToRelease->OnConnectedCallback = [PointerToRelease](const FString& SessionId)
	{
		//If we're still connected, disconnect us
		if (PointerToRelease)
		{
			PointerToRelease->SyncDisconnect();
		}
	};

	//Release the pointer on the background thread
	FSIOLambdaRunnable::RunLambdaOnBackGroundThread([PointerToRelease, this]
	{
		FScopeLock Lock(&DeleteSection);

		if (PointerToRelease)
		{
			delete PointerToRelease;
		}
	});
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSocketIOClientModule, SocketIOClient)