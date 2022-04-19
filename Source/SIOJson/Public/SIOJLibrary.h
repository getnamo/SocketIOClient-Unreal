// Modifications Copyright 2018-current Getnamo. All Rights Reserved


// Copyright 2016 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "SIOJTypes.h"
#include "SIOJConvert.h"
#include "SIOJsonObject.h"
#include "SIOJRequestJSON.h"
#include "SIOJsonValue.h"
#include "SIOJLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSIOJCallDelegate, USIOJRequestJSON*, Request);

USTRUCT()
struct FSIOJCallResponse
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	USIOJRequestJSON* Request;
	
	UPROPERTY()
	UObject* WorldContextObject;
	
	UPROPERTY()
	FSIOJCallDelegate Callback;
	
	FDelegateHandle CompleteDelegateHandle;
	FDelegateHandle FailDelegateHandle;
	
	FSIOJCallResponse()
		: Request(nullptr)
		, WorldContextObject(nullptr)
	{
	}
	
};

/**
 * Usefull tools for REST communications
 */
UCLASS()
class SIOJSON_API USIOJLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		//////////////////////////////////////////////////////////////////////////
		// Helpers

public:
	/** Applies percent-encoding to text */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility")
		static FString PercentEncode(const FString& Source);

	/**
	 * Encodes a FString into a Base64 string
	 *
	 * @param Source	The string data to convert
	 * @return			A string that encodes the binary data in a way that can be safely transmitted via various Internet protocols
	 */
	UFUNCTION(BlueprintPure, Category = "SIOJ|Utility", meta = (DisplayName = "Base64 Encode (String)"))
		static FString Base64Encode(const FString& Source);

	/**
	 * Encodes a Byte array into a Base64 string
	 *
	 * @param Source	The string data to convert
	 * @return			A string that encodes the binary data in a way that can be safely transmitted via various Internet protocols
	 */
	UFUNCTION(BlueprintPure, Category = "SIOJ|Utility", meta = (DisplayName = "Base64 Encode (Bytes)"))
		static FString Base64EncodeBytes(const TArray<uint8>& Source);

	/**
	 * Decodes a Base64 string into a FString
	 *
	 * @param Source	The stringified data to convert
	 * @param Dest		The out buffer that will be filled with the decoded data
	 * @return			True if the buffer was decoded, false if it failed to decode
	 */
	UFUNCTION(BlueprintPure, Category = "SIOJ|Utility", meta = (DisplayName = "Base64 Decode (To String)"))
		static bool Base64Decode(const FString& Source, FString& Dest);


	/**
	 * Decodes a Base64 string into a Byte array
	 *
	 * @param Source	The stringified data to convert
	 * @param Dest		The out buffer that will be filled with the decoded data
	 * @return			True if the buffer was decoded, false if it failed to decode
	 */
	UFUNCTION(BlueprintPure, Category = "SIOJ|Utility", meta = (DisplayName = "Base64 Decode (To Bytes)"))
		static bool Base64DecodeBytes(const FString& Source, TArray<uint8>& Dest);

	//////////////////////////////////////////////////////////////////////////
	// Easy URL processing

	/**
	* Decodes a json string into an array of stringified json Values
	*
	* @param JsonString				Input stringified json
	* @param OutJsonValueArray		The decoded Array of JsonValue
	*/
	UFUNCTION(BlueprintPure, Category = "SIOJ|Utility")
		static bool StringToJsonValueArray(const FString& JsonString, TArray<USIOJsonValue*>& OutJsonValueArray);

	/**
	* Uses the reflection system to convert an unreal struct into a JsonObject
	*
	* @param AnyStruct		The struct you wish to convert
	* @return				Converted Json Object
	*/
	UFUNCTION(BlueprintPure, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
		static USIOJsonObject* StructToJsonObject(TFieldPath<FProperty> AnyStruct);

	//Convert property into c++ accessible form
	DECLARE_FUNCTION(execStructToJsonObject)
	{
		//Get properties and pointers from stack
		Stack.Step(Stack.Object, NULL);
		FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		auto BPJsonObject = NewObject<USIOJsonObject>();

		auto JsonObject = USIOJConvert::ToJsonObject(StructProperty->Struct, StructPtr, true);
		BPJsonObject->SetRootObject(JsonObject);

		*(USIOJsonObject**)RESULT_PARAM = BPJsonObject;
	}

	UFUNCTION(BlueprintPure, CustomThunk, meta = (DisplayName = "To JsonValue (Struct)", BlueprintAutocast, CustomStructureParam = "AnyStruct"), Category = "Utilities|SocketIO")
	static USIOJsonValue* StructToJsonValue(TFieldPath<FProperty> AnyStruct);

	DECLARE_FUNCTION(execStructToJsonValue)
	{
		//Get properties and pointers from stack
		Stack.Step(Stack.Object, NULL);
		FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		auto JsonObject = USIOJConvert::ToJsonObject(StructProperty->Struct, StructPtr, true);

		TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueObject(JsonObject));
		USIOJsonValue* BPJsonValue = NewObject<USIOJsonValue>();
		BPJsonValue->SetRootValue(JsonValue);
		
		*(USIOJsonValue**)RESULT_PARAM = BPJsonValue;
	}


	/**
	* Uses the reflection system to fill an unreal struct from data defined in JsonObject.
	*
	* @param JsonObject		The source JsonObject for properties to fill
	* @param AnyStruct		The struct you wish to fill
	* @return				Whether all properties filled correctly
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static bool JsonObjectToStruct(USIOJsonObject* JsonObject, TFieldPath<FProperty> AnyStruct);

	DECLARE_FUNCTION(execJsonObjectToStruct)
	{
		//Get properties and pointers from stack
		P_GET_OBJECT(USIOJsonObject, JsonObject);

		Stack.Step(Stack.Object, NULL);
		FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		//Pass in the reference to the json object
		bool Success = USIOJConvert::JsonObjectToUStruct(JsonObject->GetRootObject(), StructProperty->Struct, StructPtr, true);

		*(bool*)RESULT_PARAM = Success;
	}

	//Convenience - Saving/Loading structs from files
	UFUNCTION(BlueprintCallable, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static bool SaveStructToJsonFile(TFieldPath<FProperty> AnyStruct, const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static bool LoadJsonFileToStruct(const FString& FilePath, TFieldPath<FProperty> AnyStruct);

	//custom thunk needed to handle wildcard structs
	DECLARE_FUNCTION(execSaveStructToJsonFile)
	{
		Stack.StepCompiledIn<FStructProperty>(NULL);
		FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		FString FilePath;
		Stack.StepCompiledIn<FStrProperty>(&FilePath);
		P_FINISH;

		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = USIOJConvert::ToJsonFile(FilePath, StructProp->Struct, StructPtr);
		P_NATIVE_END;
	}

	//custom thunk needed to handle wildcard structs
	DECLARE_FUNCTION(execLoadJsonFileToStruct)
	{
		FString FilePath;
		Stack.StepCompiledIn<FStrProperty>(&FilePath);
		Stack.StepCompiledIn<FStructProperty>(NULL);
		FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = USIOJConvert::JsonFileToUStruct(FilePath, StructProp->Struct, StructPtr, true);
		P_NATIVE_END;
	}

	//Conversion Nodes - comments added for blueprint hover with compact nodes

	//To JsonValue (Array)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (Array)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_ArrayToJsonValue(const TArray<USIOJsonValue*>& InArray);

	//To JsonValue (JsonObject)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (JsonObject)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_JsonObjectToJsonValue(USIOJsonObject* InObject);

	//To JsonValue (Bytes)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (Bytes)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_BytesToJsonValue(const TArray<uint8>& InBytes);

	//To JsonValue (String)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (String)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_StringToJsonValue(const FString& InString);

	//To JsonValue (Integer)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (Integer)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_IntToJsonValue(int32 InInt);

	//To JsonValue (Float)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (Float)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_FloatToJsonValue(float InFloat);

	//To JsonValue (Bool)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To JsonValue (Bool)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_BoolToJsonValue(bool InBool);

	//To String (JsonValue) - doesn't autocast due to get display name
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (JsonValue)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static FString Conv_SIOJsonValueToString(class USIOJsonValue* InValue);

	//To Integer (JsonValue)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Integer (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static int32 Conv_JsonValueToInt(class USIOJsonValue* InValue);

	//To Float (JsonValue)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Float (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static float Conv_JsonValueToFloat(class USIOJsonValue* InValue);

	//To Bool (JsonValue)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bool (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static bool Conv_JsonValueToBool(class USIOJsonValue* InValue);

	//To Bytes (JsonValue)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bytes (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static TArray<uint8> Conv_JsonValueToBytes(class USIOJsonValue* InValue);

	//To String (JsonObject) - doesn't autocast due to get display name
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (JsonObject)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static FString Conv_SIOJsonObjectToString(class USIOJsonObject* InObject);

	//To Object (JsonValue)
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Object (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonObject* Conv_JsonValueToJsonObject(class USIOJsonValue* InValue);

public:
	/** Easy way to process http requests */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility", meta = (WorldContext = "WorldContextObject"))
	static void CallURL(UObject* WorldContextObject, const FString& URL, ESIORequestVerb Verb, ESIORequestContentType ContentType, USIOJsonObject* SIOJJson, const FSIOJCallDelegate& Callback);

	/** Easy way to fetch resources using get */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))
	static void GetURLBinary(UObject* WorldContextObject, const FString& URL, ESIORequestVerb Verb, ESIORequestContentType ContentType, TArray<uint8>& OutResultData, struct FLatentActionInfo LatentInfo);

	/** Called when URL is processed (one for both success/unsuccess events)*/
	static void OnCallComplete(USIOJRequestJSON* Request);

private:
	static TMap<USIOJRequestJSON*, FSIOJCallResponse> RequestMap;

};
