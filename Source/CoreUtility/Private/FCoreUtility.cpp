// Copyright 2018-current Getnamo. All Rights Reserved


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