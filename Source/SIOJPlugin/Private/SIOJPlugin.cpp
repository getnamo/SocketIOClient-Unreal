// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJPluginPrivatePCH.h"

class FSIOJPlugin : public ISIOJPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		// @HACK Force classes to be compiled on shipping build
		USIOJJsonObject::StaticClass();
		USIOJJsonValue::StaticClass();
		USIOJRequestJSON::StaticClass();
	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_MODULE( FSIOJPlugin, SIOJPlugin )

DEFINE_LOG_CATEGORY(LogSIOJ);
