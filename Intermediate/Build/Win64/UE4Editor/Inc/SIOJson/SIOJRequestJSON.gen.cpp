// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SIOJson/Public/SIOJRequestJSON.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJRequestJSON() {}
// Cross Module References
	SIOJSON_API UFunction* Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SIOJson();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJRequestJSON_NoRegister();
	SIOJSON_API UFunction* Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJRequestJSON();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJsonObject_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FLatentActionInfo();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestVerb();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestContentType();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestStatus();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics
	{
		struct _Script_SIOJson_eventOnRequestFail_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SIOJson_eventOnRequestFail_Parms, Request), Z_Construct_UClass_USIOJRequestJSON_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SIOJson, nullptr, "OnRequestFail__DelegateSignature", nullptr, nullptr, sizeof(_Script_SIOJson_eventOnRequestFail_Parms), Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics
	{
		struct _Script_SIOJson_eventOnRequestComplete_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SIOJson_eventOnRequestComplete_Parms, Request), Z_Construct_UClass_USIOJRequestJSON_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Generate a delegates for callback events */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Generate a delegates for callback events" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SIOJson, nullptr, "OnRequestComplete__DelegateSignature", nullptr, nullptr, sizeof(_Script_SIOJson_eventOnRequestComplete_Parms), Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execHasTag)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Tag);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->HasTag(Z_Param_Tag);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execRemoveTag)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Tag);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->RemoveTag(Z_Param_Tag);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execAddTag)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Tag);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddTag(Z_Param_Tag);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execApplyURL)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Url);
		P_GET_OBJECT_REF(USIOJsonObject,Z_Param_Out_Result);
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_STRUCT(FLatentActionInfo,Z_Param_LatentInfo);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ApplyURL(Z_Param_Url,Z_Param_Out_Result,Z_Param_WorldContextObject,Z_Param_LatentInfo);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execProcessURL)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Url);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ProcessURL(Z_Param_Url);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetAllResponseHeaders)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=P_THIS->GetAllResponseHeaders();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetResponseHeader)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_HeaderName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetResponseHeader(Z_Param_HeaderName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetResponseCode)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetResponseCode();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetStatus)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(ESIORequestStatus*)Z_Param__Result=P_THIS->GetStatus();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetURL)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetURL();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetResponseObject)
	{
		P_GET_OBJECT(USIOJsonObject,Z_Param_JsonObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetResponseObject(Z_Param_JsonObject);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetResponseObject)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonObject**)Z_Param__Result=P_THIS->GetResponseObject();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetRequestObject)
	{
		P_GET_OBJECT(USIOJsonObject,Z_Param_JsonObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetRequestObject(Z_Param_JsonObject);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execGetRequestObject)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJsonObject**)Z_Param__Result=P_THIS->GetRequestObject();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execCancel)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Cancel();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execResetResponseData)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ResetResponseData();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execResetRequestData)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ResetRequestData();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execResetData)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ResetData();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetHeader)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_HeaderName);
		P_GET_PROPERTY(FStrProperty,Z_Param_HeaderValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetHeader(Z_Param_HeaderName,Z_Param_HeaderValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetBinaryRequestContent)
	{
		P_GET_TARRAY_REF(uint8,Z_Param_Out_Content);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBinaryRequestContent(Z_Param_Out_Content);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetBinaryContentType)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ContentType);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBinaryContentType(Z_Param_ContentType);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetContentType)
	{
		P_GET_ENUM(ESIORequestContentType,Z_Param_ContentType);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetContentType(ESIORequestContentType(Z_Param_ContentType));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetCustomVerb)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Verb);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetCustomVerb(Z_Param_Verb);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execSetVerb)
	{
		P_GET_ENUM(ESIORequestVerb,Z_Param_Verb);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVerb(ESIORequestVerb(Z_Param_Verb));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execConstructRequestExt)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_ENUM(ESIORequestVerb,Z_Param_Verb);
		P_GET_ENUM(ESIORequestContentType,Z_Param_ContentType);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJRequestJSON**)Z_Param__Result=USIOJRequestJSON::ConstructRequestExt(Z_Param_WorldContextObject,ESIORequestVerb(Z_Param_Verb),ESIORequestContentType(Z_Param_ContentType));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USIOJRequestJSON::execConstructRequest)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USIOJRequestJSON**)Z_Param__Result=USIOJRequestJSON::ConstructRequest(Z_Param_WorldContextObject);
		P_NATIVE_END;
	}
	void USIOJRequestJSON::StaticRegisterNativesUSIOJRequestJSON()
	{
		UClass* Class = USIOJRequestJSON::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddTag", &USIOJRequestJSON::execAddTag },
			{ "ApplyURL", &USIOJRequestJSON::execApplyURL },
			{ "Cancel", &USIOJRequestJSON::execCancel },
			{ "ConstructRequest", &USIOJRequestJSON::execConstructRequest },
			{ "ConstructRequestExt", &USIOJRequestJSON::execConstructRequestExt },
			{ "GetAllResponseHeaders", &USIOJRequestJSON::execGetAllResponseHeaders },
			{ "GetRequestObject", &USIOJRequestJSON::execGetRequestObject },
			{ "GetResponseCode", &USIOJRequestJSON::execGetResponseCode },
			{ "GetResponseHeader", &USIOJRequestJSON::execGetResponseHeader },
			{ "GetResponseObject", &USIOJRequestJSON::execGetResponseObject },
			{ "GetStatus", &USIOJRequestJSON::execGetStatus },
			{ "GetURL", &USIOJRequestJSON::execGetURL },
			{ "HasTag", &USIOJRequestJSON::execHasTag },
			{ "ProcessURL", &USIOJRequestJSON::execProcessURL },
			{ "RemoveTag", &USIOJRequestJSON::execRemoveTag },
			{ "ResetData", &USIOJRequestJSON::execResetData },
			{ "ResetRequestData", &USIOJRequestJSON::execResetRequestData },
			{ "ResetResponseData", &USIOJRequestJSON::execResetResponseData },
			{ "SetBinaryContentType", &USIOJRequestJSON::execSetBinaryContentType },
			{ "SetBinaryRequestContent", &USIOJRequestJSON::execSetBinaryRequestContent },
			{ "SetContentType", &USIOJRequestJSON::execSetContentType },
			{ "SetCustomVerb", &USIOJRequestJSON::execSetCustomVerb },
			{ "SetHeader", &USIOJRequestJSON::execSetHeader },
			{ "SetRequestObject", &USIOJRequestJSON::execSetRequestObject },
			{ "SetResponseObject", &USIOJRequestJSON::execSetResponseObject },
			{ "SetVerb", &USIOJRequestJSON::execSetVerb },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics
	{
		struct SIOJRequestJSON_eventAddTag_Parms
		{
			FName Tag;
		};
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Tag;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::NewProp_Tag = { "Tag", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventAddTag_Parms, Tag), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::NewProp_Tag,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** Add tag to this request */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Add tag to this request" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "AddTag", nullptr, nullptr, sizeof(SIOJRequestJSON_eventAddTag_Parms), Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_AddTag()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_AddTag_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics
	{
		struct SIOJRequestJSON_eventApplyURL_Parms
		{
			FString Url;
			USIOJsonObject* Result;
			UObject* WorldContextObject;
			FLatentActionInfo LatentInfo;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Url_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Url;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Result;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LatentInfo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Url_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Url = { "Url", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventApplyURL_Parms, Url), METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Url_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Url_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventApplyURL_Parms, Result), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventApplyURL_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_LatentInfo = { "LatentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventApplyURL_Parms, LatentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Url,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_Result,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::NewProp_LatentInfo,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Open URL in latent mode */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "HidePin", "WorldContextObject" },
		{ "Latent", "" },
		{ "LatentInfo", "LatentInfo" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Open URL in latent mode" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ApplyURL", nullptr, nullptr, sizeof(SIOJRequestJSON_eventApplyURL_Parms), Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ApplyURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ApplyURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_Cancel_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_Cancel_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Cancel latent response waiting  */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Cancel latent response waiting" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_Cancel_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "Cancel", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_Cancel_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_Cancel_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_Cancel()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_Cancel_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics
	{
		struct SIOJRequestJSON_eventConstructRequest_Parms
		{
			UObject* WorldContextObject;
			USIOJRequestJSON* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventConstructRequest_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventConstructRequest_Parms, ReturnValue), Z_Construct_UClass_USIOJRequestJSON_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Creates new request (totally empty) */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "DisplayName", "Construct Json Request (Empty)" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Creates new request (totally empty)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ConstructRequest", nullptr, nullptr, sizeof(SIOJRequestJSON_eventConstructRequest_Parms), Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics
	{
		struct SIOJRequestJSON_eventConstructRequestExt_Parms
		{
			UObject* WorldContextObject;
			ESIORequestVerb Verb;
			ESIORequestContentType ContentType;
			USIOJRequestJSON* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Verb_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Verb;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ContentType_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ContentType;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventConstructRequestExt_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_Verb_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_Verb = { "Verb", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventConstructRequestExt_Parms, Verb), Z_Construct_UEnum_SIOJson_ESIORequestVerb, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_ContentType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_ContentType = { "ContentType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventConstructRequestExt_Parms, ContentType), Z_Construct_UEnum_SIOJson_ESIORequestContentType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventConstructRequestExt_Parms, ReturnValue), Z_Construct_UClass_USIOJRequestJSON_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_Verb_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_Verb,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_ContentType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_ContentType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Creates new request with defined verb and content type */" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "DisplayName", "Construct Json Request" },
		{ "HidePin", "WorldContextObject" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Creates new request with defined verb and content type" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ConstructRequestExt", nullptr, nullptr, sizeof(SIOJRequestJSON_eventConstructRequestExt_Parms), Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics
	{
		struct SIOJRequestJSON_eventGetAllResponseHeaders_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetAllResponseHeaders_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Get list of all response headers */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get list of all response headers" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetAllResponseHeaders", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetAllResponseHeaders_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics
	{
		struct SIOJRequestJSON_eventGetRequestObject_Parms
		{
			USIOJsonObject* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetRequestObject_Parms, ReturnValue), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Get the Request Json object */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get the Request Json object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetRequestObject", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetRequestObject_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics
	{
		struct SIOJRequestJSON_eventGetResponseCode_Parms
		{
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetResponseCode_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Get the response code of the last query */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get the response code of the last query" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetResponseCode", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetResponseCode_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics
	{
		struct SIOJRequestJSON_eventGetResponseHeader_Parms
		{
			FString HeaderName;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HeaderName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_HeaderName;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_HeaderName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_HeaderName = { "HeaderName", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetResponseHeader_Parms, HeaderName), METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_HeaderName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_HeaderName_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetResponseHeader_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_HeaderName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Get value of desired response header */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get value of desired response header" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetResponseHeader", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetResponseHeader_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics
	{
		struct SIOJRequestJSON_eventGetResponseObject_Parms
		{
			USIOJsonObject* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetResponseObject_Parms, ReturnValue), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Get the Response Json object */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get the Response Json object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetResponseObject", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetResponseObject_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics
	{
		struct SIOJRequestJSON_eventGetStatus_Parms
		{
			ESIORequestStatus ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetStatus_Parms, ReturnValue), Z_Construct_UEnum_SIOJson_ESIORequestStatus, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::NewProp_ReturnValue_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Get status of http request */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get status of http request" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetStatus", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetStatus_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetStatus()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetStatus_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics
	{
		struct SIOJRequestJSON_eventGetURL_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventGetURL_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Get url of http request */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Get url of http request" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "GetURL", nullptr, nullptr, sizeof(SIOJRequestJSON_eventGetURL_Parms), Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_GetURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_GetURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics
	{
		struct SIOJRequestJSON_eventHasTag_Parms
		{
			FName Tag;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Tag;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::NewProp_Tag = { "Tag", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventHasTag_Parms, Tag), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SIOJRequestJSON_eventHasTag_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SIOJRequestJSON_eventHasTag_Parms), &Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::NewProp_Tag,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** See if this request contains the supplied tag */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "See if this request contains the supplied tag" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "HasTag", nullptr, nullptr, sizeof(SIOJRequestJSON_eventHasTag_Parms), Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_HasTag()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_HasTag_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics
	{
		struct SIOJRequestJSON_eventProcessURL_Parms
		{
			FString Url;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Url_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Url;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::NewProp_Url_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::NewProp_Url = { "Url", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventProcessURL_Parms, Url), METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::NewProp_Url_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::NewProp_Url_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::NewProp_Url,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Open URL with current setup */" },
		{ "CPP_Default_Url", "http://alyamkin.com" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Open URL with current setup" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ProcessURL", nullptr, nullptr, sizeof(SIOJRequestJSON_eventProcessURL_Parms), Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ProcessURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ProcessURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics
	{
		struct SIOJRequestJSON_eventRemoveTag_Parms
		{
			FName Tag;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_Tag;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::NewProp_Tag = { "Tag", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventRemoveTag_Parms, Tag), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventRemoveTag_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::NewProp_Tag,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** \n\x09 * Remove tag from this request \n\x09 *\n\x09 * @return Number of removed elements \n\x09 */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Remove tag from this request\n\n@return Number of removed elements" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "RemoveTag", nullptr, nullptr, sizeof(SIOJRequestJSON_eventRemoveTag_Parms), Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_RemoveTag()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_RemoveTag_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ResetData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ResetData_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Utility" },
		{ "Comment", "/** Reset all internal saved data */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Reset all internal saved data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ResetData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ResetData", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ResetData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ResetData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ResetData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ResetData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Reset saved request data */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Reset saved request data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ResetRequestData", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Reset saved response data */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Reset saved response data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "ResetResponseData", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics
	{
		struct SIOJRequestJSON_eventSetBinaryContentType_Parms
		{
			FString ContentType;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ContentType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ContentType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::NewProp_ContentType_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::NewProp_ContentType = { "ContentType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetBinaryContentType_Parms, ContentType), METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::NewProp_ContentType_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::NewProp_ContentType_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::NewProp_ContentType,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Set content type of the request for binary post data */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set content type of the request for binary post data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetBinaryContentType", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetBinaryContentType_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics
	{
		struct SIOJRequestJSON_eventSetBinaryRequestContent_Parms
		{
			TArray<uint8> Content;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Content_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Content_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Content;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content_Inner = { "Content", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content = { "Content", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetBinaryRequestContent_Parms, Content), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::NewProp_Content,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Set content of the request for binary post data */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set content of the request for binary post data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetBinaryRequestContent", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetBinaryRequestContent_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics
	{
		struct SIOJRequestJSON_eventSetContentType_Parms
		{
			ESIORequestContentType ContentType;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ContentType_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ContentType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::NewProp_ContentType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::NewProp_ContentType = { "ContentType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetContentType_Parms, ContentType), Z_Construct_UEnum_SIOJson_ESIORequestContentType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::NewProp_ContentType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::NewProp_ContentType,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Set content type to the request. If you're using the x-www-form-urlencoded, \n\x09 * params/constaints should be defined as key=ValueString pairs from Json data */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set content type to the request. If you're using the x-www-form-urlencoded,\nparams/constaints should be defined as key=ValueString pairs from Json data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetContentType", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetContentType_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetContentType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetContentType_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics
	{
		struct SIOJRequestJSON_eventSetCustomVerb_Parms
		{
			FString Verb;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Verb;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::NewProp_Verb = { "Verb", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetCustomVerb_Parms, Verb), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::NewProp_Verb,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Set custom verb to the request */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set custom verb to the request" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetCustomVerb", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetCustomVerb_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics
	{
		struct SIOJRequestJSON_eventSetHeader_Parms
		{
			FString HeaderName;
			FString HeaderValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HeaderName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_HeaderName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HeaderValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_HeaderValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderName = { "HeaderName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetHeader_Parms, HeaderName), METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderValue = { "HeaderValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetHeader_Parms, HeaderValue), METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::NewProp_HeaderValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Sets optional header info */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Sets optional header info" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetHeader", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetHeader_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetHeader()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetHeader_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics
	{
		struct SIOJRequestJSON_eventSetRequestObject_Parms
		{
			USIOJsonObject* JsonObject;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JsonObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::NewProp_JsonObject = { "JsonObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetRequestObject_Parms, JsonObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::NewProp_JsonObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Set the Request Json object */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set the Request Json object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetRequestObject", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetRequestObject_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics
	{
		struct SIOJRequestJSON_eventSetResponseObject_Parms
		{
			USIOJsonObject* JsonObject;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JsonObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::NewProp_JsonObject = { "JsonObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetResponseObject_Parms, JsonObject), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::NewProp_JsonObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Set the Response Json object */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set the Response Json object" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetResponseObject", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetResponseObject_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics
	{
		struct SIOJRequestJSON_eventSetVerb_Parms
		{
			ESIORequestVerb Verb;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Verb_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Verb;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::NewProp_Verb_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::NewProp_Verb = { "Verb", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SIOJRequestJSON_eventSetVerb_Parms, Verb), Z_Construct_UEnum_SIOJson_ESIORequestVerb, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::NewProp_Verb_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::NewProp_Verb,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::Function_MetaDataParams[] = {
		{ "Category", "SIOJ|Request" },
		{ "Comment", "/** Set verb to the request */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Set verb to the request" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USIOJRequestJSON, nullptr, "SetVerb", nullptr, nullptr, sizeof(SIOJRequestJSON_eventSetVerb_Parms), Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USIOJRequestJSON_SetVerb()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USIOJRequestJSON_SetVerb_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USIOJRequestJSON_NoRegister()
	{
		return USIOJRequestJSON::StaticClass();
	}
	struct Z_Construct_UClass_USIOJRequestJSON_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnRequestComplete_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRequestComplete;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnRequestFail_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRequestFail;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ResponseContent_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ResponseContent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsValidJsonResponse_MetaData[];
#endif
		static void NewProp_bIsValidJsonResponse_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsValidJsonResponse;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bShouldHaveBinaryResponse_MetaData[];
#endif
		static void NewProp_bShouldHaveBinaryResponse_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bShouldHaveBinaryResponse;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RequestJsonObj_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RequestJsonObj;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_RequestBytes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RequestBytes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RequestBytes;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BinaryContentType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_BinaryContentType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ResponseJsonObj_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ResponseJsonObj;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USIOJRequestJSON_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJson,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USIOJRequestJSON_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USIOJRequestJSON_AddTag, "AddTag" }, // 1085419294
		{ &Z_Construct_UFunction_USIOJRequestJSON_ApplyURL, "ApplyURL" }, // 1490973805
		{ &Z_Construct_UFunction_USIOJRequestJSON_Cancel, "Cancel" }, // 2493565230
		{ &Z_Construct_UFunction_USIOJRequestJSON_ConstructRequest, "ConstructRequest" }, // 865581897
		{ &Z_Construct_UFunction_USIOJRequestJSON_ConstructRequestExt, "ConstructRequestExt" }, // 577040284
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetAllResponseHeaders, "GetAllResponseHeaders" }, // 839406173
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetRequestObject, "GetRequestObject" }, // 2355232417
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetResponseCode, "GetResponseCode" }, // 2007580753
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetResponseHeader, "GetResponseHeader" }, // 3211805489
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetResponseObject, "GetResponseObject" }, // 858783371
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetStatus, "GetStatus" }, // 182590357
		{ &Z_Construct_UFunction_USIOJRequestJSON_GetURL, "GetURL" }, // 3260939854
		{ &Z_Construct_UFunction_USIOJRequestJSON_HasTag, "HasTag" }, // 3196162217
		{ &Z_Construct_UFunction_USIOJRequestJSON_ProcessURL, "ProcessURL" }, // 2002656382
		{ &Z_Construct_UFunction_USIOJRequestJSON_RemoveTag, "RemoveTag" }, // 104660654
		{ &Z_Construct_UFunction_USIOJRequestJSON_ResetData, "ResetData" }, // 4034358647
		{ &Z_Construct_UFunction_USIOJRequestJSON_ResetRequestData, "ResetRequestData" }, // 1206656452
		{ &Z_Construct_UFunction_USIOJRequestJSON_ResetResponseData, "ResetResponseData" }, // 2406944038
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetBinaryContentType, "SetBinaryContentType" }, // 3756785598
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetBinaryRequestContent, "SetBinaryRequestContent" }, // 1381988520
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetContentType, "SetContentType" }, // 2371382864
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetCustomVerb, "SetCustomVerb" }, // 641860953
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetHeader, "SetHeader" }, // 2839822201
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetRequestObject, "SetRequestObject" }, // 3225506916
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetResponseObject, "SetResponseObject" }, // 2646780398
		{ &Z_Construct_UFunction_USIOJRequestJSON_SetVerb, "SetVerb" }, // 1050021026
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * General helper class http requests via blueprints\n */" },
		{ "IncludePath", "SIOJRequestJSON.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "General helper class http requests via blueprints" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestComplete_MetaData[] = {
		{ "Category", "SIOJ|Event" },
		{ "Comment", "/** Event occured when the request has been completed */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Event occured when the request has been completed" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestComplete = { "OnRequestComplete", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, OnRequestComplete), Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestComplete_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestComplete_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestFail_MetaData[] = {
		{ "Category", "SIOJ|Event" },
		{ "Comment", "/** Event occured when the request wasn't successfull */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Event occured when the request wasn't successfull" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestFail = { "OnRequestFail", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, OnRequestFail), Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestFail_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestFail_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseContent_MetaData[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Request response stored as a string */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Request response stored as a string" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseContent = { "ResponseContent", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, ResponseContent), METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseContent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseContent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse_MetaData[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** Is the response valid JSON? */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Is the response valid JSON?" },
	};
#endif
	void Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse_SetBit(void* Obj)
	{
		((USIOJRequestJSON*)Obj)->bIsValidJsonResponse = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse = { "bIsValidJsonResponse", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(USIOJRequestJSON), &Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse_SetBit, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse_MetaData[] = {
		{ "Category", "SIOJ|Response" },
		{ "Comment", "/** If this is true it will call back on the binary callback instead of json */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "If this is true it will call back on the binary callback instead of json" },
	};
#endif
	void Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse_SetBit(void* Obj)
	{
		((USIOJRequestJSON*)Obj)->bShouldHaveBinaryResponse = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse = { "bShouldHaveBinaryResponse", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(USIOJRequestJSON), &Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse_SetBit, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestJsonObj_MetaData[] = {
		{ "Comment", "/** Internal request data stored as JSON */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Internal request data stored as JSON" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestJsonObj = { "RequestJsonObj", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, RequestJsonObj), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestJsonObj_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestJsonObj_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes_Inner = { "RequestBytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes_MetaData[] = {
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes = { "RequestBytes", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, RequestBytes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_BinaryContentType_MetaData[] = {
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_BinaryContentType = { "BinaryContentType", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, BinaryContentType), METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_BinaryContentType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_BinaryContentType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseJsonObj_MetaData[] = {
		{ "Comment", "/** Response data stored as JSON */" },
		{ "ModuleRelativePath", "Public/SIOJRequestJSON.h" },
		{ "ToolTip", "Response data stored as JSON" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseJsonObj = { "ResponseJsonObj", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJRequestJSON, ResponseJsonObj), Z_Construct_UClass_USIOJsonObject_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseJsonObj_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseJsonObj_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USIOJRequestJSON_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestComplete,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_OnRequestFail,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseContent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bIsValidJsonResponse,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_bShouldHaveBinaryResponse,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestJsonObj,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_RequestBytes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_BinaryContentType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJRequestJSON_Statics::NewProp_ResponseJsonObj,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USIOJRequestJSON_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USIOJRequestJSON>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USIOJRequestJSON_Statics::ClassParams = {
		&USIOJRequestJSON::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USIOJRequestJSON_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USIOJRequestJSON_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJRequestJSON_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USIOJRequestJSON()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USIOJRequestJSON_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USIOJRequestJSON, 448527842);
	template<> SIOJSON_API UClass* StaticClass<USIOJRequestJSON>()
	{
		return USIOJRequestJSON::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USIOJRequestJSON(Z_Construct_UClass_USIOJRequestJSON, &USIOJRequestJSON::StaticClass, TEXT("/Script/SIOJson"), TEXT("USIOJRequestJSON"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USIOJRequestJSON);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
