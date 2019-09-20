// Copyright 2018-current Getnamo. All Rights Reserved


#include "CUFileComponent.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"

UCUFileComponent::UCUFileComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
}

FString UCUFileComponent::ProjectContentsDirectory()
{
	return FPaths::ProjectContentDir();
}

FString UCUFileComponent::ProjectDirectory()
{
	return FPaths::ProjectDir();
}

FString UCUFileComponent::ProjectSavedDirectory()
{
	return FPaths::ProjectSavedDir();
}

bool UCUFileComponent::SaveBytesToFile(const TArray<uint8>& Bytes, const FString& Directory, const FString& FileName)
{
	//bool AllowOverwriting = false;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.CreateDirectoryTree(*Directory))
	{
		// Get absolute file path
		FString AbsoluteFilePath = Directory + "/" + FileName;

		// Allow overwriting or file doesn't already exist
		return FFileHelper::SaveArrayToFile(Bytes, *AbsoluteFilePath);
	}

	return false;
}

bool UCUFileComponent::ReadBytesFromFile(const FString& Directory, const FString& FileName, TArray<uint8>& OutBytes)
{
	// Get absolute file path
	FString AbsoluteFilePath = Directory + "/" + FileName;

	// Allow overwriting or file doesn't already exist
	return FFileHelper::LoadFileToArray(OutBytes, *AbsoluteFilePath);
}
