// Copyright 2018-current Getnamo.
// Available under MIT license at https://github.com/getnamo/socketio-client-ue4

#include "CoreUtilityPrivatePCH.h"
#include "ICoreUtility.h"

DEFINE_LOG_CATEGORY(CoreUtilityLog);

class FCoreUtility : public ICoreUtility
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() {};
	virtual void ShutdownModule() {};
};


IMPLEMENT_MODULE(FCoreUtility, CoreUtility)