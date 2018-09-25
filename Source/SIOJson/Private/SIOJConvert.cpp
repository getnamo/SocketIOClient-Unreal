// Copyright 2018-current Getnamo. All Rights Reserved


#include "SIOJConvert.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "SIOJsonValue.h"
#include "SIOJsonObject.h"

typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

//The one key that will break
#define TMAP_STRING TEXT("!__!INTERNAL_TMAP")


FString FTrimmedKeyMap::ToString()
{
	FString SubMapString;
	for (auto Pair : SubMap)
	{
		FString PairString = FString::Printf(TEXT("{%s:%s}"), *Pair.Key, *Pair.Value->ToString());
		SubMapString.Append(PairString);
		SubMapString.Append(",");
	}
	return FString::Printf(TEXT("{%s:%s}"), *LongKey, *SubMapString);
}

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

#if PLATFORM_WINDOWS
#pragma endregion ToJsonValue
#endif

TSharedPtr<FJsonValue> USIOJConvert::JsonStringToJsonValue(const FString& JsonString)
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

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(const TSharedPtr<FJsonObject>& JsonObject)
{
	return MakeShareable(new FJsonValueObject(JsonObject));
}

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(const FString& StringValue)
{
	return MakeShareable(new FJsonValueString(StringValue));
}

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(double NumberValue)
{
	return MakeShareable(new FJsonValueNumber(NumberValue));
}

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(bool BoolValue)
{
	return MakeShareable(new FJsonValueBoolean(BoolValue));
}

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(const TArray<uint8>& BinaryValue)
{
	return MakeShareable(new FJsonValueBinary(BinaryValue));
}

TSharedPtr<FJsonValue> USIOJConvert::ToJsonValue(const TArray<TSharedPtr<FJsonValue>>& ArrayValue)
{
	return MakeShareable(new FJsonValueArray(ArrayValue));
}

#if PLATFORM_WINDOWS
#pragma endregion ToJsonValue
#endif

TArray<TSharedPtr<FJsonValue>> USIOJConvert::JsonStringToJsonArray(const FString& JsonString)
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
	if (IsBlueprintStruct)
	{
		//Get the object keys
		TSharedPtr<FJsonObject> Object = ToJsonObject(Struct, StructPtr, false);

		//Wrap it into a value and pass it into the trimmer
		TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueObject(Object));
		TrimValueKeyNames(JsonValue);

		//Return object with trimmed names
		return JsonValue->AsObject();
	}
	else
	{
		TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		bool success = FJsonObjectConverter::UStructToJsonObject(Struct, StructPtr, JsonObject, 0, 0);
		return JsonObject;
	}
}

TSharedPtr<FJsonObject> USIOJConvert::MakeJsonObject()
{
	return MakeShareable(new FJsonObject);
}

bool USIOJConvert::JsonObjectToUStruct(TSharedPtr<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct)
{
	if (IsBlueprintStruct)
	{
		//Json object we pass will have their trimmed BP names, e.g. boolKey vs boolKey_8_EDBB36654CF43866C376DE921373AF23
		//so we have to match them to the verbose versions, get a map of the names

		TSharedPtr<FTrimmedKeyMap> KeyMap = MakeShareable(new FTrimmedKeyMap);
		SetTrimmedKeyMapForStruct(KeyMap, Struct);

		//Print our keymap for debug
		//UE_LOG(LogTemp, Log, TEXT("Keymap: %s"), *KeyMap->ToString());

		//Adjust our passed in JsonObject to use the long key names
		TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueObject(JsonObject));
		ReplaceJsonValueNamesWithMap(JsonValue, KeyMap);

		//Now it's a regular struct and will fill correctly
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

			//keep attempting sub keys even if we have a valid string
			auto SubValue = Pair.Value;
			TrimValueKeyNames(SubValue);

			if (DidNeedTrimming)
			{
				//Replace field names with the trimmed key
				JsonObject->SetField(TrimmedKey, SubValue);
				JsonObject->RemoveField(Key);
			}
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("TrimValueKeyNames:: uncaught type is: %d"), (int)JsonValue->Type);
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

void USIOJConvert::SetTrimmedKeyMapForStruct(TSharedPtr<FTrimmedKeyMap>& InMap, UStruct* Struct)
{
	//Get the child fields
	UField* FieldPtr = Struct->Children;

	//If it hasn't been set, the long key is the json standardized long name
	if (InMap->LongKey.IsEmpty())
	{
		InMap->LongKey = FJsonObjectConverter::StandardizeCase(Struct->GetName());
	}

	//For each child field...
	while (FieldPtr != nullptr)
	{
		//Map our trimmed name to our full name
		const FString& LowerKey = FJsonObjectConverter::StandardizeCase(FieldPtr->GetName());
		FString TrimmedKey;
		bool DidTrim = TrimKey(LowerKey, TrimmedKey);

		//Set the key map
		TSharedPtr<FTrimmedKeyMap> SubMap = MakeShareable(new FTrimmedKeyMap);
		SubMap->LongKey = LowerKey;

		//No-trim case, trim = long
		if (!DidTrim)
		{
			TrimmedKey = SubMap->LongKey;
		}

		//Did we get a substructure?
		UStructProperty* SubStruct = Cast<UStructProperty>(FieldPtr);
		UArrayProperty* ArrayProp = Cast<UArrayProperty>(FieldPtr);
		UMapProperty* MapProperty = Cast<UMapProperty>(FieldPtr);

		if (SubStruct != nullptr)
		{
			//We did, embed the sub-map
			SetTrimmedKeyMapForStruct(SubMap, SubStruct->Struct);
		}

		//Did we get a sub-array?
		else if (ArrayProp != nullptr)
		{
			//set the inner map for the inner property
			//UE_LOG(LogTemp, Log, TEXT("found array: %s"), *ArrayProp->GetName());
			SetTrimmedKeyMapForProp(SubMap, ArrayProp->Inner);
		}
		else if (MapProperty != nullptr)
		{
			//UE_LOG(LogTemp, Log, TEXT("I'm a tmap: %s"), *MapProperty->GetName());
			SetTrimmedKeyMapForProp(SubMap, MapProperty);
		}

		//Debug types
		/*
		UProperty* ObjectProp = Cast<UProperty>(FieldPtr);
		if (ObjectProp)
		{
			UE_LOG(LogTemp, Log, TEXT("found map: %s, %s, type: %s, %s"),
				*ObjectProp->GetName(),
				*ObjectProp->GetNameCPP(),
				*ObjectProp->GetClass()->GetFName().ToString(),
				*ObjectProp->GetCPPType());
		}*/

		InMap->SubMap.Add(TrimmedKey, SubMap);
		//UE_LOG(LogTemp, Log, TEXT("long: %s, trim: %s, is struct: %d"), *SubMap->LongKey, *TrimmedKey, SubStruct != NULL);

		FieldPtr = FieldPtr->Next;
	}

	//UE_LOG(LogTemp, Log, TEXT("Final map: %d"), InMap->SubMap.Num());
}

void USIOJConvert::SetTrimmedKeyMapForProp(TSharedPtr<FTrimmedKeyMap>& InMap, UProperty* InnerProperty)
{

	//UE_LOG(LogTemp, Log, TEXT("got prop: %s"), *InnerProperty->GetName());
	UStructProperty* SubStruct = Cast<UStructProperty>(InnerProperty);
	UArrayProperty* ArrayProp = Cast<UArrayProperty>(InnerProperty);
	UMapProperty* MapProperty = Cast<UMapProperty>(InnerProperty);

	if (SubStruct != nullptr)
	{
		//We did, embed the sub-map
		SetTrimmedKeyMapForStruct(InMap, SubStruct->Struct);
	}
	//Did we get a sub-array?
	else if (ArrayProp != nullptr)
	{
		SetTrimmedKeyMapForProp(InMap, ArrayProp->Inner);
	}
	else if (MapProperty != nullptr)
	{
		//Make a special submap with special TMAP identifier key
		TSharedPtr<FTrimmedKeyMap> SubMap = MakeShareable(new FTrimmedKeyMap);
		SubMap->LongKey = TMAP_STRING;
		InMap->SubMap.Add(SubMap->LongKey, SubMap);

		//Take the value property and set it as it's unique child
		SetTrimmedKeyMapForProp(SubMap, MapProperty->ValueProp);

		//Each child in the JSON object map will use the same structure (it's a UE4 limitation of maps anyway
	}
}

void USIOJConvert::ReplaceJsonValueNamesWithMap(TSharedPtr<FJsonValue>& JsonValue, TSharedPtr<FTrimmedKeyMap> KeyMap)
{
	if (JsonValue->Type == EJson::Object)
	{
		//Go through each key in the object
		auto Object = JsonValue->AsObject();
		auto SubMap = KeyMap->SubMap;
		auto AllValues = Object->Values;

		FString PreviewPreValue = USIOJConvert::ToJsonString(Object);
		//UE_LOG(LogTemp, Log, TEXT("Rep::PreObject: <%s>"), *PreviewPreValue);

		for (auto Pair : AllValues)
		{
			if (SubMap.Contains(TMAP_STRING))
			{
				FString TMapString = FString(TMAP_STRING);
				//If we found a tmap, replace each sub key with list of keys
				ReplaceJsonValueNamesWithMap(Pair.Value, SubMap[TMapString]);
			}
			else if (SubMap.Num() > 0 && SubMap.Contains(Pair.Key))
			{
				//Get the long key for entry
				const FString& LongKey = SubMap[Pair.Key]->LongKey;

				//loop nested structures
				ReplaceJsonValueNamesWithMap(Pair.Value, SubMap[Pair.Key]);

				if (Pair.Key != LongKey)
				{
					//finally set the field and remove the old field
					Object->SetField(LongKey, Pair.Value);
					Object->RemoveField(Pair.Key);
				}
			}
		}

		FString PreviewPostValue = USIOJConvert::ToJsonString(Object);
		//UE_LOG(LogTemp, Log, TEXT("Rep::PostObject: <%s>"), *PreviewPostValue);
	}
	else if (JsonValue->Type == EJson::Array)
	{
		auto Array = JsonValue->AsArray();
		for (auto Item : Array)
		{
			//UE_LOG(LogTemp, Log, TEXT("%s"), *Item->AsString());
			ReplaceJsonValueNamesWithMap(Item, KeyMap);
		}
	}
}