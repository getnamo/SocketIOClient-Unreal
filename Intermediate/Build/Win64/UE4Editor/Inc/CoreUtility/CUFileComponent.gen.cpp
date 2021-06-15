// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoreUtility/Public/CUFileComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCUFileComponent() {}
// Cross Module References
	COREUTILITY_API UClass* Z_Construct_UClass_UCUFileComponent_NoRegister();
	COREUTILITY_API UClass* Z_Construct_UClass_UCUFileComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_CoreUtility();
// End Cross Module References
	DEFINE_FUNCTION(UCUFileComponent::execReadBytesFromFile)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Directory);
		P_GET_PROPERTY(FStrProperty,Z_Param_FileName);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_OutBytes);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->ReadBytesFromFile(Z_Param_Directory,Z_Param_FileName,Z_Param_Out_OutBytes);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCUFileComponent::execSaveBytesToFile)
	{
		P_GET_TARRAY_REF(uint8,Z_Param_Out_Bytes);
		P_GET_PROPERTY(FStrProperty,Z_Param_Directory);
		P_GET_PROPERTY(FStrProperty,Z_Param_FileName);
		P_GET_UBOOL(Z_Param_bLogSave);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->SaveBytesToFile(Z_Param_Out_Bytes,Z_Param_Directory,Z_Param_FileName,Z_Param_bLogSave);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCUFileComponent::execExternalSaveDirectory)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ExternalSaveDirectory();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCUFileComponent::execProjectSavedDirectory)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ProjectSavedDirectory();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCUFileComponent::execProjectDirectory)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ProjectDirectory();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCUFileComponent::execProjectContentsDirectory)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ProjectContentsDirectory();
		P_NATIVE_END;
	}
	void UCUFileComponent::StaticRegisterNativesUCUFileComponent()
	{
		UClass* Class = UCUFileComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ExternalSaveDirectory", &UCUFileComponent::execExternalSaveDirectory },
			{ "ProjectContentsDirectory", &UCUFileComponent::execProjectContentsDirectory },
			{ "ProjectDirectory", &UCUFileComponent::execProjectDirectory },
			{ "ProjectSavedDirectory", &UCUFileComponent::execProjectSavedDirectory },
			{ "ReadBytesFromFile", &UCUFileComponent::execReadBytesFromFile },
			{ "SaveBytesToFile", &UCUFileComponent::execSaveBytesToFile },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics
	{
		struct CUFileComponent_eventExternalSaveDirectory_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventExternalSaveDirectory_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::Function_MetaDataParams[] = {
		{ "Category", "FileUtility" },
		{ "Comment", "/** External storage in android context, otherwise uses project saved directory*/" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "External storage in android context, otherwise uses project saved directory" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCUFileComponent, nullptr, "ExternalSaveDirectory", nullptr, nullptr, sizeof(CUFileComponent_eventExternalSaveDirectory_Parms), Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics
	{
		struct CUFileComponent_eventProjectContentsDirectory_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventProjectContentsDirectory_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::Function_MetaDataParams[] = {
		{ "Category", "FileUtility" },
		{ "Comment", "/** Get the current project contents directory path*/" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "Get the current project contents directory path" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCUFileComponent, nullptr, "ProjectContentsDirectory", nullptr, nullptr, sizeof(CUFileComponent_eventProjectContentsDirectory_Parms), Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics
	{
		struct CUFileComponent_eventProjectDirectory_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventProjectDirectory_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::Function_MetaDataParams[] = {
		{ "Category", "FileUtility" },
		{ "Comment", "/** Get the current project directory path*/" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "Get the current project directory path" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCUFileComponent, nullptr, "ProjectDirectory", nullptr, nullptr, sizeof(CUFileComponent_eventProjectDirectory_Parms), Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCUFileComponent_ProjectDirectory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCUFileComponent_ProjectDirectory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics
	{
		struct CUFileComponent_eventProjectSavedDirectory_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventProjectSavedDirectory_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::Function_MetaDataParams[] = {
		{ "Category", "FileUtility" },
		{ "Comment", "/** Get the current project saved directory path*/" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "Get the current project saved directory path" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCUFileComponent, nullptr, "ProjectSavedDirectory", nullptr, nullptr, sizeof(CUFileComponent_eventProjectSavedDirectory_Parms), Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics
	{
		struct CUFileComponent_eventReadBytesFromFile_Parms
		{
			FString Directory;
			FString FileName;
			TArray<uint8> OutBytes;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Directory_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Directory;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FileName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FileName;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_OutBytes_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutBytes;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_Directory_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_Directory = { "Directory", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventReadBytesFromFile_Parms, Directory), METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_Directory_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_Directory_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_FileName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_FileName = { "FileName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventReadBytesFromFile_Parms, FileName), METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_FileName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_FileName_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_OutBytes_Inner = { "OutBytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_OutBytes = { "OutBytes", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventReadBytesFromFile_Parms, OutBytes), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CUFileComponent_eventReadBytesFromFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CUFileComponent_eventReadBytesFromFile_Parms), &Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_Directory,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_FileName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_OutBytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_OutBytes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "FileUtility" },
		{ "Comment", "/** Read array of bytes from file at specified directory */" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "Read array of bytes from file at specified directory" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCUFileComponent, nullptr, "ReadBytesFromFile", nullptr, nullptr, sizeof(CUFileComponent_eventReadBytesFromFile_Parms), Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics
	{
		struct CUFileComponent_eventSaveBytesToFile_Parms
		{
			TArray<uint8> Bytes;
			FString Directory;
			FString FileName;
			bool bLogSave;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Bytes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Bytes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Bytes;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Directory_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Directory;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FileName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FileName;
		static void NewProp_bLogSave_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bLogSave;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes_Inner = { "Bytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes = { "Bytes", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventSaveBytesToFile_Parms, Bytes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Directory_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Directory = { "Directory", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventSaveBytesToFile_Parms, Directory), METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Directory_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Directory_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_FileName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_FileName = { "FileName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CUFileComponent_eventSaveBytesToFile_Parms, FileName), METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_FileName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_FileName_MetaData)) };
	void Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_bLogSave_SetBit(void* Obj)
	{
		((CUFileComponent_eventSaveBytesToFile_Parms*)Obj)->bLogSave = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_bLogSave = { "bLogSave", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CUFileComponent_eventSaveBytesToFile_Parms), &Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_bLogSave_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CUFileComponent_eventSaveBytesToFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CUFileComponent_eventSaveBytesToFile_Parms), &Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Bytes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_Directory,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_FileName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_bLogSave,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "FileUtility" },
		{ "Comment", "/** Save array of bytes to file at specified directory */" },
		{ "CPP_Default_bLogSave", "false" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "Save array of bytes to file at specified directory" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCUFileComponent, nullptr, "SaveBytesToFile", nullptr, nullptr, sizeof(CUFileComponent_eventSaveBytesToFile_Parms), Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCUFileComponent_NoRegister()
	{
		return UCUFileComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCUFileComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCUFileComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CoreUtility,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCUFileComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCUFileComponent_ExternalSaveDirectory, "ExternalSaveDirectory" }, // 1698161886
		{ &Z_Construct_UFunction_UCUFileComponent_ProjectContentsDirectory, "ProjectContentsDirectory" }, // 1450481400
		{ &Z_Construct_UFunction_UCUFileComponent_ProjectDirectory, "ProjectDirectory" }, // 2409155223
		{ &Z_Construct_UFunction_UCUFileComponent_ProjectSavedDirectory, "ProjectSavedDirectory" }, // 1587923941
		{ &Z_Construct_UFunction_UCUFileComponent_ReadBytesFromFile, "ReadBytesFromFile" }, // 355259296
		{ &Z_Construct_UFunction_UCUFileComponent_SaveBytesToFile, "SaveBytesToFile" }, // 4130597180
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCUFileComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Utility" },
		{ "Comment", "/**\n* Convenience component to save/load data from files\n*/" },
		{ "IncludePath", "CUFileComponent.h" },
		{ "ModuleRelativePath", "Public/CUFileComponent.h" },
		{ "ToolTip", "Convenience component to save/load data from files" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCUFileComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCUFileComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCUFileComponent_Statics::ClassParams = {
		&UCUFileComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UCUFileComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCUFileComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCUFileComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCUFileComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCUFileComponent, 415065677);
	template<> COREUTILITY_API UClass* StaticClass<UCUFileComponent>()
	{
		return UCUFileComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCUFileComponent(Z_Construct_UClass_UCUFileComponent, &UCUFileComponent::StaticClass, TEXT("/Script/CoreUtility"), TEXT("UCUFileComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCUFileComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
