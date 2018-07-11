// Copyright 2018-current Getnamo. All Rights Reserved


#include "CoreUtilityBPLibrary.h"
#include "CoreUtilityPrivatePCH.h"
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

FString UCoreUtilityBPLibrary::NowUTCString()
{
	return FDateTime::UtcNow().ToString();
}


FString UCoreUtilityBPLibrary::GetLoginId()
{
	return FPlatformMisc::GetLoginId();
}
