// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SIOJEditorPlugin/Public/SIOJ_BreakJson.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSIOJ_BreakJson() {}
// Cross Module References
	SIOJEDITORPLUGIN_API UEnum* Z_Construct_UEnum_SIOJEditorPlugin_ESIOJ_JsonType();
	UPackage* Z_Construct_UPackage__Script_SIOJEditorPlugin();
	SIOJEDITORPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FSIOJ_NamedType();
	SIOJEDITORPLUGIN_API UClass* Z_Construct_UClass_USIOJ_BreakJson_NoRegister();
	SIOJEDITORPLUGIN_API UClass* Z_Construct_UClass_USIOJ_BreakJson();
	BLUEPRINTGRAPH_API UClass* Z_Construct_UClass_UK2Node();
// End Cross Module References
	static UEnum* ESIOJ_JsonType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SIOJEditorPlugin_ESIOJ_JsonType, Z_Construct_UPackage__Script_SIOJEditorPlugin(), TEXT("ESIOJ_JsonType"));
		}
		return Singleton;
	}
	template<> SIOJEDITORPLUGIN_API UEnum* StaticEnum<ESIOJ_JsonType>()
	{
		return ESIOJ_JsonType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESIOJ_JsonType(ESIOJ_JsonType_StaticEnum, TEXT("/Script/SIOJEditorPlugin"), TEXT("ESIOJ_JsonType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SIOJEditorPlugin_ESIOJ_JsonType_Hash() { return 1292328485U; }
	UEnum* Z_Construct_UEnum_SIOJEditorPlugin_ESIOJ_JsonType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SIOJEditorPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESIOJ_JsonType"), 0, Get_Z_Construct_UEnum_SIOJEditorPlugin_ESIOJ_JsonType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESIOJ_JsonType::JSON_Bool", (int64)ESIOJ_JsonType::JSON_Bool },
				{ "ESIOJ_JsonType::JSON_Number", (int64)ESIOJ_JsonType::JSON_Number },
				{ "ESIOJ_JsonType::JSON_String", (int64)ESIOJ_JsonType::JSON_String },
				{ "ESIOJ_JsonType::JSON_Object", (int64)ESIOJ_JsonType::JSON_Object },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "JSON_Bool.Comment", "//JSON_Null UMETA(DisplayName = \"Null\"),\n" },
				{ "JSON_Bool.DisplayName", "Boolean" },
				{ "JSON_Bool.Name", "ESIOJ_JsonType::JSON_Bool" },
				{ "JSON_Bool.ToolTip", "JSON_Null UMETA(DisplayName = \"Null\")," },
				{ "JSON_Number.DisplayName", "Number" },
				{ "JSON_Number.Name", "ESIOJ_JsonType::JSON_Number" },
				{ "JSON_Object.DisplayName", "Object" },
				{ "JSON_Object.Name", "ESIOJ_JsonType::JSON_Object" },
				{ "JSON_String.DisplayName", "String" },
				{ "JSON_String.Name", "ESIOJ_JsonType::JSON_String" },
				{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SIOJEditorPlugin,
				nullptr,
				"ESIOJ_JsonType",
				"ESIOJ_JsonType",
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
class UScriptStruct* FSIOJ_NamedType::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SIOJEDITORPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FSIOJ_NamedType_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSIOJ_NamedType, Z_Construct_UPackage__Script_SIOJEditorPlugin(), TEXT("SIOJ_NamedType"), sizeof(FSIOJ_NamedType), Get_Z_Construct_UScriptStruct_FSIOJ_NamedType_Hash());
	}
	return Singleton;
}
template<> SIOJEDITORPLUGIN_API UScriptStruct* StaticStruct<FSIOJ_NamedType>()
{
	return FSIOJ_NamedType::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSIOJ_NamedType(FSIOJ_NamedType::StaticStruct, TEXT("/Script/SIOJEditorPlugin"), TEXT("SIOJ_NamedType"), false, nullptr, nullptr);
static struct FScriptStruct_SIOJEditorPlugin_StaticRegisterNativesFSIOJ_NamedType
{
	FScriptStruct_SIOJEditorPlugin_StaticRegisterNativesFSIOJ_NamedType()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SIOJ_NamedType")),new UScriptStruct::TCppStructOps<FSIOJ_NamedType>);
	}
} ScriptStruct_SIOJEditorPlugin_StaticRegisterNativesFSIOJ_NamedType;
	struct Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsArray_MetaData[];
#endif
		static void NewProp_bIsArray_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsArray;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSIOJ_NamedType>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "NamedType" },
		{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSIOJ_NamedType, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type_MetaData[] = {
		{ "Category", "NamedType" },
		{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSIOJ_NamedType, Type), Z_Construct_UEnum_SIOJEditorPlugin_ESIOJ_JsonType, METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray_MetaData[] = {
		{ "Category", "NamedType" },
		{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray_SetBit(void* Obj)
	{
		((FSIOJ_NamedType*)Obj)->bIsArray = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray = { "bIsArray", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FSIOJ_NamedType), &Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::NewProp_bIsArray,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJEditorPlugin,
		nullptr,
		&NewStructOps,
		"SIOJ_NamedType",
		sizeof(FSIOJ_NamedType),
		alignof(FSIOJ_NamedType),
		Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSIOJ_NamedType()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSIOJ_NamedType_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SIOJEditorPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SIOJ_NamedType"), sizeof(FSIOJ_NamedType), Get_Z_Construct_UScriptStruct_FSIOJ_NamedType_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSIOJ_NamedType_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSIOJ_NamedType_Hash() { return 2608459548U; }
	void USIOJ_BreakJson::StaticRegisterNativesUSIOJ_BreakJson()
	{
	}
	UClass* Z_Construct_UClass_USIOJ_BreakJson_NoRegister()
	{
		return USIOJ_BreakJson::StaticClass();
	}
	struct Z_Construct_UClass_USIOJ_BreakJson_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Outputs_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Outputs_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Outputs;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USIOJ_BreakJson_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UK2Node,
		(UObject* (*)())Z_Construct_UPackage__Script_SIOJEditorPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJ_BreakJson_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "SIOJ_BreakJson.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs_Inner = { "Outputs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FSIOJ_NamedType, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs_MetaData[] = {
		{ "Category", "PinOptions" },
		{ "ModuleRelativePath", "Public/SIOJ_BreakJson.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs = { "Outputs", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USIOJ_BreakJson, Outputs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USIOJ_BreakJson_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USIOJ_BreakJson_Statics::NewProp_Outputs,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USIOJ_BreakJson_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USIOJ_BreakJson>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USIOJ_BreakJson_Statics::ClassParams = {
		&USIOJ_BreakJson::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USIOJ_BreakJson_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USIOJ_BreakJson_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USIOJ_BreakJson_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USIOJ_BreakJson_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USIOJ_BreakJson()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USIOJ_BreakJson_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USIOJ_BreakJson, 2251736851);
	template<> SIOJEDITORPLUGIN_API UClass* StaticClass<USIOJ_BreakJson>()
	{
		return USIOJ_BreakJson::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USIOJ_BreakJson(Z_Construct_UClass_USIOJ_BreakJson, &USIOJ_BreakJson::StaticClass, TEXT("/Script/SIOJEditorPlugin"), TEXT("USIOJ_BreakJson"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USIOJ_BreakJson);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
