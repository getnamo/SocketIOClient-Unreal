// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJsonPrivatePCH.h"
#include "SIOJConvert.h"

USIOJsonValue::USIOJsonValue(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

USIOJsonValue* USIOJsonValue::ConstructJsonValueNumber(UObject* WorldContextObject, float Number)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueNumber(Number));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJsonValue* USIOJsonValue::ConstructJsonValueString(UObject* WorldContextObject, const FString& StringValue)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueString(StringValue));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJsonValue* USIOJsonValue::ConstructJsonValueBool(UObject* WorldContextObject, bool InValue)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueBoolean(InValue));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJsonValue* USIOJsonValue::ConstructJsonValueArray(UObject* WorldContextObject, const TArray<USIOJsonValue*>& InArray)
{
	// Prepare data array to create new value
	TArray< TSharedPtr<FJsonValue> > ValueArray;
	for (auto InVal : InArray)
	{
		ValueArray.Add(InVal->GetRootValue());
	}

	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueArray(ValueArray));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJsonValue* USIOJsonValue::ConstructJsonValueObject(UObject* WorldContextObject, USIOJsonObject *JsonObject)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueObject(JsonObject->GetRootObject()));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJsonValue* ConstructJsonValue(UObject* WorldContextObject, const TSharedPtr<FJsonValue>& InValue)
{
	TSharedPtr<FJsonValue> NewVal = InValue;

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}


USIOJsonValue* USIOJsonValue::ValueFromJsonString(UObject* WorldContextObject, const FString& StringValue)
{
	TSharedPtr<FJsonValue> NewVal = USIOJConvert::ToJsonValue(StringValue);

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

TSharedPtr<FJsonValue>& USIOJsonValue::GetRootValue()
{
	return JsonVal;
}

void USIOJsonValue::SetRootValue(TSharedPtr<FJsonValue>& JsonValue)
{
	JsonVal = JsonValue;
}


//////////////////////////////////////////////////////////////////////////
// FJsonValue API

ESIOJson::Type USIOJsonValue::GetType() const
{
	if (!JsonVal.IsValid())
	{
		return ESIOJson::None;
	}

	switch (JsonVal->Type)
	{
	case EJson::None:
		return ESIOJson::None;

	case EJson::Null:
		return ESIOJson::Null;

	case EJson::String:
		return ESIOJson::String;

	case EJson::Number:
		return ESIOJson::Number;

	case EJson::Boolean:
		return ESIOJson::Boolean;

	case EJson::Array:
		return ESIOJson::Array;

	case EJson::Object:
		return ESIOJson::Object;

	default:
		return ESIOJson::None;
	}
}

FString USIOJsonValue::GetTypeString() const
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

bool USIOJsonValue::IsNull() const 
{
	if (!JsonVal.IsValid())
	{
		return true;
	}

	return JsonVal->IsNull();
}

float USIOJsonValue::AsNumber() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Number"));
		return 0.f;
	}

	return JsonVal->AsNumber();
}

FString USIOJsonValue::AsString() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("String"));
		return FString();
	}

	return JsonVal->AsString();
}

bool USIOJsonValue::AsBool() const
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Boolean"));
		return false;
	}

	return JsonVal->AsBool();
}

TArray<USIOJsonValue*> USIOJsonValue::AsArray() const
{
	TArray<USIOJsonValue*> OutArray;

	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Array"));
		return OutArray;
	}

	TArray< TSharedPtr<FJsonValue> > ValArray = JsonVal->AsArray();
	for (auto Value : ValArray)
	{
		USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
		NewValue->SetRootValue(Value);

		OutArray.Add(NewValue);
	}

	return OutArray;
}

USIOJsonObject* USIOJsonValue::AsObject()
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Object"));
		return nullptr;
	}

	TSharedPtr<FJsonObject> NewObj = JsonVal->AsObject();

	USIOJsonObject* JsonObj = NewObject<USIOJsonObject>();
	JsonObj->SetRootObject(NewObj);

	return JsonObj;
}


FString USIOJsonValue::EncodeJson() const
{ 
	return USIOJConvert::ToJsonString(JsonVal);
}

//////////////////////////////////////////////////////////////////////////
// Helpers

void USIOJsonValue::ErrorMessage(const FString& InType) const
{
	UE_LOG(LogSIOJ, Error, TEXT("Json Value of type '%s' used as a '%s'."), *GetTypeString(), *InType);
}
