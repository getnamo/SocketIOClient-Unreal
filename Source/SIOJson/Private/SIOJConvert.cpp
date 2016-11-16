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

TSharedPtr<FJsonObject> USIOJConvert::ToJsonObject(UStruct* Struct, void* StructPtr, bool IsBlueprintStruct)
{
	TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	
	if (IsBlueprintStruct)
	{
		//Get the object keys
		TSharedPtr<FJsonObject> Object = ToJsonObject(Struct, StructPtr, false);

		//Wrap it into a value and pass it into the trimmer
		TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueObject(Object));
		TrimValueKeyNames(JsonValue);

		return JsonValue->AsObject();
	}
	else
	{
		bool success = FJsonObjectConverter::UStructToJsonObject(Struct, StructPtr, JsonObject, 0, 0);
	}
	return JsonObject;
}

bool USIOJConvert::JsonObjectToUStruct(TSharedPtr<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct)
{
	if (IsBlueprintStruct)
	{
		//todo manual system

		//Json object we pass will have their trimmed BP names, e.g. boolKey vs boolKey_8_EDBB36654CF43866C376DE921373AF23
		//so we have to match them to the verbose versions, get a map of the names

		TArray<FString> Keys;
		auto FieldPtr = Struct->Children;
		//while(FieldPtr->Next != nullptr)
		while(FieldPtr!=NULL){
			FString LowerKey = FJsonObjectConverter::StandardizeCase(FieldPtr->GetName());
			FString TrimmedComparison;
			TrimKey(LowerKey, TrimmedComparison);

			UE_LOG(LogTemp, Log, TEXT("lc: %s, trim: %s"), *LowerKey, *TrimmedComparison);

			
			FieldPtr = FieldPtr->Next;
		}

		//temp work around, nope we're not special
		return JsonObjectToUStruct(JsonObject, Struct, StructPtr, false);
	}
	else
	{
		return FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), Struct, StructPtr, 0, 0);
	}
}

void USIOJConvert::TrimValueKeyNames(const TSharedPtr<FJsonValue>& JsonValue)
{
	//Array?
	if (JsonValue->Type == EJson::Array) 
	{
		auto Array = JsonValue->AsArray();

		for (auto SubValue : Array)
		{
			TrimValueKeyNames(SubValue);
		}
	}
	//Object?
	else if (JsonValue->Type == EJson::Object)
	{
		auto JsonObject = JsonValue->AsObject();
		for (auto Pair : JsonObject->Values)
		{
			const FString& Key = Pair.Key;
			FString TrimmedKey;

			bool DidNeedTrimming = TrimKey(Key, TrimmedKey);

			//Positive count? trim it
			if (DidNeedTrimming)
			{
				//Trim subvalue if applicable
				auto SubValue = Pair.Value;
				TrimValueKeyNames(SubValue);

				JsonObject->SetField(TrimmedKey, SubValue);
				JsonObject->RemoveField(Key);

				UE_LOG(LogTemp, Log, TEXT("orig: %s, trimmed: %s"), *Pair.Key, *TrimmedKey);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("untrimmed: %s"), *Pair.Key);
			}
		}
	}
}

bool USIOJConvert::TrimKey(const FString& InLongKey, FString& OutTrimmedKey)
{
	//Look for the position of the 2nd '_'
	int32 LastIndex = InLongKey.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	LastIndex = InLongKey.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromEnd, LastIndex);

	if (LastIndex >= 0)
	{
		OutTrimmedKey = InLongKey.Mid(0, LastIndex);;
		return true; 
	}
	else
	{
		return false;
	}
}
