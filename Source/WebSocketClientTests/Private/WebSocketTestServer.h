// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"

/**
 * In-process websocket server for the automation tests, listening on 127.0.0.1 with a free port.
 * Echoes every message. Text commands:
 *   close:<code>:<reason>	closes from the server side
 *   drop					drops the TCP connection without a close handshake
 *   header:<name>			replies with that header of the upgrade request
 * The path /reject refuses the handshake with 401. The first requested subprotocol is accepted.
 */
class FWebSocketTestServer
{
public:
	FWebSocketTestServer();
	~FWebSocketTestServer();

	/** With TLS the server uses a certificate for "localhost" signed by GetCACertificatePEM() */
	bool Start(bool bUseTLS);
	void Stop();

	int32 GetPort() const;
	FString GetUrl(const FString& Host = TEXT("127.0.0.1"), const FString& Path = TEXT("/")) const;
	FString GetCACertificatePEM() const;

private:
	struct FImpl;
	TUniquePtr<FImpl> Impl;
};
