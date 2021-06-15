// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SocketIOClient/Public/SIOMessageConvert.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOMessageConvert() {}
// Cross Module References
	SOCKETIOCLIENT_API UClass* Z_Construct_UClass_USIOMessageConvert_NoRegister();
	SOCKETIOCLIENT_API UClass* Z_Construct_UClass_USIOMessageConvert();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_SocketIOClient();
// End Cross Module References
	void USIOMessageConvert::StaticRegisterNativesUSIOMessageConvert()
	{
	}
	UClass* Z_Construct_UClass_USIOMessageConvert_NoRegister()
	{
		return USIOMessageConvert::StaticClass();
	}
	struct Z_Construct_UClass_USIOMessageConvert_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USIOMessageConvert_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_SocketIOClient,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOMessageConvert_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "SIOMessageConvert.h" },
		{ "ModuleRelativePath", "Public/SIOMessageConvert.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USIOMessageConvert_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USIOMessageConvert>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USIOMessageConvert_Statics::ClassParams = {
		&USIOMessageConvert::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_USIOMessageConvert_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USIOMessageConvert_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USIOMessageConvert()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USIOMessageConvert_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USIOMessageConvert, 817731600);
	template<> SOCKETIOCLIENT_API UClass* StaticClass<USIOMessageConvert>()
	{
		return USIOMessageConvert::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USIOMessageConvert(Z_Construct_UClass_USIOMessageConvert, &USIOMessageConvert::StaticClass, TEXT("/Script/SocketIOClient"), TEXT("USIOMessageConvert"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USIOMessageConvert);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
