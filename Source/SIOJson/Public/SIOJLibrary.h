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
	* Uses the reflection system to convert a unreal struct into a JsonObject
	*
	* @param AnyStruct		The struct you wish to convert
	* @return				Converted Json Object
	*/
	UFUNCTION(BlueprintPure, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static USIOJsonObject* StructToJsonObject(UProperty* AnyStruct);

	//fills passed in struct with data from json object
	UFUNCTION(BlueprintCallable, Category = "SocketIOFunctions", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static void JsonObjectToStruct(USIOJsonObject* JsonObject, UProperty* AnyStruct);

	//Convert property into c++ accessible form
	DECLARE_FUNCTION(execStructToJsonObject)
	{
		// Steps into the stack, walking to the next property in it
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* StructPtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		auto BPJsonObject = NewObject<USIOJsonObject>();

		auto JsonObject = USIOJConvert::ToJsonObject(StructProperty->Struct, StructPtr);
		BPJsonObject->SetRootObject(JsonObject);

		*(USIOJsonObject**)RESULT_PARAM = BPJsonObject;
	}

	DECLARE_FUNCTION(execJsonObjectToStruct)
	{
		//todo: finish this one
	}

public:
	/** Easy way to process http requests */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility", meta = (WorldContext = "WorldContextObject"))
	static void CallURL(UObject* WorldContextObject, const FString& URL, ERequestVerb Verb, ERequestContentType ContentType, USIOJsonObject* SIOJJson, const FSIOJCallDelegate& Callback);

	/** Called when URL is processed (one for both success/unsuccess events)*/
	static void OnCallComplete(USIOJRequestJSON* Request);

private:
	static TMap<USIOJRequestJSON*, FSIOJCallResponse> RequestMap;

};