// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJson_init() {}
	SIOJSON_API UFunction* Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature();
	SIOJSON_API UFunction* Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature();
	SIOJSON_API UFunction* Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SIOJson()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SIOJson_OnRequestComplete__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SIOJson_OnRequestFail__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SIOJson_SIOJCallDelegate__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/SIOJson",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xADB807C7,
				0x834D6D12,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
