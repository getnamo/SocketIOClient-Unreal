#include "CoreUtilityPrivatePCH.h"
#include "CoreUtilityBPLibrary.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

FString UCoreUtilityBPLibrary::Conv_BytesToString(const TArray<uint8>& InArray)
{
	FString ResultString;
	FFileHelper::BufferToString(ResultString, InArray.GetData(), InArray.Num());
	return ResultString;
}

TArray<uint8> UCoreUtilityBPLibrary::Conv_StringToBytes(FString InString)
{
	TArray<uint8> ResultBytes;
	ResultBytes.Append((uint8*)TCHAR_TO_UTF8(*InString), InString.Len());
	return ResultBytes;
}
