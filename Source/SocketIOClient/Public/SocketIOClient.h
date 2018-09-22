// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "Runtime/Core/Public/Modules/ModuleManager.h"
class FSocketIONative;


class SOCKETIOCLIENT_API ISocketIOClientModule : public IModuleInterface
{
public:

	/**
	* Singleton - like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline ISocketIOClientModule& Get()
	{
		return FModuleManager::LoadModuleChecked< ISocketIOClientModule >("SocketIOClient");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("SocketIOClient");
	}

	/** 
	* Request a new plugin scoped pointer as a shared ptr.
	*/
	virtual TSharedPtr<FSocketIONative> NewValidNativePointer() { return nullptr; };

	/** 
	* Request a shared FSocketIONative instance for a given id. May allocate a new pointer.
	*/
	virtual TSharedPtr<FSocketIONative> ValidSharedNativePointer(FString SharedId) { return nullptr; };

	/** 
	* Releases the given plugin scoped pointer using a background thread
	* After calling this function make sure to set your pointer to nullptr.
	*/
	virtual void ReleaseNativePointer(TSharedPtr<FSocketIONative> PointerToRelease) {};
};