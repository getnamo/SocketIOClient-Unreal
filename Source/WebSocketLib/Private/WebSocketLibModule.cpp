// Copyright 2026-current Getnamo. All Rights Reserved

#include "Modules/ModuleManager.h"
#include "WebSocketLibInternal.h"

class FWebSocketLibModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		//Connections read the SSL certificate manager from their own threads, load it here on the game thread
		FModuleManager::Get().LoadModule(TEXT("SSL"));
	}

	virtual void ShutdownModule() override
	{
		WebSocketLib::StopAllConnections(3.f);
	}
};

IMPLEMENT_MODULE(FWebSocketLibModule, WebSocketLib)
