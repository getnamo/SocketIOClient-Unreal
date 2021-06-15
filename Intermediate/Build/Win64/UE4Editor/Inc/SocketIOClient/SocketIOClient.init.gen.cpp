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
void EmptyLinkFunctionForGeneratedCodeSocketIOClient_init() {}
	SOCKETIOCLIENT_API UFunction* Z_Construct_UDelegateFunction_SocketIOClient_SIOCEventSignature__DelegateSignature();
	SOCKETIOCLIENT_API UFunction* Z_Construct_UDelegateFunction_SocketIOClient_SIOCSocketEventSignature__DelegateSignature();
	SOCKETIOCLIENT_API UFunction* Z_Construct_UDelegateFunction_SocketIOClient_SIOCOpenEventSignature__DelegateSignature();
	SOCKETIOCLIENT_API UFunction* Z_Construct_UDelegateFunction_SocketIOClient_SIOCCloseEventSignature__DelegateSignature();
	SOCKETIOCLIENT_API UFunction* Z_Construct_UDelegateFunction_SocketIOClient_SIOCEventJsonSignature__DelegateSignature();
	SOCKETIOCLIENT_API UFunction* Z_Construct_UDelegateFunction_SocketIOClient_SIOConnectionProblemSignature__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SocketIOClient()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SocketIOClient_SIOCEventSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SocketIOClient_SIOCSocketEventSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SocketIOClient_SIOCOpenEventSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SocketIOClient_SIOCCloseEventSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SocketIOClient_SIOCEventJsonSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SocketIOClient_SIOConnectionProblemSignature__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/SocketIOClient",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x90267390,
				0x145F5AA8,
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
