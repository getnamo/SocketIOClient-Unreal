// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SIOJConvert.generated.h"

/**
 * 
 */
UCLASS()
class SIOJSON_API USIOJConvert : public UObject
{
	GENERATED_BODY()
public:

	//encode/decode json convenience wrappers
	static FString ToJsonString(const TSharedPtr<FJsonObject>& JsonObject);
	static FString ToJsonString(const TSharedPtr<FJsonValue>& JsonValue);

	static TSharedPtr<FJsonObject> ToJsonObject(const FString& JsonString);

	//typically from callbacks
	static FString ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);
	static TSharedPtr<FJsonValue> ToJsonValue(const FString& JsonString);

	static TArray<TSharedPtr<FJsonValue>> ToJsonArray(const FString& JsonString);
}; 
