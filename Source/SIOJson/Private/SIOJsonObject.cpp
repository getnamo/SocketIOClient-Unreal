// Modifications Copyright 2018-current Getnamo. All Rights Reserved


// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJsonObject.h"
#include "SIOJsonValue.h"
#include "ISIOJson.h"
#include "Misc/Base64.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

USIOJsonObject::USIOJsonObject(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Reset();
}

USIOJsonObject* USIOJsonObject::ConstructJsonObject(UObject* WorldContextObject)
{
	return NewObject<USIOJsonObject>();
}

void USIOJsonObject::Reset()
{
	if (JsonObj.IsValid())
	{
		JsonObj.Reset();
	}

	JsonObj = MakeShareable(new FJsonObject());
}

TSharedPtr<FJsonObject>& USIOJsonObject::GetRootObject()
{
	return JsonObj;
}

void USIOJsonObject::SetRootObject(const TSharedPtr<FJsonObject>& JsonObject)
{
	JsonObj = JsonObject;
}


//////////////////////////////////////////////////////////////////////////
// Serialization

FString USIOJsonObject::EncodeJson() const
{
	if (!JsonObj.IsValid())
	{
		return TEXT("");
	}

	FString OutputString;
	TSharedRef< FCondensedJsonStringWriter > Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObj.ToSharedRef(), Writer);

	return OutputString;
}

FString USIOJsonObject::EncodeJsonToSingleString() const
{
	FString OutputString = EncodeJson();

	// Remove line terminators
	(void)OutputString.Replace(LINE_TERMINATOR, TEXT(""));
	
	// Remove tabs
	(void)OutputString.Replace(LINE_TERMINATOR, TEXT("\t"));

	return OutputString;
}

bool USIOJsonObject::DecodeJson(const FString& JsonString)
{
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
	if (FJsonSerializer::Deserialize(Reader, JsonObj) && JsonObj.IsValid())
	{
		return true;
	}

	// If we've failed to deserialize the string, we should clear our internal data
	Reset();

	UE_LOG(LogSIOJ, Error, TEXT("Json decoding failed for: %s"), *JsonString);

	return false;
}


//////////////////////////////////////////////////////////////////////////
// FJsonObject API

TArray<FString> USIOJsonObject::GetFieldNames()
{
	TArray<FString> Result;
	
	if (!JsonObj.IsValid())
	{
		return Result;
	}
	
	JsonObj->Values.GetKeys(Result);
	
	return Result;
}

bool USIOJsonObject::HasField(const FString& FieldName) const
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return false;
	}

	return JsonObj->HasField(FieldName);
}

void USIOJsonObject::RemoveField(const FString& FieldName)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->RemoveField(FieldName);
}

USIOJsonValue* USIOJsonObject::GetField(const FString& FieldName) const
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return nullptr;
	}

	TSharedPtr<FJsonValue> NewVal = JsonObj->TryGetField(FieldName);
	if (NewVal.IsValid())
	{
		USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
		NewValue->SetRootValue(NewVal);

		return NewValue;
	}
	
	return nullptr;
}

void USIOJsonObject::SetField(const FString& FieldName, USIOJsonValue* JsonValue)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetField(FieldName, JsonValue->GetRootValue());
}


//////////////////////////////////////////////////////////////////////////
// FJsonObject API Helpers (easy to use with simple Json objects)

float USIOJsonObject::GetNumberField(const FString& FieldName) const
{
	if (!JsonObj.IsValid() || !JsonObj->HasTypedField<EJson::Number>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Number"), *FieldName);
		return 0.0f;
	}

	return JsonObj->GetNumberField(FieldName);
}

void USIOJsonObject::SetNumberField(const FString& FieldName, float Number)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetNumberField(FieldName, Number);
}

FString USIOJsonObject::GetStringField(const FString& FieldName) const
{
	if (!JsonObj.IsValid() || !JsonObj->HasTypedField<EJson::String>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type String"), *FieldName);
		return TEXT("");
	}
		
	return JsonObj->GetStringField(FieldName);
}

void USIOJsonObject::SetStringField(const FString& FieldName, const FString& StringValue)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetStringField(FieldName, StringValue);
}

bool USIOJsonObject::GetBoolField(const FString& FieldName) const
{
	if (!JsonObj.IsValid() || !JsonObj->HasTypedField<EJson::Boolean>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Boolean"), *FieldName);
		return false;
	}

	return JsonObj->GetBoolField(FieldName);
}

void USIOJsonObject::SetBoolField(const FString& FieldName, bool InValue)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetBoolField(FieldName, InValue);
}

TArray<USIOJsonValue*> USIOJsonObject::GetArrayField(const FString& FieldName)
{
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Array"), *FieldName);
	}

	TArray<USIOJsonValue*> OutArray;
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return OutArray;
	}

	TArray< TSharedPtr<FJsonValue> > ValArray = JsonObj->GetArrayField(FieldName);
	for (auto Value : ValArray)
	{
		USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
		NewValue->SetRootValue(Value);

		OutArray.Add(NewValue);
	}

	return OutArray;
}

void USIOJsonObject::SetArrayField(const FString& FieldName, const TArray<USIOJsonValue*>& InArray)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	TArray< TSharedPtr<FJsonValue> > ValArray;

	// Process input array and COPY original values
	for (auto InVal : InArray)
	{
		TSharedPtr<FJsonValue> JsonVal = InVal->GetRootValue();

		switch (InVal->GetType())
		{
		case ESIOJson::None:
			break;

		case ESIOJson::Null:
			ValArray.Add(MakeShareable(new FJsonValueNull()));
			break;

		case ESIOJson::String:
			ValArray.Add(MakeShareable(new FJsonValueString(JsonVal->AsString())));
			break;

		case ESIOJson::Number:
			ValArray.Add(MakeShareable(new FJsonValueNumber(JsonVal->AsNumber())));
			break;

		case ESIOJson::Boolean:
			ValArray.Add(MakeShareable(new FJsonValueBoolean(JsonVal->AsBool())));
			break;

		case ESIOJson::Array:
			ValArray.Add(MakeShareable(new FJsonValueArray(JsonVal->AsArray())));
			break;

		case ESIOJson::Object:
			ValArray.Add(MakeShareable(new FJsonValueObject(JsonVal->AsObject())));
			break;

		default:
			break;
		}
	}

	JsonObj->SetArrayField(FieldName, ValArray);
}

void USIOJsonObject::MergeJsonObject(USIOJsonObject* InJsonObject, bool Overwrite)
{
	TArray<FString> Keys = InJsonObject->GetFieldNames();
	
	for (auto Key : Keys)
	{
		if (Overwrite == false && HasField(Key))
		{
			continue;
		}
		
		SetField(Key, InJsonObject->GetField(Key));
	}
}

USIOJsonObject* USIOJsonObject::GetObjectField(const FString& FieldName) const
{
	if (!JsonObj.IsValid() || !JsonObj->HasTypedField<EJson::Object>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Object"), *FieldName);
		return nullptr;
	}

	TSharedPtr<FJsonObject> JsonObjField = JsonObj->GetObjectField(FieldName);

	USIOJsonObject* OutRestJsonObj = NewObject<USIOJsonObject>();
	OutRestJsonObj->SetRootObject(JsonObjField);

	return OutRestJsonObj;
}

void USIOJsonObject::SetObjectField(const FString& FieldName, USIOJsonObject* JsonObject)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	JsonObj->SetObjectField(FieldName, JsonObject->GetRootObject());
}

void USIOJsonObject::GetBinaryField(const FString& FieldName, TArray<uint8>& OutBinary) const
{
	if (!JsonObj->HasTypedField<EJson::String>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type String"), *FieldName);
	}
	TSharedPtr<FJsonValue> JsonValue = JsonObj->TryGetField(FieldName);

	if (FJsonValueBinary::IsBinary(JsonValue))
	{
		OutBinary = FJsonValueBinary::AsBinary(JsonValue);
	}
	else if (JsonValue->Type == EJson::String)
	{
		//If we got a string that isn't detected as a binary via socket.io protocol hack
		//then we need to decode this string as base 64
		TArray<uint8> DecodedArray;
		bool bDidDecodeCorrectly = FBase64::Decode(JsonValue->AsString(), DecodedArray);
		if (!bDidDecodeCorrectly)
		{
			UE_LOG(LogSIOJ, Warning, TEXT("USIOJsonObject::GetBinaryField couldn't decode %s as a binary."), *JsonValue->AsString());
		}
		OutBinary = DecodedArray;
	}
	else
	{
		TArray<uint8> EmptyArray;
		OutBinary = EmptyArray;
	}
}

void USIOJsonObject::SetBinaryField(const FString& FieldName, const TArray<uint8>& Bytes)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}
	TSharedPtr<FJsonValueBinary> JsonValue = MakeShareable(new FJsonValueBinary(Bytes));
	JsonObj->SetField(FieldName, JsonValue);
}

//////////////////////////////////////////////////////////////////////////
// Array fields helpers (uniform arrays)

TArray<float> USIOJsonObject::GetNumberArrayField(const FString& FieldName)
{
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Array"), *FieldName);
	}

	TArray<float> NumberArray;
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return NumberArray;
	}

	TArray<TSharedPtr<FJsonValue> > JsonArrayValues = JsonObj->GetArrayField(FieldName);
	for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
	{
		auto Value = (*It).Get();
		if (Value->Type != EJson::Number)
		{
			UE_LOG(LogSIOJ, Error, TEXT("Not Number element in array with field name %s"), *FieldName);
		}
		
		NumberArray.Add((*It)->AsNumber());
	}

	return NumberArray;
}

void USIOJsonObject::SetNumberArrayField(const FString& FieldName, const TArray<float>& NumberArray)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	TArray< TSharedPtr<FJsonValue> > EntriesArray;

	for (auto Number : NumberArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueNumber(Number)));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}

TArray<FString> USIOJsonObject::GetStringArrayField(const FString& FieldName)
{
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Array"), *FieldName);
	}

	TArray<FString> StringArray;
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return StringArray;
	}

	TArray<TSharedPtr<FJsonValue> > JsonArrayValues = JsonObj->GetArrayField(FieldName);
	for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
	{
		auto Value = (*It).Get();
		if (Value->Type != EJson::String)
		{
			UE_LOG(LogSIOJ, Error, TEXT("Not String element in array with field name %s"), *FieldName);
		}

		StringArray.Add((*It)->AsString());
	}

	return StringArray;
}

void USIOJsonObject::SetStringArrayField(const FString& FieldName, const TArray<FString>& StringArray)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	TArray< TSharedPtr<FJsonValue> > EntriesArray;
	for (auto String : StringArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueString(String)));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}

TArray<bool> USIOJsonObject::GetBoolArrayField(const FString& FieldName)
{
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Array"), *FieldName);
	}

	TArray<bool> BoolArray;
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return BoolArray;
	}

	TArray<TSharedPtr<FJsonValue> > JsonArrayValues = JsonObj->GetArrayField(FieldName);
	for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
	{
		auto Value = (*It).Get();
		if (Value->Type != EJson::Boolean)
		{
			UE_LOG(LogSIOJ, Error, TEXT("Not Boolean element in array with field name %s"), *FieldName);
		}

		BoolArray.Add((*It)->AsBool());
	}

	return BoolArray;
}

void USIOJsonObject::SetBoolArrayField(const FString& FieldName, const TArray<bool>& BoolArray)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	TArray< TSharedPtr<FJsonValue> > EntriesArray;
	for (auto Boolean : BoolArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueBoolean(Boolean)));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}

TArray<USIOJsonObject*> USIOJsonObject::GetObjectArrayField(const FString& FieldName)
{
	if (!JsonObj->HasTypedField<EJson::Array>(FieldName))
	{
		UE_LOG(LogSIOJ, Warning, TEXT("No field with name %s of type Array"), *FieldName);
	}

	TArray<USIOJsonObject*> OutArray;
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return OutArray;
	}

	TArray< TSharedPtr<FJsonValue> > ValArray = JsonObj->GetArrayField(FieldName);
	for (auto Value : ValArray)
	{
		if (Value->Type != EJson::Object)
		{
			UE_LOG(LogSIOJ, Error, TEXT("Not Object element in array with field name %s"), *FieldName);
		}

		TSharedPtr<FJsonObject> NewObj = Value->AsObject();

		USIOJsonObject* NewJson = NewObject<USIOJsonObject>();
		NewJson->SetRootObject(NewObj);

		OutArray.Add(NewJson);
	}

	return OutArray;
}

void USIOJsonObject::SetObjectArrayField(const FString& FieldName, const TArray<USIOJsonObject*>& ObjectArray)
{
	if (!JsonObj.IsValid() || FieldName.IsEmpty())
	{
		return;
	}

	TArray< TSharedPtr<FJsonValue> > EntriesArray;
	for (auto Value : ObjectArray)
	{
		EntriesArray.Add(MakeShareable(new FJsonValueObject(Value->GetRootObject())));
	}

	JsonObj->SetArrayField(FieldName, EntriesArray);
}
