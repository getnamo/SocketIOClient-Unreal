#include "SocketIOClientPrivatePCH.h"
#include "SocketIONative.h"

#define LOCTEXT_NAMESPACE "FSocketIOClientModule"

class FSocketIOClientModule : public ISocketIOClientModule
{
public:
	virtual FSocketIONative* NewValidNativePointer() override;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
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

	for (auto Pointer : ModulePointers)
	{
		delete Pointer;
	}
}

FSocketIONative* FSocketIOClientModule::NewValidNativePointer()
{
	FSocketIONative* NewPointer = new FSocketIONative;
	ModulePointers.Add(NewPointer);

	return NewPointer;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSocketIOClientModule, SocketIOClient)