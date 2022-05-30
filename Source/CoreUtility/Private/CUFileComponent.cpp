// Copyright 2018-current Getnamo. All Rights Reserved


#include "CUFileComponent.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#if PLATFORM_ANDROID
#include "Android/AndroidPlatformMisc.h"
#endif

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

FString UCUFileComponent::ExternalSaveDirectory()
{
#if PLATFORM_ANDROID
	return  FString(FAndroidMisc::GamePersistentDownloadDir());
#else
	return FPaths::ProjectSavedDir();
#endif
}

void UCUFileComponent::SplitFullPath(const FString& InFullPath, FString& OutDirectory, FString& OutFileName)
{
	bool bDidSplit = InFullPath.Split(TEXT("/"), &OutDirectory, &OutFileName, ESearchCase::CaseSensitive, ESearchDir::FromEnd);

	if (!bDidSplit) 
	{
		//search by backslash
		InFullPath.Split(TEXT("\\\\"), &OutDirectory, &OutFileName, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
	}
}

void UCUFileComponent::ProjectRelativePath(const FString& InFullPath, FString& OutProjectRelativePath)
{
	const FString PathToProject = ProjectDirectory();

	FString Before, After;

	InFullPath.Split(PathToProject, &Before, &After);

	OutProjectRelativePath = After;
}

bool UCUFileComponent::SaveBytesToFile(const TArray<uint8>& Bytes, const FString& Directory, const FString& FileName, bool bLogSave)
{
	//bool AllowOverwriting = false;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.CreateDirectoryTree(*Directory))
	{
		FString AbsoluteFilePath;

		// Get absolute file path
		if (Directory.EndsWith(TEXT("/")))
		{
			AbsoluteFilePath = FPaths::ConvertRelativePathToFull(Directory + FileName);
		}
		else
		{
			AbsoluteFilePath = FPaths::ConvertRelativePathToFull(Directory + "/" + FileName);
		}

		// Allow overwriting or file doesn't already exist
		bool bSaveSuccesful = FFileHelper::SaveArrayToFile(Bytes, *AbsoluteFilePath);

		if (bLogSave)
		{
			if (bSaveSuccesful)
			{
				UE_LOG(LogTemp, Log, TEXT("Saved: %s with %d bytes"), *AbsoluteFilePath, Bytes.Num());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Failed to save: %s"), *AbsoluteFilePath);
			}
		}

		return bSaveSuccesful;
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
