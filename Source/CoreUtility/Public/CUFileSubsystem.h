#pragma once

#include "Subsystems/EngineSubsystem.h"
#include "CUFileSubsystem.generated.h"

UCLASS(ClassGroup = "WRCoreAI")
class COREUTILITY_API UCUFileSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	/** Get the current project contents directory path*/
	UFUNCTION(BlueprintPure, Category = FileUtility)
	FString ProjectContentsDirectory();

	/** Get the current project directory path*/
	UFUNCTION(BlueprintPure, Category = FileUtility)
	FString ProjectDirectory();

	/** Get the current project saved directory path*/
	UFUNCTION(BlueprintPure, Category = FileUtility)
	FString ProjectSavedDirectory();

	/** External storage in android context, otherwise uses project saved directory*/
	UFUNCTION(BlueprintPure, Category = FileUtility)
	FString ExternalSaveDirectory();

	UFUNCTION(BlueprintPure, Category = FileUtility)
	void SplitFullPath(const FString& InFullPath, FString& OutDirectory, FString& OutFileName);

	UFUNCTION(BlueprintPure, Category = FileUtility)
	void ProjectRelativePath(const FString& InFullPath, FString& OutProjectRelativePath);

	/** Save array of bytes to file at specified directory */
	UFUNCTION(BlueprintCallable, Category = FileUtility)
	bool SaveBytesToFile(const TArray<uint8>& Bytes, const FString& Directory, const FString& FileName, bool bLogSave = false);

	/** Read array of bytes from file at specified directory */
	UFUNCTION(BlueprintCallable, Category = FileUtility)
	bool ReadBytesFromFile(const FString& Directory, const FString& FileName, TArray<uint8>& OutBytes);
	
	//Lifetime
	virtual	void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};