// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SIOJson/Public/SIOJConvert.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJConvert() {}
// Cross Module References
	SIOJSON_API UClass* Z_Construct_UClass_USIOJConvert_NoRegister();
	SIOJSON_API UClass* Z_Construct_UClass_USIOJConvert();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_SIOJson();
// End Cross Module References
	void USIOJConvert::StaticRegisterNativesUSIOJConvert()
	{
	}
	UClass* Z_Construct_UClass_USIOJConvert_NoRegister()
	{
		return USIOJConvert::StaticClass();
	}
	struct Z_Construct_UClass_USIOJConvert_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USIOJConvert_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJson,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJConvert_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "SIOJConvert.h" },
		{ "ModuleRelativePath", "Public/SIOJConvert.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USIOJConvert_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USIOJConvert>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USIOJConvert_Statics::ClassParams = {
		&USIOJConvert::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USIOJConvert_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJConvert_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USIOJConvert()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USIOJConvert_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USIOJConvert, 2347308931);
	template<> SIOJSON_API UClass* StaticClass<USIOJConvert>()
	{
		return USIOJConvert::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USIOJConvert(Z_Construct_UClass_USIOJConvert, &USIOJConvert::StaticClass, TEXT("/Script/SIOJson"), TEXT("USIOJConvert"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USIOJConvert);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
