// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "SIOJsonValue.generated.h"

class USIOJsonObject;

/**
 * Represents all the types a Json Value can be.
 */
UENUM(BlueprintType)
namespace ESIOJson
{
	enum Type
	{
		None,
		Null,
		String,
		Number,
		Boolean,
		Array,
		Object,
	};
}

/**
 * Blueprintable FJsonValue wrapper
 */
UCLASS(BlueprintType, Blueprintable)
class SIOJSON_API USIOJsonValue : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Create new Json Number value
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Number Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Json")
	static USIOJsonValue* ConstructJsonValueNumber(UObject* WorldContextObject, float Number);

	/** Create new Json String value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json String Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Json")
	static USIOJsonValue* ConstructJsonValueString(UObject* WorldContextObject, const FString& StringValue);

	/** Create new Json Bool value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Bool Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Json")
	static USIOJsonValue* ConstructJsonValueBool(UObject* WorldContextObject, bool InValue);

	/** Create new Json Array value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Array Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Json")
	static USIOJsonValue* ConstructJsonValueArray(UObject* WorldContextObject, const TArray<USIOJsonValue*>& InArray);

	/** Create new Json Object value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Construct Json Object Value", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Json")
	static USIOJsonValue* ConstructJsonValueObject(UObject* WorldContextObject, USIOJsonObject *JsonObject);

	/** Create new Json value from FJsonValue (to be used from SIOJJsonObject) */
	static USIOJsonValue* ConstructJsonValue(UObject* WorldContextObject, const TSharedPtr<FJsonValue>& InValue);

	/** Create new Json value from JSON encoded string*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Value From Json String", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Json")
	static USIOJsonValue* ValueFromJsonString(UObject* WorldContextObject, const FString& StringValue);

	/** Get the root Json value */
	TSharedPtr<FJsonValue>& GetRootValue();

	/** Set the root Json value */
	void SetRootValue(TSharedPtr<FJsonValue>& JsonValue);


	//////////////////////////////////////////////////////////////////////////
	// FJsonValue API

	/** Get type of Json value (Enum) */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	ESIOJson::Type GetType() const;

	/** Get type of Json value (String) */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	FString GetTypeString() const;

	/** Returns true if this value is a 'null' */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	bool IsNull() const;

	/** Returns this value as a double, throwing an error if this is not an Json Number
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	float AsNumber() const;

	/** Returns this value as a number, throwing an error if this is not an Json String */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	FString AsString() const;

	/** Returns this value as a boolean, throwing an error if this is not an Json Bool */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	bool AsBool() const;

	/** Returns this value as an array, throwing an error if this is not an Json Array */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	TArray<USIOJsonValue*> AsArray() const;

	/** Returns this value as an object, throwing an error if this is not an Json Object */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	USIOJsonObject* AsObject();


	UFUNCTION(BlueprintCallable, Category = "SIOJ|Json")
	FString EncodeJson() const;

	//////////////////////////////////////////////////////////////////////////
	// Data

private:
	/** Internal JSON data */
	TSharedPtr<FJsonValue> JsonVal;


	//////////////////////////////////////////////////////////////////////////
	// Helpers

protected:
	/** Simple error logger */
	void ErrorMessage(const FString& InType) const;

};