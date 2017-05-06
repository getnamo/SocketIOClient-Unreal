

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
	static FString ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);

	static TSharedPtr<FJsonObject> ToJsonObject(const FString& JsonString);
	static TSharedPtr<FJsonObject> MakeJsonObject();


	//Structs

	//Will trim names if specified as blueprint
	static TSharedPtr<FJsonObject> ToJsonObject(UStruct* Struct, void* StructPtr, bool IsBlueprintStruct = false);

	//Expects a JsonObject, if blueprint struct it will lengthen the names to fill properly
	static bool JsonObjectToUStruct(TSharedPtr<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct = false);
		

	//typically from callbacks
	static class USIOJsonValue* ToSIOJsonValue(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);

	//Convenience overrides for JsonValues
	static TSharedPtr<FJsonValue> ToJsonValue(const TSharedPtr<FJsonObject>& JsonObject);
	static TSharedPtr<FJsonValue> ToJsonValue(const FString& StringValue);
	static TSharedPtr<FJsonValue> ToJsonValue(double NumberValue);
	static TSharedPtr<FJsonValue> ToJsonValue(bool BoolValue);
	static TSharedPtr<FJsonValue> ToJsonValue(const TArray<uint8>& BinaryValue);
	static TSharedPtr<FJsonValue> ToJsonValue(const TArray<TSharedPtr<FJsonValue>>& ArrayValue);

	static TSharedPtr<FJsonValue> JsonStringToJsonValue(const FString& JsonString);
	static TArray<TSharedPtr<FJsonValue>> JsonStringToJsonArray(const FString& JsonString);


	//internal utility, exposed for modularity
	static void TrimValueKeyNames(const TSharedPtr<FJsonValue>& JsonValue);
	static bool TrimKey(const FString& InLongKey, FString& OutTrimmedKey);
	static void SetTrimmedKeyMapForStruct(TSharedPtr<FTrimmedKeyMap>& InMap, UStruct* Struct);
	static void SetTrimmedKeyMapForProp(TSharedPtr<FTrimmedKeyMap>& InMap, UProperty* ArrayInnerProp);
	static void ReplaceJsonValueNamesWithMap(TSharedPtr<FJsonValue>& InValue, TSharedPtr<FTrimmedKeyMap> KeyMap);
}; 
