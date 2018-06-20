// Copyright 2018-current Getnamo. All Rights Reserved


#include "FileUtilityComponent.h"
#include "CoreUtilityPrivatePCH.h"


UFileUtilityComponent::UFileUtilityComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
}

FString UFileUtilityComponent::ProjectContentsDirectory()
{
	return FPaths::ProjectContentDir();
}

FString UFileUtilityComponent::ProjectDirectory()
{
	return FPaths::ProjectDir();
}

FString UFileUtilityComponent::ProjectSavedDirectory()
{
	return FPaths::ProjectSavedDir();
}

bool UFileUtilityComponent::SaveBytesToFile(const TArray<uint8>& Bytes, const FString& Directory, const FString& FileName)
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

bool UFileUtilityComponent::ReadBytesFromFile(const FString& Directory, const FString& FileName, TArray<uint8>& OutBytes)
{
	// Get absolute file path
	FString AbsoluteFilePath = Directory + "/" + FileName;

	// Allow overwriting or file doesn't already exist
	return FFileHelper::LoadFileToArray(OutBytes, *AbsoluteFilePath);
}
