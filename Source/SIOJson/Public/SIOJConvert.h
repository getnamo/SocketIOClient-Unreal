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

	//struct encoding to json, todo: clean-up and match internal names
	static TSharedPtr<FJsonObject> ToJsonObject(UStruct* Struct, void* StructPtr, bool IsBlueprintStruct = false);
	//struct encoding from json, todo: clean-up and match internal names
	static bool JsonObjectToUStruct(TSharedPtr<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct = false);

	//typically from callbacks
	static FString ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);
	static class USIOJsonValue* ToSIOJsonValue(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);

	static TSharedPtr<FJsonValue> ToJsonValue(const FString& JsonString);

	static TArray<TSharedPtr<FJsonValue>> ToJsonArray(const FString& JsonString);
}; 
