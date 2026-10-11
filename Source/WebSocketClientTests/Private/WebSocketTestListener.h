// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SIOJsonValue.h"
#include "WebSocketTestListener.generated.h"

/** Struct for the SendStruct round trip */
USTRUCT()
struct FWebSocketTestStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Count = 0;

	UPROPERTY()
	TArray<float> Values;
};

/** Records UWebSocketClientComponent events for the automation tests */
UCLASS(Transient)
class UWebSocketTestListener : public UObject
{
	GENERATED_BODY()

public:
	int32 Connects = 0;
	FString Protocol;
	int32 Disconnects = 0;
	int32 StatusCode = 0;
	FString Reason;
	bool bWasClean = false;
	TArray<FString> Errors;
	TArray<FString> Messages;
	TArray<TArray<uint8>> BinaryMessages;
	TArray<FString> JsonMessages;

	UFUNCTION()
	void HandleConnected(FString InProtocol)
	{
		Connects++;
		Protocol = InProtocol;
	}

	UFUNCTION()
	void HandleDisconnected(int32 InStatusCode, FString InReason, bool bInWasClean)
	{
		Disconnects++;
		StatusCode = InStatusCode;
		Reason = InReason;
		bWasClean = bInWasClean;
	}

	UFUNCTION()
	void HandleError(FString Error)
	{
		Errors.Add(Error);
	}

	UFUNCTION()
	void HandleMessage(FString Message)
	{
		Messages.Add(Message);
	}

	UFUNCTION()
	void HandleBinaryMessage(const TArray<uint8>& Bytes)
	{
		BinaryMessages.Add(Bytes);
	}

	UFUNCTION()
	void HandleJsonMessage(USIOJsonValue* Message)
	{
		JsonMessages.Add(Message ? Message->EncodeJson() : FString());
	}
};
