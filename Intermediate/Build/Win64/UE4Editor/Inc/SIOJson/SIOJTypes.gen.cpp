// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SIOJson/Public/SIOJTypes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJTypes() {}
// Cross Module References
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestStatus();
	UPackage* Z_Construct_UPackage__Script_SIOJson();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestContentType();
	SIOJSON_API UEnum* Z_Construct_UEnum_SIOJson_ESIORequestVerb();
// End Cross Module References
	static UEnum* ESIORequestStatus_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SIOJson_ESIORequestStatus, Z_Construct_UPackage__Script_SIOJson(), TEXT("ESIORequestStatus"));
		}
		return Singleton;
	}
	template<> SIOJSON_API UEnum* StaticEnum<ESIORequestStatus>()
	{
		return ESIORequestStatus_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESIORequestStatus(ESIORequestStatus_StaticEnum, TEXT("/Script/SIOJson"), TEXT("ESIORequestStatus"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SIOJson_ESIORequestStatus_Hash() { return 4271307581U; }
	UEnum* Z_Construct_UEnum_SIOJson_ESIORequestStatus()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SIOJson();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESIORequestStatus"), 0, Get_Z_Construct_UEnum_SIOJson_ESIORequestStatus_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESIORequestStatus::NotStarted", (int64)ESIORequestStatus::NotStarted },
				{ "ESIORequestStatus::Processing", (int64)ESIORequestStatus::Processing },
				{ "ESIORequestStatus::Failed", (int64)ESIORequestStatus::Failed },
				{ "ESIORequestStatus::Failed_ConnectionError", (int64)ESIORequestStatus::Failed_ConnectionError },
				{ "ESIORequestStatus::Succeeded", (int64)ESIORequestStatus::Succeeded },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "/** Enumerates the current state of an Http request */" },
				{ "Failed.Comment", "/** Finished but failed */" },
				{ "Failed.Name", "ESIORequestStatus::Failed" },
				{ "Failed.ToolTip", "Finished but failed" },
				{ "Failed_ConnectionError.Comment", "/** Failed because it was unable to connect (safe to retry) */" },
				{ "Failed_ConnectionError.Name", "ESIORequestStatus::Failed_ConnectionError" },
				{ "Failed_ConnectionError.ToolTip", "Failed because it was unable to connect (safe to retry)" },
				{ "ModuleRelativePath", "Public/SIOJTypes.h" },
				{ "NotStarted.Comment", "/** Has not been started via ProcessRequest() */" },
				{ "NotStarted.Name", "ESIORequestStatus::NotStarted" },
				{ "NotStarted.ToolTip", "Has not been started via ProcessRequest()" },
				{ "Processing.Comment", "/** Currently being ticked and processed */" },
				{ "Processing.Name", "ESIORequestStatus::Processing" },
				{ "Processing.ToolTip", "Currently being ticked and processed" },
				{ "Succeeded.Comment", "/** Finished and was successful */" },
				{ "Succeeded.Name", "ESIORequestStatus::Succeeded" },
				{ "Succeeded.ToolTip", "Finished and was successful" },
				{ "ToolTip", "Enumerates the current state of an Http request" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SIOJson,
				nullptr,
				"ESIORequestStatus",
				"ESIORequestStatus",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESIORequestContentType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SIOJson_ESIORequestContentType, Z_Construct_UPackage__Script_SIOJson(), TEXT("ESIORequestContentType"));
		}
		return Singleton;
	}
	template<> SIOJSON_API UEnum* StaticEnum<ESIORequestContentType>()
	{
		return ESIORequestContentType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESIORequestContentType(ESIORequestContentType_StaticEnum, TEXT("/Script/SIOJson"), TEXT("ESIORequestContentType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SIOJson_ESIORequestContentType_Hash() { return 3988117796U; }
	UEnum* Z_Construct_UEnum_SIOJson_ESIORequestContentType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SIOJson();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESIORequestContentType"), 0, Get_Z_Construct_UEnum_SIOJson_ESIORequestContentType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESIORequestContentType::x_www_form_urlencoded_url", (int64)ESIORequestContentType::x_www_form_urlencoded_url },
				{ "ESIORequestContentType::x_www_form_urlencoded_body", (int64)ESIORequestContentType::x_www_form_urlencoded_body },
				{ "ESIORequestContentType::json", (int64)ESIORequestContentType::json },
				{ "ESIORequestContentType::binary", (int64)ESIORequestContentType::binary },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "binary.Name", "ESIORequestContentType::binary" },
				{ "BlueprintType", "true" },
				{ "Comment", "/** Content type (json, urlencoded, etc.) used by the request */" },
				{ "json.Name", "ESIORequestContentType::json" },
				{ "ModuleRelativePath", "Public/SIOJTypes.h" },
				{ "ToolTip", "Content type (json, urlencoded, etc.) used by the request" },
				{ "x_www_form_urlencoded_body.DisplayName", "x-www-form-urlencoded (Request Body)" },
				{ "x_www_form_urlencoded_body.Name", "ESIORequestContentType::x_www_form_urlencoded_body" },
				{ "x_www_form_urlencoded_url.DisplayName", "x-www-form-urlencoded (URL)" },
				{ "x_www_form_urlencoded_url.Name", "ESIORequestContentType::x_www_form_urlencoded_url" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SIOJson,
				nullptr,
				"ESIORequestContentType",
				"ESIORequestContentType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESIORequestVerb_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SIOJson_ESIORequestVerb, Z_Construct_UPackage__Script_SIOJson(), TEXT("ESIORequestVerb"));
		}
		return Singleton;
	}
	template<> SIOJSON_API UEnum* StaticEnum<ESIORequestVerb>()
	{
		return ESIORequestVerb_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESIORequestVerb(ESIORequestVerb_StaticEnum, TEXT("/Script/SIOJson"), TEXT("ESIORequestVerb"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SIOJson_ESIORequestVerb_Hash() { return 3611405538U; }
	UEnum* Z_Construct_UEnum_SIOJson_ESIORequestVerb()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SIOJson();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESIORequestVerb"), 0, Get_Z_Construct_UEnum_SIOJson_ESIORequestVerb_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESIORequestVerb::GET", (int64)ESIORequestVerb::GET },
				{ "ESIORequestVerb::POST", (int64)ESIORequestVerb::POST },
				{ "ESIORequestVerb::PUT", (int64)ESIORequestVerb::PUT },
				{ "ESIORequestVerb::DEL", (int64)ESIORequestVerb::DEL },
				{ "ESIORequestVerb::CUSTOM", (int64)ESIORequestVerb::CUSTOM },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "/** Verb (GET, PUT, POST) used by the request */" },
				{ "CUSTOM.Comment", "/** Set CUSTOM verb by SetCustomVerb() function */" },
				{ "CUSTOM.Name", "ESIORequestVerb::CUSTOM" },
				{ "CUSTOM.ToolTip", "Set CUSTOM verb by SetCustomVerb() function" },
				{ "DEL.DisplayName", "DELETE" },
				{ "DEL.Name", "ESIORequestVerb::DEL" },
				{ "GET.Name", "ESIORequestVerb::GET" },
				{ "ModuleRelativePath", "Public/SIOJTypes.h" },
				{ "POST.Name", "ESIORequestVerb::POST" },
				{ "PUT.Name", "ESIORequestVerb::PUT" },
				{ "ToolTip", "Verb (GET, PUT, POST) used by the request" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SIOJson,
				nullptr,
				"ESIORequestVerb",
				"ESIORequestVerb",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
