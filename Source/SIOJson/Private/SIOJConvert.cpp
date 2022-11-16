// Copyright 2018-current Getnamo. All Rights Reserved


#include "SIOJConvert.h"
//#include "Json.h"
#include "UObject/TextProperty.h"
#include "JsonGlobals.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Misc/FileHelper.h"
#include "SIOJsonValue.h"
#include "SIOJsonObject.h"
#include "JsonObjectConverter.h"
#include "UObject/PropertyPortFlags.h"
#include "Misc/Base64.h"

typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

//The one key that will break
#define TMAP_STRING TEXT("!__!INTERNAL_TMAP")

namespace
{
	FJsonObjectConverter::CustomExportCallback EnumOverrideExportCallback;

	//Begin partial copy of FJsonObjectConverter for BP enum workaround
	bool JsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags);
	bool JsonAttributesToUStructWithContainer(const TMap< FString, TSharedPtr<FJsonValue> >& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags);

	/** Convert JSON to property, assuming either the property is not an array or the value is an individual array element */
	bool ConvertScalarJsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags)
	{
		if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property))
		{
			if (JsonValue->Type == EJson::String)
			{
				// see if we were passed a string for the enum
				const UEnum* Enum = EnumProperty->GetEnum();
				check(Enum);
				FString StrValue = JsonValue->AsString();
				int64 IntValue = Enum->GetValueByName(FName(*StrValue));
				if (IntValue == INDEX_NONE)
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import enum %s from string value %s for property %s"), *Enum->CppType, *StrValue, *Property->GetNameCPP());
					return false;
				}
				EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(OutValue, IntValue);
			}
			else
			{
				// AsNumber will log an error for completely inappropriate types (then give us a default)
				EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(OutValue, (int64)JsonValue->AsNumber());
			}
		}
		else if (FNumericProperty *NumericProperty = CastField<FNumericProperty>(Property))
		{
			if (NumericProperty->IsEnum() && JsonValue->Type == EJson::String)
			{
				// see if we were passed a string for the enum
				const UEnum* Enum = NumericProperty->GetIntPropertyEnum();
				check(Enum); // should be assured by IsEnum()
				FString StrValue = JsonValue->AsString();
				int64 IntValue = Enum->GetValueByName(FName(*StrValue));

				//BEGIN WORKAROUND MODIFICATION
				if (IntValue == INDEX_NONE)
				{
					//Failed 'NewEnumeratorX' lookup, try via DisplayNames
					const FString LowerStrValue = StrValue.ToLower();

					//blueprints only support int8 sized enums
					int8 MaxEnum = (int8)Enum->GetMaxEnumValue();
					for (int32 i = 0; i < MaxEnum; i++)
					{
						//Case insensitive match
						if (LowerStrValue.Equals(Enum->GetDisplayNameTextByIndex(i).ToString().ToLower()))
						{
							IntValue = i;
						}
					}

					//END WORKAROUND MODIFICATION

					if (IntValue == INDEX_NONE)
					{
						UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import enum %s from string value %s for property %s"), *Enum->CppType, *StrValue, *Property->GetNameCPP());
						return false;
					}
				}
				NumericProperty->SetIntPropertyValue(OutValue, IntValue);
			}
			else if (NumericProperty->IsFloatingPoint())
			{
				// AsNumber will log an error for completely inappropriate types (then give us a default)
				NumericProperty->SetFloatingPointPropertyValue(OutValue, JsonValue->AsNumber());
			}
			else if (NumericProperty->IsInteger())
			{
				if (JsonValue->Type == EJson::String)
				{
					// parse string -> int64 ourselves so we don't lose any precision going through AsNumber (aka double)
					NumericProperty->SetIntPropertyValue(OutValue, FCString::Atoi64(*JsonValue->AsString()));
				}
				else
				{
					// AsNumber will log an error for completely inappropriate types (then give us a default)
					NumericProperty->SetIntPropertyValue(OutValue, (int64)JsonValue->AsNumber());
				}
			}
			else
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to set numeric property type %s for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FBoolProperty *BoolProperty = CastField<FBoolProperty>(Property))
		{
			// AsBool will log an error for completely inappropriate types (then give us a default)
			BoolProperty->SetPropertyValue(OutValue, JsonValue->AsBool());
		}
		else if (FStrProperty *StringProperty = CastField<FStrProperty>(Property))
		{
			// AsString will log an error for completely inappropriate types (then give us a default)
			StringProperty->SetPropertyValue(OutValue, JsonValue->AsString());
		}
		else if (FArrayProperty *ArrayProperty = CastField<FArrayProperty>(Property))
		{
			if (JsonValue->Type == EJson::Array)
			{
				TArray< TSharedPtr<FJsonValue> > ArrayValue = JsonValue->AsArray();
				int32 ArrLen = ArrayValue.Num();

				// make the output array size match
				FScriptArrayHelper Helper(ArrayProperty, OutValue);
				Helper.Resize(ArrLen);

				// set the property values
				for (int32 i = 0; i < ArrLen; ++i)
				{
					const TSharedPtr<FJsonValue>& ArrayValueItem = ArrayValue[i];
					if (ArrayValueItem.IsValid() && !ArrayValueItem->IsNull())
					{
						if (!JsonValueToFPropertyWithContainer(ArrayValueItem, ArrayProperty->Inner, Helper.GetRawPtr(i), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags))
						{
							UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to deserialize array element [%d] for property %s"), i, *Property->GetNameCPP());
							return false;
						}
					}
				}
			}
			else
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TArray from non-array JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FMapProperty* MapProperty = CastField<FMapProperty>(Property))
		{
			if (JsonValue->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> ObjectValue = JsonValue->AsObject();

				FScriptMapHelper Helper(MapProperty, OutValue);

				check(ObjectValue);

				int32 MapSize = ObjectValue->Values.Num();
				Helper.EmptyValues(MapSize);

				// set the property values
				for (const auto& Entry : ObjectValue->Values)
				{
					if (Entry.Value.IsValid() && !Entry.Value->IsNull())
					{
						int32 NewIndex = Helper.AddDefaultValue_Invalid_NeedsRehash();

						TSharedPtr<FJsonValueString> TempKeyValue = MakeShared<FJsonValueString>(Entry.Key);

						const bool bKeySuccess = JsonValueToFPropertyWithContainer(TempKeyValue, MapProperty->KeyProp, Helper.GetKeyPtr(NewIndex), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags);
						const bool bValueSuccess = JsonValueToFPropertyWithContainer(Entry.Value, MapProperty->ValueProp, Helper.GetValuePtr(NewIndex), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags);

						if (!(bKeySuccess && bValueSuccess))
						{
							UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to deserialize map element [key: %s] for property %s"), *Entry.Key, *Property->GetNameCPP());
							return false;
						}
					}
				}

				Helper.Rehash();
			}
			else
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TMap from non-object JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FSetProperty* SetProperty = CastField<FSetProperty>(Property))
		{
			if (JsonValue->Type == EJson::Array)
			{
				TArray< TSharedPtr<FJsonValue> > ArrayValue = JsonValue->AsArray();
				int32 ArrLen = ArrayValue.Num();

				FScriptSetHelper Helper(SetProperty, OutValue);

				// set the property values
				for (int32 i = 0; i < ArrLen; ++i)
				{
					const TSharedPtr<FJsonValue>& ArrayValueItem = ArrayValue[i];
					if (ArrayValueItem.IsValid() && !ArrayValueItem->IsNull())
					{
						int32 NewIndex = Helper.AddDefaultValue_Invalid_NeedsRehash();
						if (!JsonValueToFPropertyWithContainer(ArrayValueItem, SetProperty->ElementProp, Helper.GetElementPtr(NewIndex), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags))
						{
							UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to deserialize set element [%d] for property %s"), i, *Property->GetNameCPP());
							return false;
						}
					}
				}

				Helper.Rehash();
			}
			else
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TSet from non-array JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property))
		{
			if (JsonValue->Type == EJson::String)
			{
				// assume this string is already localized, so import as invariant
				TextProperty->SetPropertyValue(OutValue, FText::FromString(JsonValue->AsString()));
			}
			else if (JsonValue->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
				check(Obj.IsValid()); // should not fail if Type == EJson::Object

									  // import the subvalue as a culture invariant string
				FText Text;
				if (!FJsonObjectConverter::GetTextFromObject(Obj.ToSharedRef(), Text))
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import FText from JSON object with invalid keys for property %s"), *Property->GetNameCPP());
					return false;
				}
				TextProperty->SetPropertyValue(OutValue, Text);
			}
			else
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import FText from JSON that was neither string nor object for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FStructProperty *StructProperty = CastField<FStructProperty>(Property))
		{
			static const FName NAME_DateTime(TEXT("DateTime"));
			static const FName NAME_Color_Local(TEXT("Color"));
			static const FName NAME_LinearColor_Local(TEXT("LinearColor"));
			if (JsonValue->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
				check(Obj.IsValid()); // should not fail if Type == EJson::Object
				if (!JsonAttributesToUStructWithContainer(Obj->Values, StructProperty->Struct, OutValue, ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags))
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - FJsonObjectConverter::JsonObjectToUStruct failed for property %s"), *Property->GetNameCPP());
					return false;
				}
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetFName() == NAME_LinearColor_Local)
			{
				FLinearColor& ColorOut = *(FLinearColor*)OutValue;
				FString ColorString = JsonValue->AsString();

				FColor IntermediateColor;
				IntermediateColor = FColor::FromHex(ColorString);

				ColorOut = IntermediateColor;
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetFName() == NAME_Color)
			{
				FColor& ColorOut = *(FColor*)OutValue;
				FString ColorString = JsonValue->AsString();

				ColorOut = FColor::FromHex(ColorString);
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetFName() == NAME_DateTime)
			{
				FString DateString = JsonValue->AsString();
				FDateTime& DateTimeOut = *(FDateTime*)OutValue;
				if (DateString == TEXT("min"))
				{
					// min representable value for our date struct. Actual date may vary by platform (this is used for sorting)
					DateTimeOut = FDateTime::MinValue();
				}
				else if (DateString == TEXT("max"))
				{
					// max representable value for our date struct. Actual date may vary by platform (this is used for sorting)
					DateTimeOut = FDateTime::MaxValue();
				}
				else if (DateString == TEXT("now"))
				{
					// this value's not really meaningful from json serialization (since we don't know timezone) but handle it anyway since we're handling the other keywords
					DateTimeOut = FDateTime::UtcNow();
				}
				else if (FDateTime::ParseIso8601(*DateString, DateTimeOut))
				{
					// ok
				}
				else if (FDateTime::Parse(DateString, DateTimeOut))
				{
					// ok
				}
				else
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to import FDateTime for property %s"), *Property->GetNameCPP());
					return false;
				}
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetCppStructOps() && StructProperty->Struct->GetCppStructOps()->HasImportTextItem())
			{
				UScriptStruct::ICppStructOps* TheCppStructOps = StructProperty->Struct->GetCppStructOps();

				FString ImportTextString = JsonValue->AsString();
				const TCHAR* ImportTextPtr = *ImportTextString;
				if (!TheCppStructOps->ImportTextItem(ImportTextPtr, OutValue, PPF_None, nullptr, (FOutputDevice*)GWarn))
				{
					// Fall back to trying the tagged property approach if custom ImportTextItem couldn't get it done
					Property->ImportText_Direct(ImportTextPtr, OutValue, nullptr, PPF_None);
				}
			}
			else if (JsonValue->Type == EJson::String)
			{
				FString ImportTextString = JsonValue->AsString();
				const TCHAR* ImportTextPtr = *ImportTextString;
				Property->ImportText_Direct(ImportTextPtr, OutValue, nullptr, PPF_None);
			}
			else
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import UStruct from non-object JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FObjectProperty *ObjectProperty = CastField<FObjectProperty>(Property))
		{
			if (JsonValue->Type == EJson::Object)
			{
				UObject* Outer = GetTransientPackage();
				if (ContainerStruct->IsChildOf(UObject::StaticClass()))
				{
					Outer = (UObject*)Container;
				}

				UClass* PropertyClass = ObjectProperty->PropertyClass;
				UObject* createdObj = StaticAllocateObject(PropertyClass, Outer, NAME_None, EObjectFlags::RF_NoFlags, EInternalObjectFlags::None, false);
				(*PropertyClass->ClassConstructor)(FObjectInitializer(createdObj, PropertyClass->ClassDefaultObject, EObjectInitializerOptions::None));

				ObjectProperty->SetObjectPropertyValue(OutValue, createdObj);

				TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
				check(Obj.IsValid()); // should not fail if Type == EJson::Object
				if (!JsonAttributesToUStructWithContainer(Obj->Values, ObjectProperty->PropertyClass, createdObj, ObjectProperty->PropertyClass, createdObj, CheckFlags & (~CPF_ParmFlags), SkipFlags))
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - FJsonObjectConverter::JsonObjectToUStruct failed for property %s"), *Property->GetNameCPP());
					return false;
				}
			}
			else if (JsonValue->Type == EJson::String)
			{
				// Default to expect a string for everything else
				if (Property->ImportText_Direct(*JsonValue->AsString(), OutValue, nullptr, PPF_None) == nullptr)
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import property type %s from string value for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
					return false;
				}
			}
		}
		else
		{
			// Default to expect a string for everything else
			if (Property->ImportText_Direct(*JsonValue->AsString(), OutValue, nullptr, PPF_None) == nullptr)
			{
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import property type %s from string value for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
				return false;
			}
		}

		return true;
	}


	bool JsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags)
	{
		if (!JsonValue.IsValid())
		{
			UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Invalid value JSON key"));
			return false;
		}

		bool bArrayOrSetProperty = Property->IsA<FArrayProperty>() || Property->IsA<FSetProperty>();
		bool bJsonArray = JsonValue->Type == EJson::Array;

		if (!bJsonArray)
		{
			if (bArrayOrSetProperty)
			{
				//Begin custom workaround - support string -> binary array conversion
				FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property);
				if (ArrayProperty->Inner->IsA<FByteProperty>())
				{
					//Did we get a direct binary?
					TArray<uint8> ByteArray;
					if (FJsonValueBinary::IsBinary(JsonValue))
					{
						ByteArray = FJsonValueBinary::AsBinary(JsonValue);
					}
					//it's a string, convert use base64 to bytes
					else if(JsonValue->Type == EJson::String)
					{
						bool bDidDecodeCorrectly = FBase64::Decode(JsonValue->AsString(), ByteArray);
						if (!bDidDecodeCorrectly)
						{
							UE_LOG(LogJson, Warning, TEXT("FBase64::Decode failed on %s"), *Property->GetName());
							return false;
						}
					}
					else
					{
						UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TArray from unsupported non-array JSON key: %s"), *Property->GetName());
						return false;
					}
					//Memcpy raw arrays
					FScriptArrayHelper ArrayHelper(ArrayProperty, OutValue);
					ArrayHelper.EmptyAndAddUninitializedValues(ByteArray.Num());
					FGenericPlatformMemory::Memcpy(ArrayHelper.GetRawPtr(), ByteArray.GetData(), ByteArray.Num());
					return true;
				}
				//End custom workaround 
				UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TArray from non-array JSON key"));
				return false;
			}

			if (Property->ArrayDim != 1)
			{
				UE_LOG(LogJson, Warning, TEXT("Ignoring excess properties when deserializing %s"), *Property->GetName());
			}

			return ConvertScalarJsonValueToFPropertyWithContainer(JsonValue, Property, OutValue, ContainerStruct, Container, CheckFlags, SkipFlags);
		}

		// In practice, the ArrayDim == 1 check ought to be redundant, since nested arrays of UPropertys are not supported
		if (bArrayOrSetProperty && Property->ArrayDim == 1)
		{
			// Read into TArray
			return ConvertScalarJsonValueToFPropertyWithContainer(JsonValue, Property, OutValue, ContainerStruct, Container, CheckFlags, SkipFlags);
		}

		// We're deserializing a JSON array
		const auto& ArrayValue = JsonValue->AsArray();
		if (Property->ArrayDim < ArrayValue.Num())
		{
			UE_LOG(LogJson, Warning, TEXT("BPEnumWA-Ignoring excess properties when deserializing %s"), *Property->GetName());
		}

		// Read into native array
		int ItemsToRead = FMath::Clamp(ArrayValue.Num(), 0, Property->ArrayDim);
		for (int Index = 0; Index != ItemsToRead; ++Index)
		{
			if (!ConvertScalarJsonValueToFPropertyWithContainer(ArrayValue[Index], Property, (char*)OutValue + Index * Property->ElementSize, ContainerStruct, Container, CheckFlags, SkipFlags))
			{
				return false;
			}
		}
		return true;
	}

	bool JsonAttributesToUStructWithContainer(const TMap< FString, TSharedPtr<FJsonValue> >& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags)
	{
		if (StructDefinition == FJsonObjectWrapper::StaticStruct())
		{
			// Just copy it into the object
			FJsonObjectWrapper* ProxyObject = (FJsonObjectWrapper *)OutStruct;
			ProxyObject->JsonObject = MakeShared<FJsonObject>();
			ProxyObject->JsonObject->Values = JsonAttributes;
			return true;
		}

		int32 NumUnclaimedProperties = JsonAttributes.Num();
		if (NumUnclaimedProperties <= 0)
		{
			return true;
		}

		// iterate over the struct properties
		for (TFieldIterator<FProperty> PropIt(StructDefinition); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;

			// Check to see if we should ignore this property
			if (CheckFlags != 0 && !Property->HasAnyPropertyFlags(CheckFlags))
			{
				continue;
			}
			if (Property->HasAnyPropertyFlags(SkipFlags))
			{
				continue;
			}

			// find a json value matching this property name
			const TSharedPtr<FJsonValue>* JsonValue = JsonAttributes.Find(Property->GetName());
			if (!JsonValue)
			{
				// we allow values to not be found since this mirrors the typical UObject mantra that all the fields are optional when deserializing
				continue;
			}

			if (JsonValue->IsValid() && !(*JsonValue)->IsNull())
			{
				void* Value = Property->ContainerPtrToValuePtr<uint8>(OutStruct);
				if (!JsonValueToFPropertyWithContainer(*JsonValue, Property, Value, ContainerStruct, Container, CheckFlags, SkipFlags))
				{
					UE_LOG(LogJson, Error, TEXT("BPEnumWA-JsonObjectToUStruct - Unable to parse %s.%s from JSON"), *StructDefinition->GetName(), *Property->GetName());
					return false;
				}
			}

			if (--NumUnclaimedProperties <= 0)
			{
				// If we found all properties that were in the JsonAttributes map, there is no reason to keep looking for more.
				break;
			}
		}

		return true;
	}
	//End FJsonObjectConverter BPEnum Workaround

	class FJsonObjectConverterBPEnum : public FJsonObjectConverter
	{
	public:
		static bool JsonObjectToUStruct(const TSharedRef<FJsonObject>& JsonObject, const UStruct* StructDefinition, void* OutStruct, int64 CheckFlags, int64 SkipFlags)
		{
			return JsonAttributesToUStructWithContainer(JsonObject->Values, StructDefinition, OutStruct, StructDefinition, OutStruct, CheckFlags, SkipFlags);
		}
	};
}


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
		return FString::Printf(TEXT("%f"), JsonValue->AsNumber());
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
		TSharedPtr< FJsonObject > JsonObject = ToJsonObject(JsonString);
		return MakeShareable(new FJsonValueObject(JsonObject));
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



TSharedPtr<FJsonObject> USIOJConvert::ToJsonObject(UStruct* StructDefinition, void* StructPtr, bool IsBlueprintStruct, bool BinaryStructCppSupport /*= false */)
{
	TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (IsBlueprintStruct || BinaryStructCppSupport)
	{
		//Handle BP enum override
		if (!EnumOverrideExportCallback.IsBound())
		{
			EnumOverrideExportCallback.BindLambda([](FProperty* Property, const void* Value)
			{
				if (FByteProperty* BPEnumProperty = CastField<FByteProperty>(Property))
				{
					//Override default enum behavior by fetching display name text
					UEnum* EnumDef = BPEnumProperty->Enum;

					uint8 IntValue = *(uint8*)Value;

					//It's an enum byte
					if (EnumDef)
					{
						FString StringValue = EnumDef->GetDisplayNameTextByIndex(IntValue).ToString();
						return (TSharedPtr<FJsonValue>)MakeShared<FJsonValueString>(StringValue);
					}
					//it's a regular byte, convert to number
					else
					{
						return (TSharedPtr<FJsonValue>)MakeShared<FJsonValueNumber>(IntValue);
					}
				}
				//byte array special case
				else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
				{
					//is it a byte array?
					if (ArrayProperty->Inner->IsA<FByteProperty>())
					{
						FScriptArrayHelper ArrayHelper(ArrayProperty, Value);
						TArray<uint8> ByteArray(ArrayHelper.GetRawPtr(), ArrayHelper.Num());
						return USIOJConvert::ToJsonValue(ByteArray);
					}
				}

				// invalid
				return TSharedPtr<FJsonValue>();
			});
		}

		//Get the object keys
		FJsonObjectConverter::UStructToJsonObject(StructDefinition, StructPtr, JsonObject, 0, 0, &EnumOverrideExportCallback);

		//Wrap it into a value and pass it into the trimmer
		TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueObject(JsonObject));
		TrimValueKeyNames(JsonValue);

		//Return object with trimmed names
		return JsonValue->AsObject();
	}
	else
	{
		FJsonObjectConverter::UStructToJsonObject(StructDefinition, StructPtr, JsonObject, 0, 0);
		return JsonObject;
	}
}

TSharedPtr<FJsonObject> USIOJConvert::MakeJsonObject()
{
	return MakeShareable(new FJsonObject);
}

bool USIOJConvert::JsonObjectToUStruct(TSharedPtr<FJsonObject> JsonObject, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct /*= false*/, bool BinaryStructCppSupport /*= false*/)
{
	if (IsBlueprintStruct || BinaryStructCppSupport)
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

		/*Todo: add support for enums by pretty name and not by NewEnumeratorX
		Will require re-writing FJsonObjectConverter::JsonObjectToUStruct to lookup by display name in numeric case
		of https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/JsonUtilities/Private/JsonObjectConverter.cpp#L377,
		or getting engine pull request merge.
		*/

		//Use custom blueprint JsonObjectToUStruct to fix BPEnums
		return FJsonObjectConverterBPEnum::JsonObjectToUStruct(JsonObject.ToSharedRef(), Struct, StructPtr, 0, 0);
	}
	else
	{
		return FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), Struct, StructPtr, 0, 0);
	}
}

bool USIOJConvert::JsonFileToUStruct(const FString& FilePath, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct /*= false*/)
{
	//Read bytes from file
	TArray<uint8> OutBytes;
	if (!FFileHelper::LoadFileToArray(OutBytes, *FilePath))
	{
		return false;
	}

	//Convert to json string
	FString JsonString;
	FFileHelper::BufferToString(JsonString, OutBytes.GetData(), OutBytes.Num());

	//Read into struct
	return JsonObjectToUStruct(ToJsonObject(JsonString), Struct, StructPtr, IsBlueprintStruct);
}


bool USIOJConvert::ToJsonFile(const FString& FilePath, UStruct* Struct, void* StructPtr, bool IsBlueprintStruct /*= false*/)
{
	//Get json object with trimmed values
	TSharedPtr<FJsonObject> JsonObject = ToJsonObject(Struct, StructPtr, IsBlueprintStruct);
	TSharedPtr<FJsonValue> TrimmedValue = MakeShareable(new FJsonValueObject(JsonObject));
	TrimValueKeyNames(TrimmedValue);

	//Convert to string
	FString JsonString = ToJsonString(TrimmedValue);
	FTCHARToUTF8 Utf8String(*JsonString);

	TArray<uint8> Bytes;
	Bytes.Append((uint8*)Utf8String.Get(), Utf8String.Length());

	//flush to disk
	return FFileHelper::SaveArrayToFile(Bytes, *FilePath);
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
	FField* FieldPtr = Struct->ChildProperties;

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
		FStructProperty* SubStruct = CastField<FStructProperty>(FieldPtr);
		FArrayProperty* ArrayProp = CastField<FArrayProperty>(FieldPtr);
		FMapProperty* MapProperty = CastField<FMapProperty>(FieldPtr);

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

void USIOJConvert::SetTrimmedKeyMapForProp(TSharedPtr<FTrimmedKeyMap>& InMap, FProperty* InnerProperty)
{

	//UE_LOG(LogTemp, Log, TEXT("got prop: %s"), *InnerProperty->GetName());
	FStructProperty* SubStruct = CastField<FStructProperty>(InnerProperty);
	FArrayProperty* ArrayProp = CastField<FArrayProperty>(InnerProperty);
	FMapProperty* MapProperty = CastField<FMapProperty>(InnerProperty);

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
