// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/Async/Future.h"
#include "CoreUtilityBPLibrary.generated.h"

/* Wrapper for EImageFormat::Type for BP*/
UENUM()
enum class EImageFormatBPType : uint8
{
	/** Invalid or unrecognized format. */
	Invalid = 254,

	/** Portable Network Graphics. */
	PNG = 0,

	/** Joint Photographic Experts Group. */
	JPEG,

	/** Single channel JPEG. */
	GrayscaleJPEG,

	/** Windows Bitmap. */
	BMP,

	/** Windows Icon resource. */
	ICO,

	/** OpenEXR (HDR) image file format. */
	EXR,

	/** Mac icon. */
	ICNS
};

/**
 * Useful generic blueprint functions, mostly conversion
 */
UCLASS()
class COREUTILITY_API UCoreUtilityBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Conversion Nodes

	//Convert any unicode bytes to string
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (Bytes)", BlueprintAutocast), Category = "CoreUtility|Conversion")
	static FString Conv_BytesToString(const TArray<uint8>& InBytes);

	//Convert string to UTF8 bytes
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bytes (String)", BlueprintAutocast), Category = "CoreUtility|Conversion")
	static TArray<uint8> Conv_StringToBytes(FString InString);

	//Convert bytes to UTexture2D using auto-detection - optimized, but can still have performance implication
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Texture2D (Bytes)", BlueprintAutocast), Category = "CoreUtility|Conversion")
	static UTexture2D* Conv_BytesToTexture(const TArray<uint8>& InBytes);

	//Fully Async texture conversion from bytes will auto-detect format, depends on TFuture, cannot be called in blueprint
	static TFuture<UTexture2D*> Conv_BytesToTexture_Async(const TArray<uint8>& InBytes);

	//Convert UTexture2D to bytes in given format - can have performance implication
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bytes (Texture2D)", BlueprintAutocast), Category = "CoreUtility|Conversion")
	static bool Conv_TextureToBytes(UTexture2D* Texture, TArray<uint8>& OutBuffer, EImageFormatBPType Format = EImageFormatBPType::PNG);

	//Current UTC time in string format
	UFUNCTION(BlueprintPure, Category = "CoreUtility|Conversion")
	static FString NowUTCString();

	//Hardware ID
	UFUNCTION(BlueprintPure, Category = "CoreUtility|Conversion")
	static FString GetLoginId();

};
