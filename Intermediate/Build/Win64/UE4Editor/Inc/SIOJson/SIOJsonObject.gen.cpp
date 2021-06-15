// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SIOJson/Public/SIOJsonObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJsonObject() {}
// Cross Module References
	SIOJSON_API UClass* Z_Construct_UClass_USIOJsonObject_NoRegister();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJsonObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_SIOJson();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJsonValue_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(USIOJsonObject::execSetObjectArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(USIOJsonObject*,Z_Param_Out_ObjectArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetObjectArrayField(Z_Param_FieldName,Z_Param_Out_ObjectArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetObjectArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<USIOJsonObject*>*)Z_Param__Result=P_THIS->GetObjectArrayField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetBoolArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(bool,Z_Param_Out_BoolArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBoolArrayField(Z_Param_FieldName,Z_Param_Out_BoolArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetBoolArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<bool>*)Z_Param__Result=P_THIS->GetBoolArrayField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetStringArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(FString,Z_Param_Out_StringArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetStringArrayField(Z_Param_FieldName,Z_Param_Out_StringArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetStringArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=P_THIS->GetStringArrayField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetNumberArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(float,Z_Param_Out_NumberArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetNumberArrayField(Z_Param_FieldName,Z_Param_Out_NumberArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetNumberArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<float>*)Z_Param__Result=P_THIS->GetNumberArrayField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetBinaryField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_Bytes);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBinaryField(Z_Param_FieldName,Z_Param_Out_Bytes);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetBinaryField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_OutBinary);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetBinaryField(Z_Param_FieldName,Z_Param_Out_OutBinary);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetObjectField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_OBJECT(USIOJsonObject,Z_Param_JsonObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetObjectField(Z_Param_FieldName,Z_Param_JsonObject);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetObjectField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonObject**)Z_Param__Result=P_THIS->GetObjectField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetBoolField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_UBOOL(Z_Param_InValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBoolField(Z_Param_FieldName,Z_Param_InValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetBoolField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetBoolField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetStringField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_PROPERTY(FStrProperty,Z_Param_StringValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetStringField(Z_Param_FieldName,Z_Param_StringValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetStringField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetStringField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetNumberField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Number);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetNumberField(Z_Param_FieldName,Z_Param_Number);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetNumberField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetNumberField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execMergeJsonObject)
	{
		P_GET_OBJECT(USIOJsonObject,Z_Param_InJsonObject);
		P_GET_UBOOL(Z_Param_Overwrite);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MergeJsonObject(Z_Param_InJsonObject,Z_Param_Overwrite);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_TARRAY_REF(USIOJsonValue*,Z_Param_Out_InArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetArrayField(Z_Param_FieldName,Z_Param_Out_InArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetArrayField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<USIOJsonValue*>*)Z_Param__Result=P_THIS->GetArrayField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execSetField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_GET_OBJECT(USIOJsonValue,Z_Param_JsonValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetField(Z_Param_FieldName,Z_Param_JsonValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=P_THIS->GetField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execRemoveField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RemoveField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execHasField)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_FieldName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->HasField(Z_Param_FieldName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execGetFieldNames)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=P_THIS->GetFieldNames();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execDecodeJson)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_JsonString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->DecodeJson(Z_Param_JsonString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execEncodeJsonToSingleString)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->EncodeJsonToSingleString();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execEncodeJson)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->EncodeJson();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execReset)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Reset();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJsonObject::execConstructJsonObject)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonObject**)Z_Param__Result=USIOJsonObject::ConstructJsonObject(Z_Param_WorldContextObject);
		P_NATIVE_END;
	}
	void USIOJsonObject::StaticRegisterNativesUSIOJsonObject()
	{
		UClass* Class = USIOJsonObject::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ConstructJsonObject", &USIOJsonObject::execConstructJsonObject },
			{ "DecodeJson", &USIOJsonObject::execDecodeJson },
			{ "EncodeJson", &USIOJsonObject::execEncodeJson },
			{ "EncodeJsonToSingleString", &USIOJsonObject::execEncodeJsonToSingleString },
			{ "GetArrayField", &USIOJsonObject::execGetArrayField },
			{ "GetBinaryField", &USIOJsonObject::execGetBinaryField },
			{ "GetBoolArrayField", &USIOJsonObject::execGetBoolArrayField },
			{ "GetBoolField", &USIOJsonObject::execGetBoolField },
			{ "GetField", &USIOJsonObject::execGetField },
			{ "GetFieldNames", &USIOJsonObject::execGetFieldNames },
			{ "GetNumberArrayField", &USIOJsonObject::execGetNumberArrayField },
			{ "GetNumberField", &USIOJsonObject::execGetNumberField },
			{ "GetObjectArrayField", &USIOJsonObject::execGetObjectArrayField },
			{ "GetObjectField", &USIOJsonObject::execGetObjectField },
			{ "GetStringArrayField", &USIOJsonObject::execGetStringArrayField },
			{ "GetStringField", &USIOJsonObject::execGetStringField },
			{ "HasField", &USIOJsonObject::execHasField },
			{ "MergeJsonObject", &USIOJsonObject::execMergeJsonObject },
			{ "RemoveField", &USIOJsonObject::execRemoveField },
			{ "Reset", &USIOJsonObject::execReset },
			{ "SetArrayField", &USIOJsonObject::execSetArrayField },
			{ "SetBinaryField", &USIOJsonObject::execSetBinaryField },
			{ "SetBoolArrayField", &USIOJsonObject::execSetBoolArrayField },
			{ "SetBoolField", &USIOJsonObject::execSetBoolField },
			{ "SetField", &USIOJsonObject::execSetField },
			{ "SetNumberArrayField", &USIOJsonObject::execSetNumberArrayField },
			{ "SetNumberField", &USIOJsonObject::execSetNumberField },
			{ "SetObjectArrayField", &USIOJsonObject::execSetObjectArrayField },
			{ "SetObjectField", &USIOJsonObject::execSetObjectField },
			{ "SetStringArrayField", &USIOJsonObject::execSetStringArrayField },
			{ "SetStringField", &USIOJsonObject::execSetStringField },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics
	{
		struct SIOJsonObject_eventConstructJsonObject_Parms
		{
			UObject* WorldContextObject;
			USIOJsonObject* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventConstructJsonObject_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventConstructJsonObject_Parms, ReturnValue), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Create new Json object, cannot be pure  */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "DisplayName", "Construct Json Object" },
		{ "HidePin", "WorldContextObject" },
		{ "KeyWords", "create make" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Create new Json object, cannot be pure" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "ConstructJsonObject", nullptr, nullptr, sizeof(SIOJsonObject_eventConstructJsonObject_Parms), Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics
	{
		struct SIOJsonObject_eventDecodeJson_Parms
		{
			FString JsonString;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_JsonString_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_JsonString;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_JsonString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_JsonString = { "JsonString", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventDecodeJson_Parms, JsonString), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_JsonString_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_JsonString_MetaData)) };
	void Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJsonObject_eventDecodeJson_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJsonObject_eventDecodeJson_Parms), &Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_JsonString,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Construct Json object from string */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Construct Json object from string" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "DecodeJson", nullptr, nullptr, sizeof(SIOJsonObject_eventDecodeJson_Parms), Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_DecodeJson()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_DecodeJson_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics
	{
		struct SIOJsonObject_eventEncodeJson_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventEncodeJson_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Serialize Json to string (formatted with line breaks) */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Serialize Json to string (formatted with line breaks)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "EncodeJson", nullptr, nullptr, sizeof(SIOJsonObject_eventEncodeJson_Parms), Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_EncodeJson()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_EncodeJson_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics
	{
		struct SIOJsonObject_eventEncodeJsonToSingleString_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventEncodeJsonToSingleString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Serialize Json to string (single string without line breaks) */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Serialize Json to string (single string without line breaks)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "EncodeJsonToSingleString", nullptr, nullptr, sizeof(SIOJsonObject_eventEncodeJsonToSingleString_Parms), Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics
	{
		struct SIOJsonObject_eventGetArrayField_Parms
		{
			FString FieldName;
			TArray<USIOJsonValue*> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetArrayField_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a Json Array */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a Json Array" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics
	{
		struct SIOJsonObject_eventGetBinaryField_Parms
		{
			FString FieldName;
			TArray<uint8> OutBinary;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_OutBinary_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutBinary;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetBinaryField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_OutBinary_Inner = { "OutBinary", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_OutBinary = { "OutBinary", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetBinaryField_Parms, OutBinary), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_OutBinary_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::NewProp_OutBinary,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a binary buffer array. */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a binary buffer array." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetBinaryField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetBinaryField_Parms), Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetBinaryField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetBinaryField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics
	{
		struct SIOJsonObject_eventGetBoolArrayField_Parms
		{
			FString FieldName;
			TArray<bool> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetBoolArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetBoolArrayField_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a Bool Array. Use it only if you're sure that array is uniform! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a Bool Array. Use it only if you're sure that array is uniform!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetBoolArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetBoolArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics
	{
		struct SIOJsonObject_eventGetBoolField_Parms
		{
			FString FieldName;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetBoolField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_FieldName_MetaData)) };
	void Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJsonObject_eventGetBoolField_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJsonObject_eventGetBoolField_Parms), &Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a boolean. */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a boolean." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetBoolField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetBoolField_Parms), Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetBoolField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetBoolField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetField_Statics
	{
		struct SIOJsonObject_eventGetField_Parms
		{
			FString FieldName;
			USIOJsonValue* ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetField_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a JsonValue */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a JsonValue" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetField_Parms), Z_Construct_UFunction_USIOJsonObject_GetField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics
	{
		struct SIOJsonObject_eventGetFieldNames_Parms
		{
			TArray<FString> ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetFieldNames_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Returns a list of field names that exist in the object */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Returns a list of field names that exist in the object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetFieldNames", nullptr, nullptr, sizeof(SIOJsonObject_eventGetFieldNames_Parms), Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetFieldNames()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetFieldNames_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics
	{
		struct SIOJsonObject_eventGetNumberArrayField_Parms
		{
			FString FieldName;
			TArray<float> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetNumberArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetNumberArrayField_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a Number Array. Use it only if you're sure that array is uniform!\n\x09 * Attn.!! float used instead of double to make the function blueprintable! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a Number Array. Use it only if you're sure that array is uniform!\nAttn.!! float used instead of double to make the function blueprintable!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetNumberArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetNumberArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics
	{
		struct SIOJsonObject_eventGetNumberField_Parms
		{
			FString FieldName;
			float ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetNumberField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetNumberField_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a number. Ensures that the field is present and is of type Json number.\n\x09 * Attn.!! float used instead of double to make the function blueprintable! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a number. Ensures that the field is present and is of type Json number.\nAttn.!! float used instead of double to make the function blueprintable!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetNumberField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetNumberField_Parms), Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetNumberField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetNumberField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics
	{
		struct SIOJsonObject_eventGetObjectArrayField_Parms
		{
			FString FieldName;
			TArray<USIOJsonObject*> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetObjectArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetObjectArrayField_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as an Object Array. Use it only if you're sure that array is uniform! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as an Object Array. Use it only if you're sure that array is uniform!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetObjectArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetObjectArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics
	{
		struct SIOJsonObject_eventGetObjectField_Parms
		{
			FString FieldName;
			USIOJsonObject* ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetObjectField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetObjectField_Parms, ReturnValue), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a Json object. */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a Json object." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetObjectField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetObjectField_Parms), Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetObjectField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetObjectField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics
	{
		struct SIOJsonObject_eventGetStringArrayField_Parms
		{
			FString FieldName;
			TArray<FString> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetStringArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetStringArrayField_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a String Array. Use it only if you're sure that array is uniform! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a String Array. Use it only if you're sure that array is uniform!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetStringArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetStringArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetStringArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetStringArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics
	{
		struct SIOJsonObject_eventGetStringField_Parms
		{
			FString FieldName;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetStringField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventGetStringField_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Get the field named FieldName as a string. */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Get the field named FieldName as a string." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "GetStringField", nullptr, nullptr, sizeof(SIOJsonObject_eventGetStringField_Parms), Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_GetStringField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_GetStringField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_HasField_Statics
	{
		struct SIOJsonObject_eventHasField_Parms
		{
			FString FieldName;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventHasField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_FieldName_MetaData)) };
	void Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJsonObject_eventHasField_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJsonObject_eventHasField_Parms), &Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_HasField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_HasField_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_HasField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Checks to see if the FieldName exists in the object */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Checks to see if the FieldName exists in the object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_HasField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "HasField", nullptr, nullptr, sizeof(SIOJsonObject_eventHasField_Parms), Z_Construct_UFunction_USIOJsonObject_HasField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_HasField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_HasField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_HasField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_HasField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_HasField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics
	{
		struct SIOJsonObject_eventMergeJsonObject_Parms
		{
			USIOJsonObject* InJsonObject;
			bool Overwrite;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InJsonObject;
		static void NewProp_Overwrite_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Overwrite;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::NewProp_InJsonObject = { "InJsonObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventMergeJsonObject_Parms, InJsonObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::NewProp_Overwrite_SetBit(void* Obj)
	{
		((SIOJsonObject_eventMergeJsonObject_Parms*)Obj)->Overwrite = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::NewProp_Overwrite = { "Overwrite", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJsonObject_eventMergeJsonObject_Parms), &Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::NewProp_Overwrite_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::NewProp_InJsonObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::NewProp_Overwrite,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Adds all of the fields from one json object to this one */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Adds all of the fields from one json object to this one" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "MergeJsonObject", nullptr, nullptr, sizeof(SIOJsonObject_eventMergeJsonObject_Parms), Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_MergeJsonObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_MergeJsonObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics
	{
		struct SIOJsonObject_eventRemoveField_Parms
		{
			FString FieldName;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventRemoveField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::NewProp_FieldName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Remove field named FieldName */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Remove field named FieldName" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "RemoveField", nullptr, nullptr, sizeof(SIOJsonObject_eventRemoveField_Parms), Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_RemoveField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_RemoveField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_Reset_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_Reset_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Reset all internal data */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Reset all internal data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_Reset_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "Reset", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_Reset_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_Reset_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_Reset()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_Reset_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics
	{
		struct SIOJsonObject_eventSetArrayField_Parms
		{
			FString FieldName;
			TArray<USIOJsonValue*> InArray;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_InArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray_Inner = { "InArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray = { "InArray", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetArrayField_Parms, InArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::NewProp_InArray,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an ObjectField named FieldName and value of Json Array */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an ObjectField named FieldName and value of Json Array" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics
	{
		struct SIOJsonObject_eventSetBinaryField_Parms
		{
			FString FieldName;
			TArray<uint8> Bytes;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Bytes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Bytes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Bytes;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetBinaryField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes_Inner = { "Bytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes = { "Bytes", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetBinaryField_Parms, Bytes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::NewProp_Bytes,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an BinaryField named FieldName and binary buffer array */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an BinaryField named FieldName and binary buffer array" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetBinaryField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetBinaryField_Parms), Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetBinaryField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetBinaryField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics
	{
		struct SIOJsonObject_eventSetBoolArrayField_Parms
		{
			FString FieldName;
			TArray<bool> BoolArray;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_BoolArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BoolArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_BoolArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetBoolArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray_Inner = { "BoolArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray = { "BoolArray", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetBoolArrayField_Parms, BoolArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::NewProp_BoolArray,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an ObjectField named FieldName and value of Bool Array */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an ObjectField named FieldName and value of Bool Array" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetBoolArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetBoolArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics
	{
		struct SIOJsonObject_eventSetBoolField_Parms
		{
			FString FieldName;
			bool InValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static void NewProp_InValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_InValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetBoolField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_FieldName_MetaData)) };
	void Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_InValue_SetBit(void* Obj)
	{
		((SIOJsonObject_eventSetBoolField_Parms*)Obj)->InValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJsonObject_eventSetBoolField_Parms), &Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_InValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::NewProp_InValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set a boolean field named FieldName and value of InValue */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set a boolean field named FieldName and value of InValue" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetBoolField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetBoolField_Parms), Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetBoolField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetBoolField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetField_Statics
	{
		struct SIOJsonObject_eventSetField_Parms
		{
			FString FieldName;
			USIOJsonValue* JsonValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JsonValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_JsonValue = { "JsonValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetField_Parms, JsonValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetField_Statics::NewProp_JsonValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Add a field named FieldName with a Value */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Add a field named FieldName with a Value" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetField_Parms), Z_Construct_UFunction_USIOJsonObject_SetField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics
	{
		struct SIOJsonObject_eventSetNumberArrayField_Parms
		{
			FString FieldName;
			TArray<float> NumberArray;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_NumberArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumberArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_NumberArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetNumberArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray_Inner = { "NumberArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray = { "NumberArray", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetNumberArrayField_Parms, NumberArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::NewProp_NumberArray,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an ObjectField named FieldName and value of Number Array\n\x09 * Attn.!! float used instead of double to make the function blueprintable! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an ObjectField named FieldName and value of Number Array\nAttn.!! float used instead of double to make the function blueprintable!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetNumberArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetNumberArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics
	{
		struct SIOJsonObject_eventSetNumberField_Parms
		{
			FString FieldName;
			float Number;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Number;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetNumberField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_Number = { "Number", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetNumberField_Parms, Number), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::NewProp_Number,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Add a field named FieldName with Number as value\n\x09 * Attn.!! float used instead of double to make the function blueprintable! */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Add a field named FieldName with Number as value\nAttn.!! float used instead of double to make the function blueprintable!" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetNumberField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetNumberField_Parms), Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetNumberField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetNumberField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics
	{
		struct SIOJsonObject_eventSetObjectArrayField_Parms
		{
			FString FieldName;
			TArray<USIOJsonObject*> ObjectArray;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ObjectArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ObjectArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ObjectArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetObjectArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray_Inner = { "ObjectArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray = { "ObjectArray", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetObjectArrayField_Parms, ObjectArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::NewProp_ObjectArray,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an ObjectField named FieldName and value of Ob Array */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an ObjectField named FieldName and value of Ob Array" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetObjectArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetObjectArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics
	{
		struct SIOJsonObject_eventSetObjectField_Parms
		{
			FString FieldName;
			USIOJsonObject* JsonObject;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JsonObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetObjectField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_JsonObject = { "JsonObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetObjectField_Parms, JsonObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::NewProp_JsonObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an ObjectField named FieldName and value of JsonObject */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an ObjectField named FieldName and value of JsonObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetObjectField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetObjectField_Parms), Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetObjectField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetObjectField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics
	{
		struct SIOJsonObject_eventSetStringArrayField_Parms
		{
			FString FieldName;
			TArray<FString> StringArray;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_StringArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StringArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_StringArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetStringArrayField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_FieldName_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray_Inner = { "StringArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray = { "StringArray", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetStringArrayField_Parms, StringArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::NewProp_StringArray,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Set an ObjectField named FieldName and value of String Array */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Set an ObjectField named FieldName and value of String Array" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetStringArrayField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetStringArrayField_Parms), Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetStringArrayField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetStringArrayField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics
	{
		struct SIOJsonObject_eventSetStringField_Parms
		{
			FString FieldName;
			FString StringValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FieldName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FieldName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StringValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_StringValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_FieldName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_FieldName = { "FieldName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetStringField_Parms, FieldName), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_FieldName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_FieldName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_StringValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_StringValue = { "StringValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJsonObject_eventSetStringField_Parms, StringValue), METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_StringValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_StringValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_FieldName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::NewProp_StringValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Json" },
		{ "Comment", "/** Add a field named FieldName with value of StringValue */" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Add a field named FieldName with value of StringValue" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJsonObject, nullptr, "SetStringField", nullptr, nullptr, sizeof(SIOJsonObject_eventSetStringField_Parms), Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJsonObject_SetStringField()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJsonObject_SetStringField_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USIOJsonObject_NoRegister()
	{
		return USIOJsonObject::StaticClass();
	}
	struct Z_Construct_UClass_USIOJsonObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USIOJsonObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJson,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USIOJsonObject_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USIOJsonObject_ConstructJsonObject, "ConstructJsonObject" }, // 141979631
		{ &Z_Construct_UFunction_USIOJsonObject_DecodeJson, "DecodeJson" }, // 1714960107
		{ &Z_Construct_UFunction_USIOJsonObject_EncodeJson, "EncodeJson" }, // 3006685419
		{ &Z_Construct_UFunction_USIOJsonObject_EncodeJsonToSingleString, "EncodeJsonToSingleString" }, // 2898997273
		{ &Z_Construct_UFunction_USIOJsonObject_GetArrayField, "GetArrayField" }, // 1650590752
		{ &Z_Construct_UFunction_USIOJsonObject_GetBinaryField, "GetBinaryField" }, // 4197459257
		{ &Z_Construct_UFunction_USIOJsonObject_GetBoolArrayField, "GetBoolArrayField" }, // 2834779481
		{ &Z_Construct_UFunction_USIOJsonObject_GetBoolField, "GetBoolField" }, // 2014317909
		{ &Z_Construct_UFunction_USIOJsonObject_GetField, "GetField" }, // 1194420098
		{ &Z_Construct_UFunction_USIOJsonObject_GetFieldNames, "GetFieldNames" }, // 4170654822
		{ &Z_Construct_UFunction_USIOJsonObject_GetNumberArrayField, "GetNumberArrayField" }, // 1905610151
		{ &Z_Construct_UFunction_USIOJsonObject_GetNumberField, "GetNumberField" }, // 2872372346
		{ &Z_Construct_UFunction_USIOJsonObject_GetObjectArrayField, "GetObjectArrayField" }, // 4282195618
		{ &Z_Construct_UFunction_USIOJsonObject_GetObjectField, "GetObjectField" }, // 3912904149
		{ &Z_Construct_UFunction_USIOJsonObject_GetStringArrayField, "GetStringArrayField" }, // 1143196845
		{ &Z_Construct_UFunction_USIOJsonObject_GetStringField, "GetStringField" }, // 3270342729
		{ &Z_Construct_UFunction_USIOJsonObject_HasField, "HasField" }, // 2008033290
		{ &Z_Construct_UFunction_USIOJsonObject_MergeJsonObject, "MergeJsonObject" }, // 1530938314
		{ &Z_Construct_UFunction_USIOJsonObject_RemoveField, "RemoveField" }, // 249383932
		{ &Z_Construct_UFunction_USIOJsonObject_Reset, "Reset" }, // 1440101248
		{ &Z_Construct_UFunction_USIOJsonObject_SetArrayField, "SetArrayField" }, // 1933592434
		{ &Z_Construct_UFunction_USIOJsonObject_SetBinaryField, "SetBinaryField" }, // 2413010485
		{ &Z_Construct_UFunction_USIOJsonObject_SetBoolArrayField, "SetBoolArrayField" }, // 2414357877
		{ &Z_Construct_UFunction_USIOJsonObject_SetBoolField, "SetBoolField" }, // 1306295308
		{ &Z_Construct_UFunction_USIOJsonObject_SetField, "SetField" }, // 3785256056
		{ &Z_Construct_UFunction_USIOJsonObject_SetNumberArrayField, "SetNumberArrayField" }, // 742551861
		{ &Z_Construct_UFunction_USIOJsonObject_SetNumberField, "SetNumberField" }, // 4187895234
		{ &Z_Construct_UFunction_USIOJsonObject_SetObjectArrayField, "SetObjectArrayField" }, // 2655078620
		{ &Z_Construct_UFunction_USIOJsonObject_SetObjectField, "SetObjectField" }, // 2413310055
		{ &Z_Construct_UFunction_USIOJsonObject_SetStringArrayField, "SetStringArrayField" }, // 646877904
		{ &Z_Construct_UFunction_USIOJsonObject_SetStringField, "SetStringField" }, // 3622722017
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJsonObject_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Blueprintable FJsonObject wrapper\n */" },
		{ "IncludePath", "SIOJsonObject.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/SIOJsonObject.h" },
		{ "ToolTip", "Blueprintable FJsonObject wrapper" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USIOJsonObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USIOJsonObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USIOJsonObject_Statics::ClassParams = {
		&USIOJsonObject::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USIOJsonObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJsonObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USIOJsonObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USIOJsonObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USIOJsonObject, 1794624084);
	template<> SIOJSON_API UClass* StaticClass<USIOJsonObject>()
	{
		return USIOJsonObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USIOJsonObject(Z_Construct_UClass_USIOJsonObject, &USIOJsonObject::StaticClass, TEXT("/Script/SIOJson"), TEXT("USIOJsonObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USIOJsonObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
