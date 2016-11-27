// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJsonPrivatePCH.h"
#include "SIOJConvert.h"

#if PLATFORM_WINDOWS
#pragma region FJsonValueBinary
#endif


TArray<uint8> FJsonValueBinary::AsBinary(const TSharedPtr<FJsonValue>& InJsonValue)
{
	if (FJsonValueBinary::IsBinary(InJsonValue))
	{
		TSharedPtr<FJsonValueBinary> BinaryValue = StaticCastSharedPtr<FJsonValueBinary>(InJsonValue);
		return BinaryValue->AsBinary();
	}
	else
	{
		TArray<uint8> EmptyArray;
		return EmptyArray;
	}
}


bool FJsonValueBinary::IsBinary(const TSharedPtr<FJsonValue>& InJsonValue)
{
	//use our hackery to determine if we got a binary string
	bool IgnoreBool;
	return !InJsonValue->TryGetBool(IgnoreBool);
}

#if PLATFORM_WINDOWS
#pragma endregion FJsonValueBinary
#pragma region USIOJsonValue
#endif

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

USIOJsonValue* USIOJsonValue::ConstructJsonValueObject(USIOJsonObject *JsonObject, UObject* WorldContextObject)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueObject(JsonObject->GetRootObject()));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}


USIOJsonValue* USIOJsonValue::ConstructJsonValueBinary(UObject* WorldContextObject, TArray<uint8> ByteArray)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueBinary(ByteArray));

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
	TSharedPtr<FJsonValue> NewVal = USIOJConvert::JsonStringToJsonValue(StringValue);

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
		if (FJsonValueBinary::IsBinary(JsonVal))
		{
			return ESIOJson::Binary;
		}
		else
		{
			return ESIOJson::String;
		}
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


TArray<uint8> USIOJsonValue::AsBinary()
{
	if (!JsonVal.IsValid())
	{
		ErrorMessage(TEXT("Binary"));
		TArray<uint8> ByteArray;
		return ByteArray;
	}
	
	//binary object pretending & starts with non-json format? it's our disguise binary
	if (JsonVal->Type == EJson::String && 
		FJsonValueBinary::IsBinary(JsonVal))
	{
		//Valid binary available
		return FJsonValueBinary::AsBinary(JsonVal);
	}
	else
	{
		//Empty array
		TArray<uint8> ByteArray;
		return ByteArray;
	}
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

#if PLATFORM_WINDOWS
#pragma endregion USIOJsonValue
#endif