// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SIOJson/Public/SIOJLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJLibrary() {}
// Cross Module References
	SIOJSON_API UFunction* Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SIOJson();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJRequestJSON_NoRegister();
	SIOJSON_API UScriptStruct* Z_Construct_UScriptStruct_FSIOJCallResponse();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJLibrary_NoRegister();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestVerb();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestContentType();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJsonObject_NoRegister();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJsonValue_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FLatentActionInfo();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics
	{
		struct _Script_SIOJson_eventSIOJCallDelegate_Parms
		{
			USIOJRequestJSON* Request;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Request;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SIOJson_eventSIOJCallDelegate_Parms, Request), Z_Construct_UClass_USIOJRequestJSON_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SIOJson, nullptr, "SIOJCallDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_SIOJson_eventSIOJCallDelegate_Parms), Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
class UScriptStruct* FSIOJCallResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SIOJSON_API uint32 Get_Z_Construct_UScriptStruct_FSIOJCallResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSIOJCallResponse, Z_Construct_UPackage__Script_SIOJson(), TEXT("SIOJCallResponse"), sizeof(FSIOJCallResponse), Get_Z_Construct_UScriptStruct_FSIOJCallResponse_Hash());
	}
	return Singleton;
}
template<> SIOJSON_API UScriptStruct* StaticStruct<FSIOJCallResponse>()
{
	return FSIOJCallResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSIOJCallResponse(FSIOJCallResponse::StaticStruct, TEXT("/Script/SIOJson"), TEXT("SIOJCallResponse"), false, nullptr, nullptr);
static struct FScriptStruct_SIOJson_StaticRegisterNativesFSIOJCallResponse
{
	FScriptStruct_SIOJson_StaticRegisterNativesFSIOJCallResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SIOJCallResponse")),new UScriptStruct::TCppStructOps<FSIOJCallResponse>);
	}
} ScriptStruct_SIOJson_StaticRegisterNativesFSIOJCallResponse;
	struct Z_Construct_UScriptStruct_FSIOJCallResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Request_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Request;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Callback_MetaData[];
#endif
		static const UE4CodeGen_Private::FDelegatePropertyParams NewProp_Callback;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSIOJCallResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Request_MetaData[] = {
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSIOJCallResponse, Request), Z_Construct_UClass_USIOJRequestJSON_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Request_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Request_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_WorldContextObject_MetaData[] = {
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSIOJCallResponse, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_WorldContextObject_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_WorldContextObject_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Callback_MetaData[] = {
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FDelegatePropertyParams Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Callback = { "Callback", nullptr, (EPropertyFlags)0x0010000000080000, UE4CodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSIOJCallResponse, Callback), Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Callback_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Callback_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Request,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::NewProp_Callback,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJson,
		nullptr,
		&NewStructOps,
		"SIOJCallResponse",
		sizeof(FSIOJCallResponse),
		alignof(FSIOJCallResponse),
		Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000005),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSIOJCallResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSIOJCallResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SIOJson();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SIOJCallResponse"), sizeof(FSIOJCallResponse), Get_Z_Construct_UScriptStruct_FSIOJCallResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSIOJCallResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSIOJCallResponse_Hash() { return 1524310959U; }
	DEFINE_FUNCTION(USIOJLibrary::execGetURLBinary)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_PROPERTY(FStrProperty,Z_Param_URL);
		P_GET_ENUM(ESIORequestVerb,Z_Param_Verb);
		P_GET_ENUM(ESIORequestContentType,Z_Param_ContentType);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_OutResultData);
		P_GET_STRUCT(FLatentActionInfo,Z_Param_LatentInfo);
		P_FINISH;
		P_NATIVE_BEGIN;
		USIOJLibrary::GetURLBinary(Z_Param_WorldContextObject,Z_Param_URL,ESIORequestVerb(Z_Param_Verb),ESIORequestContentType(Z_Param_ContentType),Z_Param_Out_OutResultData,Z_Param_LatentInfo);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execCallURL)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_PROPERTY(FStrProperty,Z_Param_URL);
		P_GET_ENUM(ESIORequestVerb,Z_Param_Verb);
		P_GET_ENUM(ESIORequestContentType,Z_Param_ContentType);
		P_GET_OBJECT(USIOJsonObject,Z_Param_SIOJJson);
		P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_Callback);
		P_FINISH;
		P_NATIVE_BEGIN;
		USIOJLibrary::CallURL(Z_Param_WorldContextObject,Z_Param_URL,ESIORequestVerb(Z_Param_Verb),ESIORequestContentType(Z_Param_ContentType),Z_Param_SIOJJson,FSIOJCallDelegate(Z_Param_Out_Callback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonValueToJsonObject)
	{
		P_GET_OBJECT(USIOJsonValue,Z_Param_InValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonObject**)Z_Param__Result=USIOJLibrary::Conv_JsonValueToJsonObject(Z_Param_InValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonObjectToString)
	{
		P_GET_OBJECT(USIOJsonObject,Z_Param_InObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=USIOJLibrary::Conv_JsonObjectToString(Z_Param_InObject);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonValueToBytes)
	{
		P_GET_OBJECT(USIOJsonValue,Z_Param_InValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<uint8>*)Z_Param__Result=USIOJLibrary::Conv_JsonValueToBytes(Z_Param_InValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonValueToBool)
	{
		P_GET_OBJECT(USIOJsonValue,Z_Param_InValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=USIOJLibrary::Conv_JsonValueToBool(Z_Param_InValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonValueToFloat)
	{
		P_GET_OBJECT(USIOJsonValue,Z_Param_InValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=USIOJLibrary::Conv_JsonValueToFloat(Z_Param_InValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonValueToInt)
	{
		P_GET_OBJECT(USIOJsonValue,Z_Param_InValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=USIOJLibrary::Conv_JsonValueToInt(Z_Param_InValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_BoolToJsonValue)
	{
		P_GET_UBOOL(Z_Param_InBool);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_BoolToJsonValue(Z_Param_InBool);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_FloatToJsonValue)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_InFloat);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_FloatToJsonValue(Z_Param_InFloat);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_IntToJsonValue)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_InInt);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_IntToJsonValue(Z_Param_InInt);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_StringToJsonValue)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_StringToJsonValue(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_BytesToJsonValue)
	{
		P_GET_TARRAY_REF(uint8,Z_Param_Out_InBytes);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_BytesToJsonValue(Z_Param_Out_InBytes);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_JsonObjectToJsonValue)
	{
		P_GET_OBJECT(USIOJsonObject,Z_Param_InObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_JsonObjectToJsonValue(Z_Param_InObject);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execConv_ArrayToJsonValue)
	{
		P_GET_TARRAY_REF(USIOJsonValue*,Z_Param_Out_InArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonValue**)Z_Param__Result=USIOJLibrary::Conv_ArrayToJsonValue(Z_Param_Out_InArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execStringToJsonValueArray)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_JsonString);
		P_GET_TARRAY_REF(USIOJsonValue*,Z_Param_Out_OutJsonValueArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=USIOJLibrary::StringToJsonValueArray(Z_Param_JsonString,Z_Param_Out_OutJsonValueArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execBase64DecodeBytes)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Source);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_Dest);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=USIOJLibrary::Base64DecodeBytes(Z_Param_Source,Z_Param_Out_Dest);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execBase64Decode)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Source);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Dest);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=USIOJLibrary::Base64Decode(Z_Param_Source,Z_Param_Out_Dest);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execBase64EncodeBytes)
	{
		P_GET_TARRAY_REF(uint8,Z_Param_Out_Source);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=USIOJLibrary::Base64EncodeBytes(Z_Param_Out_Source);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execBase64Encode)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Source);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=USIOJLibrary::Base64Encode(Z_Param_Source);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJLibrary::execPercentEncode)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Source);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=USIOJLibrary::PercentEncode(Z_Param_Source);
		P_NATIVE_END;
	}
	void USIOJLibrary::StaticRegisterNativesUSIOJLibrary()
	{
		UClass* Class = USIOJLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Base64Decode", &USIOJLibrary::execBase64Decode },
			{ "Base64DecodeBytes", &USIOJLibrary::execBase64DecodeBytes },
			{ "Base64Encode", &USIOJLibrary::execBase64Encode },
			{ "Base64EncodeBytes", &USIOJLibrary::execBase64EncodeBytes },
			{ "CallURL", &USIOJLibrary::execCallURL },
			{ "Conv_ArrayToJsonValue", &USIOJLibrary::execConv_ArrayToJsonValue },
			{ "Conv_BoolToJsonValue", &USIOJLibrary::execConv_BoolToJsonValue },
			{ "Conv_BytesToJsonValue", &USIOJLibrary::execConv_BytesToJsonValue },
			{ "Conv_FloatToJsonValue", &USIOJLibrary::execConv_FloatToJsonValue },
			{ "Conv_IntToJsonValue", &USIOJLibrary::execConv_IntToJsonValue },
			{ "Conv_JsonObjectToJsonValue", &USIOJLibrary::execConv_JsonObjectToJsonValue },
			{ "Conv_JsonObjectToString", &USIOJLibrary::execConv_JsonObjectToString },
			{ "Conv_JsonValueToBool", &USIOJLibrary::execConv_JsonValueToBool },
			{ "Conv_JsonValueToBytes", &USIOJLibrary::execConv_JsonValueToBytes },
			{ "Conv_JsonValueToFloat", &USIOJLibrary::execConv_JsonValueToFloat },
			{ "Conv_JsonValueToInt", &USIOJLibrary::execConv_JsonValueToInt },
			{ "Conv_JsonValueToJsonObject", &USIOJLibrary::execConv_JsonValueToJsonObject },
			{ "Conv_StringToJsonValue", &USIOJLibrary::execConv_StringToJsonValue },
			{ "GetURLBinary", &USIOJLibrary::execGetURLBinary },
			{ "JsonObjectToStruct", &USIOJLibrary::execJsonObjectToStruct },
			{ "LoadJsonFileToStruct", &USIOJLibrary::execLoadJsonFileToStruct },
			{ "PercentEncode", &USIOJLibrary::execPercentEncode },
			{ "SaveStructToJsonFile", &USIOJLibrary::execSaveStructToJsonFile },
			{ "StringToJsonValueArray", &USIOJLibrary::execStringToJsonValueArray },
			{ "StructToJsonObject", &USIOJLibrary::execStructToJsonObject },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics
	{
		struct SIOJLibrary_eventBase64Decode_Parms
		{
			FString Source;
			FString Dest;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Source;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Dest;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Source_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64Decode_Parms, Source), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Source_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Source_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Dest = { "Dest", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64Decode_Parms, Dest), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventBase64Decode_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventBase64Decode_Parms), &Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Source,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_Dest,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/**\n\x09 * Decodes a Base64 string into a FString\n\x09 *\n\x09 * @param Source\x09The stringified data to convert\n\x09 * @param Dest\x09\x09The out buffer that will be filled with the decoded data\n\x09 * @return\x09\x09\x09True if the buffer was decoded, false if it failed to decode\n\x09 */" },
		{ "DisplayName", "Base64 Decode (To String)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Decodes a Base64 string into a FString\n\n@param Source        The stringified data to convert\n@param Dest          The out buffer that will be filled with the decoded data\n@return                      True if the buffer was decoded, false if it failed to decode" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Base64Decode", nullptr, nullptr, sizeof(SIOJLibrary_eventBase64Decode_Parms), Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Base64Decode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Base64Decode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics
	{
		struct SIOJLibrary_eventBase64DecodeBytes_Parms
		{
			FString Source;
			TArray<uint8> Dest;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Source;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Dest_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Dest;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Source_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64DecodeBytes_Parms, Source), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Source_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Source_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Dest_Inner = { "Dest", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Dest = { "Dest", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64DecodeBytes_Parms, Dest), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventBase64DecodeBytes_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventBase64DecodeBytes_Parms), &Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Source,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Dest_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_Dest,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/**\n\x09 * Decodes a Base64 string into a Byte array\n\x09 *\n\x09 * @param Source\x09The stringified data to convert\n\x09 * @param Dest\x09\x09The out buffer that will be filled with the decoded data\n\x09 * @return\x09\x09\x09True if the buffer was decoded, false if it failed to decode\n\x09 */" },
		{ "DisplayName", "Base64 Decode (To Bytes)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Decodes a Base64 string into a Byte array\n\n@param Source        The stringified data to convert\n@param Dest          The out buffer that will be filled with the decoded data\n@return                      True if the buffer was decoded, false if it failed to decode" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Base64DecodeBytes", nullptr, nullptr, sizeof(SIOJLibrary_eventBase64DecodeBytes_Parms), Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics
	{
		struct SIOJLibrary_eventBase64Encode_Parms
		{
			FString Source;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Source;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_Source_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64Encode_Parms, Source), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_Source_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_Source_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64Encode_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_Source,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/**\n\x09 * Encodes a FString into a Base64 string\n\x09 *\n\x09 * @param Source\x09The string data to convert\n\x09 * @return\x09\x09\x09""A string that encodes the binary data in a way that can be safely transmitted via various Internet protocols\n\x09 */" },
		{ "DisplayName", "Base64 Encode (String)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Encodes a FString into a Base64 string\n\n@param Source        The string data to convert\n@return                      A string that encodes the binary data in a way that can be safely transmitted via various Internet protocols" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Base64Encode", nullptr, nullptr, sizeof(SIOJLibrary_eventBase64Encode_Parms), Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Base64Encode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Base64Encode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics
	{
		struct SIOJLibrary_eventBase64EncodeBytes_Parms
		{
			TArray<uint8> Source;
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Source_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Source;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source_Inner = { "Source", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64EncodeBytes_Parms, Source), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventBase64EncodeBytes_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_Source,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/**\n\x09 * Encodes a Byte array into a Base64 string\n\x09 *\n\x09 * @param Source\x09The string data to convert\n\x09 * @return\x09\x09\x09""A string that encodes the binary data in a way that can be safely transmitted via various Internet protocols\n\x09 */" },
		{ "DisplayName", "Base64 Encode (Bytes)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Encodes a Byte array into a Base64 string\n\n@param Source        The string data to convert\n@return                      A string that encodes the binary data in a way that can be safely transmitted via various Internet protocols" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Base64EncodeBytes", nullptr, nullptr, sizeof(SIOJLibrary_eventBase64EncodeBytes_Parms), Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_CallURL_Statics
	{
		struct SIOJLibrary_eventCallURL_Parms
		{
			UObject* WorldContextObject;
			FString URL;
			ESIORequestVerb Verb;
			ESIORequestContentType ContentType;
			USIOJsonObject* SIOJJson;
			FScriptDelegate Callback;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_URL_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_URL;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Verb_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Verb;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ContentType_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ContentType;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SIOJJson;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Callback_MetaData[];
#endif
		static const UE4CodeGen_Private::FDelegatePropertyParams NewProp_Callback;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventCallURL_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_URL_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_URL = { "URL", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventCallURL_Parms, URL), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_URL_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_URL_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Verb_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Verb = { "Verb", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventCallURL_Parms, Verb), Z_Construct_UEnum_SIOJson_ESIORequestVerb, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_ContentType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_ContentType = { "ContentType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventCallURL_Parms, ContentType), Z_Construct_UEnum_SIOJson_ESIORequestContentType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_SIOJJson = { "SIOJJson", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventCallURL_Parms, SIOJJson), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Callback_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Callback = { "Callback", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventCallURL_Parms, Callback), Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Callback_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Callback_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_URL,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Verb_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Verb,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_ContentType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_ContentType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_SIOJJson,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::NewProp_Callback,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** Easy way to process http requests */" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Easy way to process http requests" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "CallURL", nullptr, nullptr, sizeof(SIOJLibrary_eventCallURL_Parms), Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_CallURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_CallURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_ArrayToJsonValue_Parms
		{
			TArray<USIOJsonValue*> InArray;
			USIOJsonValue* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InArray_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InArray_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_InArray;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray_Inner = { "InArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray = { "InArray", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_ArrayToJsonValue_Parms, InArray), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_ArrayToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_InArray,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "Comment", "//ToJsonValue\n" },
		{ "DisplayName", "To JsonValue (Array)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "ToJsonValue" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_ArrayToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_ArrayToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_BoolToJsonValue_Parms
		{
			bool InBool;
			USIOJsonValue* ReturnValue;
		};
		static void NewProp_InBool_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_InBool;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::NewProp_InBool_SetBit(void* Obj)
	{
		((SIOJLibrary_eventConv_BoolToJsonValue_Parms*)Obj)->InBool = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::NewProp_InBool = { "InBool", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventConv_BoolToJsonValue_Parms), &Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::NewProp_InBool_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_BoolToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::NewProp_InBool,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To JsonValue (Bool)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_BoolToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_BoolToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_BytesToJsonValue_Parms
		{
			TArray<uint8> InBytes;
			USIOJsonValue* ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_InBytes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InBytes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_InBytes;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes_Inner = { "InBytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes = { "InBytes", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_BytesToJsonValue_Parms, InBytes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_BytesToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_InBytes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To JsonValue (Bytes)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_BytesToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_BytesToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_FloatToJsonValue_Parms
		{
			float InFloat;
			USIOJsonValue* ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_InFloat;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::NewProp_InFloat = { "InFloat", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_FloatToJsonValue_Parms, InFloat), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_FloatToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::NewProp_InFloat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To JsonValue (Float)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_FloatToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_FloatToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_IntToJsonValue_Parms
		{
			int32 InInt;
			USIOJsonValue* ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_InInt;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::NewProp_InInt = { "InInt", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_IntToJsonValue_Parms, InInt), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_IntToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::NewProp_InInt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To JsonValue (Integer)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_IntToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_IntToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_JsonObjectToJsonValue_Parms
		{
			USIOJsonObject* InObject;
			USIOJsonValue* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::NewProp_InObject = { "InObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonObjectToJsonValue_Parms, InObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonObjectToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::NewProp_InObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To JsonValue (JsonObject)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonObjectToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonObjectToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics
	{
		struct SIOJLibrary_eventConv_JsonObjectToString_Parms
		{
			USIOJsonObject* InObject;
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InObject;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::NewProp_InObject = { "InObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonObjectToString_Parms, InObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonObjectToString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::NewProp_InObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "Comment", "//ToString - these never get called sadly, kismet library get display name takes priority\n" },
		{ "CompactNodeTitle", "->" },
		{ "DisplayName", "To String (SIOJsonObject)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "ToString - these never get called sadly, kismet library get display name takes priority" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonObjectToString", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonObjectToString_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics
	{
		struct SIOJLibrary_eventConv_JsonValueToBool_Parms
		{
			USIOJsonValue* InValue;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InValue;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToBool_Parms, InValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventConv_JsonValueToBool_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventConv_JsonValueToBool_Parms), &Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::NewProp_InValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To Bool (JsonValue)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonValueToBool", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonValueToBool_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics
	{
		struct SIOJLibrary_eventConv_JsonValueToBytes_Parms
		{
			USIOJsonValue* InValue;
			TArray<uint8> ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InValue;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToBytes_Parms, InValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToBytes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::NewProp_InValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To Bytes (JsonValue)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonValueToBytes", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonValueToBytes_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics
	{
		struct SIOJLibrary_eventConv_JsonValueToFloat_Parms
		{
			USIOJsonValue* InValue;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToFloat_Parms, InValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToFloat_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::NewProp_InValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To Float (JsonValue)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonValueToFloat", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonValueToFloat_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics
	{
		struct SIOJLibrary_eventConv_JsonValueToInt_Parms
		{
			USIOJsonValue* InValue;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InValue;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToInt_Parms, InValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToInt_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::NewProp_InValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "Comment", "//To Native Types\n" },
		{ "DisplayName", "To Integer (JsonValue)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "To Native Types" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonValueToInt", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonValueToInt_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics
	{
		struct SIOJLibrary_eventConv_JsonValueToJsonObject_Parms
		{
			USIOJsonValue* InValue;
			USIOJsonObject* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InValue;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToJsonObject_Parms, InValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_JsonValueToJsonObject_Parms, ReturnValue), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::NewProp_InValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To Object (JsonValue)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_JsonValueToJsonObject", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_JsonValueToJsonObject_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics
	{
		struct SIOJLibrary_eventConv_StringToJsonValue_Parms
		{
			FString InString;
			USIOJsonValue* ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_StringToJsonValue_Parms, InString), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_InString_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_InString_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventConv_StringToJsonValue_Parms, ReturnValue), Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_InString,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::Function_MetaDataParams[] = {
		{ "BlueprintAutocast", "" },
		{ "Category", "Utilities|SocketIO" },
		{ "DisplayName", "To JsonValue (String)" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "Conv_StringToJsonValue", nullptr, nullptr, sizeof(SIOJLibrary_eventConv_StringToJsonValue_Parms), Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics
	{
		struct SIOJLibrary_eventGetURLBinary_Parms
		{
			UObject* WorldContextObject;
			FString URL;
			ESIORequestVerb Verb;
			ESIORequestContentType ContentType;
			TArray<uint8> OutResultData;
			FLatentActionInfo LatentInfo;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_URL_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_URL;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Verb_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Verb;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ContentType_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ContentType;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_OutResultData_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutResultData;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LatentInfo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventGetURLBinary_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_URL_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_URL = { "URL", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventGetURLBinary_Parms, URL), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_URL_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_URL_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_Verb_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_Verb = { "Verb", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventGetURLBinary_Parms, Verb), Z_Construct_UEnum_SIOJson_ESIORequestVerb, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_ContentType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_ContentType = { "ContentType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventGetURLBinary_Parms, ContentType), Z_Construct_UEnum_SIOJson_ESIORequestContentType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_OutResultData_Inner = { "OutResultData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_OutResultData = { "OutResultData", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventGetURLBinary_Parms, OutResultData), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_LatentInfo = { "LatentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventGetURLBinary_Parms, LatentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_URL,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_Verb_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_Verb,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_ContentType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_ContentType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_OutResultData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_OutResultData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::NewProp_LatentInfo,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** Easy way to fetch resources using get */" },
		{ "Latent", "" },
		{ "LatentInfo", "LatentInfo" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Easy way to fetch resources using get" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "GetURLBinary", nullptr, nullptr, sizeof(SIOJLibrary_eventGetURLBinary_Parms), Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_GetURLBinary()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_GetURLBinary_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics
	{
		struct SIOJLibrary_eventJsonObjectToStruct_Parms
		{
			USIOJsonObject* JsonObject;
			TFieldPath<FProperty> AnyStruct;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JsonObject;
		static const UE4CodeGen_Private::FFieldPathPropertyParams NewProp_AnyStruct;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_JsonObject = { "JsonObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventJsonObjectToStruct_Parms, JsonObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFieldPathPropertyParams Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_AnyStruct = { "AnyStruct", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::FieldPath, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventJsonObjectToStruct_Parms, AnyStruct), &FProperty::StaticClass, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventJsonObjectToStruct_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventJsonObjectToStruct_Parms), &Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_JsonObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_AnyStruct,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::Function_MetaDataParams[] = {
		{ "Category", "SocketIOFunctions" },
		{ "Comment", "/**\n\x09* Uses the reflection system to fill an unreal struct from data defined in JsonObject.\n\x09*\n\x09* @param JsonObject\x09\x09The source JsonObject for properties to fill\n\x09* @param AnyStruct\x09\x09The struct you wish to fill\n\x09* @return\x09\x09\x09\x09Whether all properties filled correctly\n\x09*/" },
		{ "CustomStructureParam", "AnyStruct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Uses the reflection system to fill an unreal struct from data defined in JsonObject.\n\n@param JsonObject             The source JsonObject for properties to fill\n@param AnyStruct              The struct you wish to fill\n@return                               Whether all properties filled correctly" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "JsonObjectToStruct", nullptr, nullptr, sizeof(SIOJLibrary_eventJsonObjectToStruct_Parms), Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics
	{
		struct SIOJLibrary_eventLoadJsonFileToStruct_Parms
		{
			FString FilePath;
			TFieldPath<FProperty> AnyStruct;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FilePath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FilePath;
		static const UE4CodeGen_Private::FFieldPathPropertyParams NewProp_AnyStruct;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_FilePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_FilePath = { "FilePath", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventLoadJsonFileToStruct_Parms, FilePath), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_FilePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_FilePath_MetaData)) };
	const UE4CodeGen_Private::FFieldPathPropertyParams Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_AnyStruct = { "AnyStruct", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::FieldPath, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventLoadJsonFileToStruct_Parms, AnyStruct), &FProperty::StaticClass, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventLoadJsonFileToStruct_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventLoadJsonFileToStruct_Parms), &Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_FilePath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_AnyStruct,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::Function_MetaDataParams[] = {
		{ "Category", "SocketIOFunctions" },
		{ "CustomStructureParam", "AnyStruct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "LoadJsonFileToStruct", nullptr, nullptr, sizeof(SIOJLibrary_eventLoadJsonFileToStruct_Parms), Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics
	{
		struct SIOJLibrary_eventPercentEncode_Parms
		{
			FString Source;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Source;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_Source_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventPercentEncode_Parms, Source), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_Source_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_Source_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventPercentEncode_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_Source,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** Applies percent-encoding to text */" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Applies percent-encoding to text" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "PercentEncode", nullptr, nullptr, sizeof(SIOJLibrary_eventPercentEncode_Parms), Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_PercentEncode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_PercentEncode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics
	{
		struct SIOJLibrary_eventSaveStructToJsonFile_Parms
		{
			TFieldPath<FProperty> AnyStruct;
			FString FilePath;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FFieldPathPropertyParams NewProp_AnyStruct;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FilePath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FilePath;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFieldPathPropertyParams Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_AnyStruct = { "AnyStruct", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::FieldPath, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventSaveStructToJsonFile_Parms, AnyStruct), &FProperty::StaticClass, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_FilePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_FilePath = { "FilePath", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventSaveStructToJsonFile_Parms, FilePath), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_FilePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_FilePath_MetaData)) };
	void Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventSaveStructToJsonFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventSaveStructToJsonFile_Parms), &Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_AnyStruct,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_FilePath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "SocketIOFunctions" },
		{ "Comment", "//Convenience - Saving/Loading structs from files\n" },
		{ "CustomStructureParam", "AnyStruct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Convenience - Saving/Loading structs from files" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "SaveStructToJsonFile", nullptr, nullptr, sizeof(SIOJLibrary_eventSaveStructToJsonFile_Parms), Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics
	{
		struct SIOJLibrary_eventStringToJsonValueArray_Parms
		{
			FString JsonString;
			TArray<USIOJsonValue*> OutJsonValueArray;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_JsonString_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_JsonString;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OutJsonValueArray_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutJsonValueArray;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_JsonString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_JsonString = { "JsonString", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventStringToJsonValueArray_Parms, JsonString), METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_JsonString_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_JsonString_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_OutJsonValueArray_Inner = { "OutJsonValueArray", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USIOJsonValue_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_OutJsonValueArray = { "OutJsonValueArray", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventStringToJsonValueArray_Parms, OutJsonValueArray), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJLibrary_eventStringToJsonValueArray_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJLibrary_eventStringToJsonValueArray_Parms), &Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_JsonString,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_OutJsonValueArray_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_OutJsonValueArray,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/**\n\x09* Decodes a json string into an array of stringified json Values\n\x09*\n\x09* @param JsonString\x09\x09\x09\x09Input stringified json\n\x09* @param OutJsonValueArray\x09\x09The decoded Array of JsonValue \n\x09*/" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Decodes a json string into an array of stringified json Values\n\n@param JsonString                             Input stringified json\n@param OutJsonValueArray              The decoded Array of JsonValue" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "StringToJsonValueArray", nullptr, nullptr, sizeof(SIOJLibrary_eventStringToJsonValueArray_Parms), Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics
	{
		struct SIOJLibrary_eventStructToJsonObject_Parms
		{
			TFieldPath<FProperty> AnyStruct;
			USIOJsonObject* ReturnValue;
		};
		static const UE4CodeGen_Private::FFieldPathPropertyParams NewProp_AnyStruct;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFieldPathPropertyParams Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::NewProp_AnyStruct = { "AnyStruct", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::FieldPath, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventStructToJsonObject_Parms, AnyStruct), &FProperty::StaticClass, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJLibrary_eventStructToJsonObject_Parms, ReturnValue), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::NewProp_AnyStruct,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SocketIOFunctions" },
		{ "Comment", "/**\n\x09* Uses the reflection system to convert an unreal struct into a JsonObject\n\x09*\n\x09* @param AnyStruct\x09\x09The struct you wish to convert\n\x09* @return\x09\x09\x09\x09""Converted Json Object\n\x09*/" },
		{ "CustomStructureParam", "AnyStruct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Uses the reflection system to convert an unreal struct into a JsonObject\n\n@param AnyStruct              The struct you wish to convert\n@return                               Converted Json Object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJLibrary, nullptr, "StructToJsonObject", nullptr, nullptr, sizeof(SIOJLibrary_eventStructToJsonObject_Parms), Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJLibrary_StructToJsonObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJLibrary_StructToJsonObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USIOJLibrary_NoRegister()
	{
		return USIOJLibrary::StaticClass();
	}
	struct Z_Construct_UClass_USIOJLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USIOJLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJson,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USIOJLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USIOJLibrary_Base64Decode, "Base64Decode" }, // 2131689652
		{ &Z_Construct_UFunction_USIOJLibrary_Base64DecodeBytes, "Base64DecodeBytes" }, // 58645601
		{ &Z_Construct_UFunction_USIOJLibrary_Base64Encode, "Base64Encode" }, // 2575392857
		{ &Z_Construct_UFunction_USIOJLibrary_Base64EncodeBytes, "Base64EncodeBytes" }, // 1686485510
		{ &Z_Construct_UFunction_USIOJLibrary_CallURL, "CallURL" }, // 3045542794
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_ArrayToJsonValue, "Conv_ArrayToJsonValue" }, // 3763660185
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_BoolToJsonValue, "Conv_BoolToJsonValue" }, // 638671008
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_BytesToJsonValue, "Conv_BytesToJsonValue" }, // 1255315688
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_FloatToJsonValue, "Conv_FloatToJsonValue" }, // 1536592161
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_IntToJsonValue, "Conv_IntToJsonValue" }, // 2062372616
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToJsonValue, "Conv_JsonObjectToJsonValue" }, // 484909633
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonObjectToString, "Conv_JsonObjectToString" }, // 3904212269
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBool, "Conv_JsonValueToBool" }, // 3283715048
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToBytes, "Conv_JsonValueToBytes" }, // 66018747
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToFloat, "Conv_JsonValueToFloat" }, // 2606666738
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToInt, "Conv_JsonValueToInt" }, // 3582622406
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_JsonValueToJsonObject, "Conv_JsonValueToJsonObject" }, // 1880903246
		{ &Z_Construct_UFunction_USIOJLibrary_Conv_StringToJsonValue, "Conv_StringToJsonValue" }, // 2968322006
		{ &Z_Construct_UFunction_USIOJLibrary_GetURLBinary, "GetURLBinary" }, // 901408895
		{ &Z_Construct_UFunction_USIOJLibrary_JsonObjectToStruct, "JsonObjectToStruct" }, // 767797740
		{ &Z_Construct_UFunction_USIOJLibrary_LoadJsonFileToStruct, "LoadJsonFileToStruct" }, // 3675308824
		{ &Z_Construct_UFunction_USIOJLibrary_PercentEncode, "PercentEncode" }, // 1656664875
		{ &Z_Construct_UFunction_USIOJLibrary_SaveStructToJsonFile, "SaveStructToJsonFile" }, // 4189009235
		{ &Z_Construct_UFunction_USIOJLibrary_StringToJsonValueArray, "StringToJsonValueArray" }, // 1399647812
		{ &Z_Construct_UFunction_USIOJLibrary_StructToJsonObject, "StructToJsonObject" }, // 2400905647
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Usefull tools for REST communications\n */" },
		{ "IncludePath", "SIOJLibrary.h" },
		{ "ModuleRelativePath", "Public/SIOJLibrary.h" },
		{ "ToolTip", "Usefull tools for REST communications" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USIOJLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USIOJLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USIOJLibrary_Statics::ClassParams = {
		&USIOJLibrary::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_USIOJLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USIOJLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USIOJLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USIOJLibrary, 2942324956);
	template<> SIOJSON_API UClass* StaticClass<USIOJLibrary>()
	{
		return USIOJLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USIOJLibrary(Z_Construct_UClass_USIOJLibrary, &USIOJLibrary::StaticClass, TEXT("/Script/SIOJson"), TEXT("USIOJLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USIOJLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
