// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"

namespace WebSocketLib
{
	/** Module shutdown: let closing connections finish, then stop whatever is left and wait for their threads */
	void StopAllConnections(float TimeoutSeconds);
}
