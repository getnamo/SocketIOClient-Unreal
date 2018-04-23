#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreUtilityBPLibrary.generated.h"

/**
 * Useful generic blueprint functions
 */
UCLASS()
class UCoreUtilityBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Conversion Nodes

	//Converts any unicode bytes to string
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (Bytes)", BlueprintAutocast), Category = "CoreUtility|Conversion")
	static FString Conv_BytesToString(const TArray<uint8>& InArray);

	//Converts string to UTF8 bytes
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bytes (String)", BlueprintAutocast), Category = "CoreUtility|Conversion")
	static TArray<uint8> Conv_StringToBytes(FString InString);

	//Current UTC time in string format
	UFUNCTION(BlueprintPure, Category = "CoreUtility|Conversion")
	static FString NowUTCString();

	//Hardware ID
	UFUNCTION(BlueprintPure, Category = "CoreUtility|Conversion")
	static FString GetLoginId();

};
