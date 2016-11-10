// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJPluginPrivatePCH.h"

USIOJJsonValue::USIOJJsonValue(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

USIOJJsonValue* USIOJJsonValue::ConstructJsonValueNumber(UObject* WorldContextObject, float Number)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueNumber(Number));

	USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJJsonValue* USIOJJsonValue::ConstructJsonValueString(UObject* WorldContextObject, const FString& StringValue)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueString(StringValue));

	USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJJsonValue* USIOJJsonValue::ConstructJsonValueBool(UObject* WorldContextObject, bool InValue)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueBoolean(InValue));

	USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJJsonValue* USIOJJsonValue::ConstructJsonValueArray(UObject* WorldContextObject, const TArray<USIOJJsonValue*>& InArray)
{
	// Prepare data array to create new value
	TArray< TSharedPtr<FJsonValue> > ValueArray;
	for (auto InVal : InArray)
	{
		ValueArray.Add(InVal->GetRootValue());
	}

	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueArray(ValueArray));

	USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJJsonValue* USIOJJsonValue::ConstructJsonValueObject(UObject* WorldContextObject, USIOJJsonObject *JsonObject)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueObject(JsonObject->GetRootObject()));

	USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJJsonValue* ConstructJsonValue(UObject* WorldContextObject, const TSharedPtr<FJsonValue>& InValue)
{
	TSharedPtr<FJsonValue> NewVal = InValue;

	USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

TSharedPtr<FJsonValue>& USIOJJsonValue::GetRootValue()
{
	return JsonVal;
}

void USIOJJsonValue::SetRootValue(TSharedPtr<FJsonValue>& JsonValue)
{
	JsonVal = JsonValue;
}


//////////////////////////////////////////////////////////////////////////
// FJsonValue API

EVaJson::Type USIOJJsonValue::GetType() const
{
	if (!JsonVal.IsValid())
	{
		return EVaJson::None;
	}

	switch (JsonVal->Type)
	{
	case EJson::None:
		return EVaJson::None;

	case EJson::Null:
		return EVaJson::Null;

	case EJson::String:
		return EVaJson::String;

	case EJson::Number:
		return EVaJson::Number;

	case EJson::Boolean:
		return EVaJson::Boolean;

	case EJson::Array:
		return EVaJson::Array;

	case EJson::Object:
		return EVaJson::Object;

	default:
		return EVaJson::None;
	}
}

FString USIOJJsonValue::GetTypeString() const
{
	if (!JsonVal.IsValid())
	{
		return "None";
	}

	switch (JsonVal->Type)
	{
	case EJson::None:
		return TEXT("None");

	case EJson::Null:
		return TEXT("Null");

	case EJson::String:
		return TEXT("String");

	case EJson::Number:
		return TEXT("Number");

	case EJson::Boolean:
		return TEXT("Boolean");

	case EJson::Array:
		return TEXT("Array");

	case EJson::Object:
		return TEXT("Object");

	default:
		return TEXT("None");
	}
}

bool USIOJJsonValue::IsNull() const 
{
	if (!JsonVal.IsValid())
	{
		return true;
	}

	return JsonVal->IsNull();
}

float USIOJJsonValue::AsNumber() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Number"));
		return 0.f;
	}

	return JsonVal->AsNumber();
}

FString USIOJJsonValue::AsString() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("String"));
		return FString();
	}

	return JsonVal->AsString();
}

bool USIOJJsonValue::AsBool() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Boolean"));
		return false;
	}

	return JsonVal->AsBool();
}

TArray<USIOJJsonValue*> USIOJJsonValue::AsArray() const
{
	TArray<USIOJJsonValue*> OutArray;

	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Array"));
		return OutArray;
	}

	TArray< TSharedPtr<FJsonValue> > ValArray = JsonVal->AsArray();
	for (auto Value : ValArray)
	{
		USIOJJsonValue* NewValue = NewObject<USIOJJsonValue>();
		NewValue->SetRootValue(Value);

		OutArray.Add(NewValue);
	}

	return OutArray;
}

USIOJJsonObject* USIOJJsonValue::AsObject()
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Object"));
		return nullptr;
	}

	TSharedPtr<FJsonObject> NewObj = JsonVal->AsObject();

	USIOJJsonObject* JsonObj = NewObject<USIOJJsonObject>();
	JsonObj->SetRootObject(NewObj);

	return JsonObj;
}


//////////////////////////////////////////////////////////////////////////
// Helpers

void USIOJJsonValue::ErrorMessage(const FString& InType) const
{
	UE_LOG(LogSIOJ, Error, TEXT("Json Value of type '%s' used as a '%s'."), *GetTypeString(), *InType);
}
