// Copyright 2018-current Getnamo. All Rights Reserved


#include "SocketIOLib.h"


//struct 

class FSocketIOLibModule : public ISocketIOLibModule
{
public:
	virtual void StartupModule() override
	{
		//TLS certificate verification uses the SSL module's certificate manager
		FModuleManager::Get().LoadModule(TEXT("SSL"));
	}
};


IMPLEMENT_MODULE(FSocketIOLibModule, SocketIOLib)