// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SIOJConvert.generated.h"

struct FTrimmedKeyMap
{
	FString LongKey;
	TMap<FString, TSharedPtr<FTrimmedKeyMap>> SubMap;
};

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

	//BP struct get their names cleaned
	static TSharedPtr<FJsonObject> ToJsonObject(UStruct* Struct, void* StructPtr, bool IsBlueprintStruct = false);
	
	//Expects a JsonObject, if blueprint struct it will lengthen the names to fill properly
	static bool JsonObjectToUStruct(TSharedPtr<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct = false);
		
	//typically from callbacks
	static FString ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);
	static class USIOJsonValue* ToSIOJsonValue(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);

	static TSharedPtr<FJsonValue> ToJsonValue(const FString& JsonString);

	static TArray<TSharedPtr<FJsonValue>> ToJsonArray(const FString& JsonString);


	//internalish utility
	static void TrimValueKeyNames(const TSharedPtr<FJsonValue>& JsonValue);
	static bool TrimKey(const FString& InLongKey, FString& OutTrimmedKey);
	static void SetTrimmedKeyMapForStruct(TSharedPtr<FTrimmedKeyMap>& InMap, UStruct* Struct);
	static void SetTrimmedKeyMapForProp(TSharedPtr<FTrimmedKeyMap>& InMap, UProperty* ArrayInnerProp);
	static void ReplaceJsonValueNamesWithMap(TSharedPtr<FJsonValue>& InValue, TSharedPtr<FTrimmedKeyMap> KeyMap);
}; 
