// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SocketIOClient/Public/SocketIONative.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSocketIONative() {}
// Cross Module References
	SOCKETIOCLIENT_API UEnum* Z_Construct_UEnum_SocketIOClient_ESIOThreadOverrideOption();
	UPackage* Z_Construct_UPackage__Script_SocketIOClient();
	SOCKETIOCLIENT_API UEnum* Z_Construct_UEnum_SocketIOClient_ESIOConnectionCloseReason();
// End Cross Module References
	static UEnum* ESIOThreadOverrideOption_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SocketIOClient_ESIOThreadOverrideOption, Z_Construct_UPackage__Script_SocketIOClient(), TEXT("ESIOThreadOverrideOption"));
		}
		return Singleton;
	}
	template<> SOCKETIOCLIENT_API UEnum* StaticEnum<ESIOThreadOverrideOption>()
	{
		return ESIOThreadOverrideOption_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESIOThreadOverrideOption(ESIOThreadOverrideOption_StaticEnum, TEXT("/Script/SocketIOClient"), TEXT("ESIOThreadOverrideOption"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SocketIOClient_ESIOThreadOverrideOption_Hash() { return 2796065303U; }
	UEnum* Z_Construct_UEnum_SocketIOClient_ESIOThreadOverrideOption()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SocketIOClient();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESIOThreadOverrideOption"), 0, Get_Z_Construct_UEnum_SocketIOClient_ESIOThreadOverrideOption_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "USE_DEFAULT", (int64)USE_DEFAULT },
				{ "USE_GAME_THREAD", (int64)USE_GAME_THREAD },
				{ "USE_NETWORK_THREAD", (int64)USE_NETWORK_THREAD },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/SocketIONative.h" },
				{ "USE_DEFAULT.Name", "USE_DEFAULT" },
				{ "USE_GAME_THREAD.Name", "USE_GAME_THREAD" },
				{ "USE_NETWORK_THREAD.Name", "USE_NETWORK_THREAD" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SocketIOClient,
				nullptr,
				"ESIOThreadOverrideOption",
				"ESIOThreadOverrideOption",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ESIOConnectionCloseReason_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SocketIOClient_ESIOConnectionCloseReason, Z_Construct_UPackage__Script_SocketIOClient(), TEXT("ESIOConnectionCloseReason"));
		}
		return Singleton;
	}
	template<> SOCKETIOCLIENT_API UEnum* StaticEnum<ESIOConnectionCloseReason>()
	{
		return ESIOConnectionCloseReason_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESIOConnectionCloseReason(ESIOConnectionCloseReason_StaticEnum, TEXT("/Script/SocketIOClient"), TEXT("ESIOConnectionCloseReason"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SocketIOClient_ESIOConnectionCloseReason_Hash() { return 3190136421U; }
	UEnum* Z_Construct_UEnum_SocketIOClient_ESIOConnectionCloseReason()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SocketIOClient();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESIOConnectionCloseReason"), 0, Get_Z_Construct_UEnum_SocketIOClient_ESIOConnectionCloseReason_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "CLOSE_REASON_NORMAL", (int64)CLOSE_REASON_NORMAL },
				{ "CLOSE_REASON_DROP", (int64)CLOSE_REASON_DROP },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "CLOSE_REASON_DROP.Name", "CLOSE_REASON_DROP" },
				{ "CLOSE_REASON_NORMAL.Name", "CLOSE_REASON_NORMAL" },
				{ "ModuleRelativePath", "Public/SocketIONative.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SocketIOClient,
				nullptr,
				"ESIOConnectionCloseReason",
				"ESIOConnectionCloseReason",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
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
