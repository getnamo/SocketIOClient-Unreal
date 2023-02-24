#include "CUFileSubsystem.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#if PLATFORM_ANDROID
#include "Android/AndroidPlatformMisc.h"
#endif

void UCUFileSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UCUFileSubsystem::Deinitialize()
{

}

FString UCUFileSubsystem::ProjectContentsDirectory()
{
	return FPaths::ProjectContentDir();
}

FString UCUFileSubsystem::ProjectDirectory()
{
	return FPaths::ProjectDir();
}

FString UCUFileSubsystem::ProjectSavedDirectory()
{
	return FPaths::ProjectSavedDir();
}

FString UCUFileSubsystem::ExternalSaveDirectory()
{
#if PLATFORM_ANDROID
	return  FString(FAndroidMisc::GamePersistentDownloadDir());
#else
	return FPaths::ProjectSavedDir();
#endif
}

void UCUFileSubsystem::SplitFullPath(const FString& InFullPath, FString& OutDirectory, FString& OutFileName)
{
	bool bDidSplit = InFullPath.Split(TEXT("/"), &OutDirectory, &OutFileName, ESearchCase::CaseSensitive, ESearchDir::FromEnd);

	if (!bDidSplit)
	{
		//search by backslash
		InFullPath.Split(TEXT("\\\\"), &OutDirectory, &OutFileName, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
	}
}

void UCUFileSubsystem::ProjectRelativePath(const FString& InFullPath, FString& OutProjectRelativePath)
{
	const FString PathToProject = ProjectDirectory();

	FString Before, After;

	InFullPath.Split(PathToProject, &Before, &After);

	OutProjectRelativePath = After;
}

bool UCUFileSubsystem::SaveBytesToFile(const TArray<uint8>& Bytes, const FString& Directory, const FString& FileName, bool bLogSave)
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

bool UCUFileSubsystem::SaveBytesToPath(const TArray<uint8>& Bytes, const FString& Path, bool bLogSave /*= false*/)
{
	//we use the split file overload due to some potential directory automation checks
	FString Directory, FileName;
	SplitFullPath(Path, Directory, FileName);
	return SaveBytesToFile(Bytes, Directory, FileName, bLogSave);
}

bool UCUFileSubsystem::ReadBytesFromFile(const FString& Directory, const FString& FileName, TArray<uint8>& OutBytes)
{
	// Get absolute file path
	const FString AbsoluteFilePath = Directory + "/" + FileName;

	return ReadBytesFromPath(AbsoluteFilePath, OutBytes);
}

bool UCUFileSubsystem::ReadBytesFromPath(const FString& Path, TArray<uint8>& OutBytes)
{
	return FFileHelper::LoadFileToArray(OutBytes, *Path);
}

bool UCUFileSubsystem::DeleteFileAtPath(const FString& Path)
{
	if (!Path.IsEmpty())
	{
		if (FPaths::ValidatePath(Path) && FPaths::FileExists(Path))
		{
			IFileManager& FileManager = IFileManager::Get();
			FileManager.Delete(*Path);
			return true;
		}
	}
	return false;
}

