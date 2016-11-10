// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJsonPrivatePCH.h"

class FSIOJson : public ISIOJson
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		// @HACK Force classes to be compiled on shipping build
		USIOJsonObject::StaticClass();
		USIOJsonValue::StaticClass();
		USIOJRequestJSON::StaticClass();
	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_MODULE(FSIOJson, SIOJson)

DEFINE_LOG_CATEGORY(LogSIOJ);
