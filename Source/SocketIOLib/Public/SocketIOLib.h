// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "Runtime/Core/Public/Modules/ModuleManager.h"


class SOCKETIOLIB_API ISocketIOLibModule : public IModuleInterface
{
public:

	/**
	* Singleton - like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline ISocketIOLibModule& Get()
	{
		return FModuleManager::LoadModuleChecked< ISocketIOLibModule >("SocketIOLib");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("SocketIOLib");
	}
};