// Copyright 2016 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "SIOJTypes.h"
#include "SIOJLibrary.generated.h"

class USIOJRequestJSON;
class USIOJsonObject;

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
class USIOJLibrary : public UBlueprintFunctionLibrary
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
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility", meta = (DisplayName = "Base64 Encode"))
	static FString Base64Encode(const FString& Source);

	/**
	 * Decodes a Base64 string into a FString
	 *
	 * @param Source	The stringified data to convert
	 * @param Dest		The out buffer that will be filled with the decoded data
	 * @return			True if the buffer was decoded, false if it failed to decode
	 */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility", meta = (DisplayName = "Base64 Decode"))
	static bool Base64Decode(const FString& Source, FString& Dest);

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
	static USIOJsonObject* StructToJsonObject(UProperty* AnyStruct);

	/**
	* Uses the reflection system to fill an unreal struct from data defined in JsonObject.
	*
	* @param JsonObject		The source JsonObject for properties to fill
	* @param AnyStruct		The struct you wish to fill
	* @return				Whether all properties filled correctly
	*/
	UFUNCTION(BlueprintCallable, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static bool JsonObjectToStruct(USIOJsonObject* JsonObject, UProperty* AnyStruct);

	//Convert property into c++ accessible form
	DECLARE_FUNCTION(execStructToJsonObject)
	{
		//Get properties and pointers from stack
		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		auto BPJsonObject = NewObject<USIOJsonObject>();

		auto JsonObject = USIOJConvert::ToJsonObject(StructProperty->Struct, StructPtr, true);
		BPJsonObject->SetRootObject(JsonObject);

		*(USIOJsonObject**)RESULT_PARAM = BPJsonObject;
	}

	DECLARE_FUNCTION(execJsonObjectToStruct)
	{
		//Get properties and pointers from stack
		P_GET_OBJECT(USIOJsonObject, JsonObject);

		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		//Pass in the reference to the json object
		bool Success = USIOJConvert::JsonObjectToUStruct(JsonObject->GetRootObject(), StructProperty->Struct, StructPtr, true);

		*(bool*)RESULT_PARAM = Success;
	}

	//Conversion Nodes

	//ToJsonValue

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (Array)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_ArrayToJsonValue(const TArray<USIOJsonValue*>& InArray);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (JsonObject)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_JsonObjectToJsonValue(USIOJsonObject* InObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (Bytes)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_BytesToJsonValue(const TArray<uint8>& InBytes);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (String)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_StringToJsonValue(const FString& InString);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (Integer)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_IntToJsonValue(int32 InInt);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (Float)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_FloatToJsonValue(float InFloat);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (Bool)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonValue* Conv_BoolToJsonValue(bool InBool);

	//To Native Types
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Integer (JsonValue)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static int32 Conv_JsonValueToInt(class USIOJsonValue* InValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Float (JsonValue)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static float Conv_JsonValueToFloat(class USIOJsonValue* InValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bool (JsonValue)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static bool Conv_JsonValueToBool(class USIOJsonValue* InValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bytes (JsonValue)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static TArray<uint8> Conv_JsonValueToBytes(class USIOJsonValue* InValue);

	//ToString - these never get called sadly, kismet library get display name takes priority
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (SIOJsonObject)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|SocketIO")
	static FString Conv_JsonObjectToString(class USIOJsonObject* InObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Object (JsonValue)", BlueprintAutocast), Category = "Utilities|SocketIO")
	static USIOJsonObject* Conv_JsonValueToJsonObject(class USIOJsonValue* InValue);

public:
	/** Easy way to process http requests */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility", meta = (WorldContext = "WorldContextObject"))
	static void CallURL(UObject* WorldContextObject, const FString& URL, ESIORequestVerb Verb, ESIORequestContentType ContentType, USIOJsonObject* SIOJJson, const FSIOJCallDelegate& Callback);

	/** Called when URL is processed (one for both success/unsuccess events)*/
	static void OnCallComplete(USIOJRequestJSON* Request);

private:
	static TMap<USIOJRequestJSON*, FSIOJCallResponse> RequestMap;

};
