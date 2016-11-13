// Fill out your copyright notice in the Description page of Project Settings.

#include "SIOJsonPrivatePCH.h"

typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

FString USIOJConvert::ToJsonString(const TSharedPtr<FJsonObject>& JsonObject)
{
	FString OutputString;
	TSharedRef< FCondensedJsonStringWriter > Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return OutputString;
}

FString USIOJConvert::ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray)
{
	FString OutputString;
	TSharedRef< FCondensedJsonStringWriter > Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
	FJsonSerializer::Serialize(JsonValueArray, Writer);
	return OutputString;
}

FString USIOJConvert::ToJsonString(const TSharedPtr<FJsonValue>& JsonValue)
{
	if (JsonValue->Type == EJson::None)
	{
		return FString();
	}
	else if (JsonValue->Type == EJson::Null)
	{
		return FString();
	}
	else if (JsonValue->Type == EJson::String)
	{
		return JsonValue->AsString();
	}
	else if (JsonValue->Type == EJson::Number)
	{
		return FString::Printf(TEXT("%f"),JsonValue->AsNumber());
	}
	else if (JsonValue->Type == EJson::Boolean)
	{
		return FString::Printf(TEXT("%d"), JsonValue->AsBool());
	}
	else if (JsonValue->Type == EJson::Array)
	{
		return ToJsonString(JsonValue->AsArray());
	}
	else if (JsonValue->Type == EJson::Object)
	{
		return ToJsonString(JsonValue->AsObject());
	}
	else
	{
		return FString();
	}
}

USIOJsonValue* USIOJConvert::ToSIOJsonValue(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray)
{
	TArray< TSharedPtr<FJsonValue> > ValueArray;
	for (auto InVal : JsonValueArray)
	{
		ValueArray.Add(InVal);
	}
	
	USIOJsonValue* ResultValue = NewObject<USIOJsonValue>();
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueArray(ValueArray));
	ResultValue->SetRootValue(NewVal);

	return ResultValue;
}

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(const FString& JsonString)
{
	//Null
	if (JsonString.IsEmpty())
	{
		return MakeShareable(new FJsonValueNull);
	}

	//Number
	if (JsonString.IsNumeric())
	{
		//convert to double
		return MakeShareable(new FJsonValueNumber(FCString::Atod(*JsonString)));
	}

	//Object
	if (JsonString.StartsWith(FString(TEXT("{"))))
	{
		TSharedPtr< FJsonObject > JsonObject = MakeShareable(new FJsonObject);
		TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
		bool success = FJsonSerializer::Deserialize(Reader, JsonObject);

		if (success)
		{
			return MakeShareable(new FJsonValueObject(JsonObject));
		}
	}

	//Array
	if (JsonString.StartsWith(FString(TEXT("["))))
	{
		TArray < TSharedPtr<FJsonValue>> RawJsonValueArray;
		TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
		bool success = FJsonSerializer::Deserialize(Reader, RawJsonValueArray);

		if (success) 
		{
			return MakeShareable(new FJsonValueArray(RawJsonValueArray));
		}
	}

	//Bool
	if (JsonString == FString("true") || JsonString == FString("false"))
	{
		bool BooleanValue = (JsonString == FString("true"));
		return MakeShareable(new FJsonValueBoolean(BooleanValue));
	}
	
	//String
	return MakeShareable(new FJsonValueString(JsonString));
}

TArray<TSharedPtr<FJsonValue>> USIOJConvert::ToJsonArray(const FString& JsonString)
{
	TArray < TSharedPtr<FJsonValue>> RawJsonValueArray;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
	FJsonSerializer::Deserialize(Reader, RawJsonValueArray);

	return RawJsonValueArray;
}

TSharedPtr<FJsonObject> USIOJConvert::ToJsonObject(const FString& JsonString)
{
	TSharedPtr< FJsonObject > JsonObject = MakeShareable(new FJsonObject);
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
	FJsonSerializer::Deserialize(Reader, JsonObject);
	return JsonObject;
}

TSharedPtr<FJsonObject> USIOJConvert::ToJsonObject(UStruct* Struct, void* StructPtr)
{
	USIOJsonValue* Value = NewObject<USIOJsonValue>();
	TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	bool success = FJsonObjectConverter::UStructToJsonObject(Struct, StructPtr, JsonObject, 0, 0);

	return JsonObject;
}

bool USIOJConvert::JsonObjectToUStruct(TSharedRef<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr)
{
	return FJsonObjectConverter::JsonObjectToUStruct(JsonObject, Struct, StructPtr, 0, 0);
}
