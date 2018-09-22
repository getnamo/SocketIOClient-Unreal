// Copyright 2018-current Getnamo. All Rights Reserved


#include "CoreUtilityBPLibrary.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "EngineMinimal.h"
#include "LambdaRunnable.h"
#include "Runtime/RHI/Public/RHI.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "CoreMinimal.h"

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

UTexture2D* UCoreUtilityBPLibrary::Conv_BytesToTexture(const TArray<uint8>& InBytes)
{
	//Convert the UTexture2D back to an image
	UTexture2D* Texture = nullptr;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	EImageFormat DetectedFormat = ImageWrapperModule.DetectImageFormat(InBytes.GetData(), InBytes.Num());

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(DetectedFormat);

	//Set the compressed bytes - we need this information on game thread to be able to determine texture size, otherwise we'll need a complete async callback
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(InBytes.GetData(), InBytes.Num()))
	{
		//Create image given sizes
		Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
		Texture->UpdateResource();

		//Uncompress on a background thread pool
		FLambdaRunnable::RunLambdaOnBackGroundThreadPool([ImageWrapper, Texture] {
			const TArray<uint8>* UncompressedBGRA = nullptr;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{

				//Update on render thread, wrap up all required data
				struct FUpdateTextureData
				{
					UTexture2D* Texture2D;
					FUpdateTextureRegion2D Region;
					uint32 Pitch;
					const TArray<uint8>* BufferArray;
					TSharedPtr<IImageWrapper> Wrapper;	//to keep the uncompressed data alive
				};

				FUpdateTextureData* UpdateData = new FUpdateTextureData;
				UpdateData->Texture2D = Texture;
				UpdateData->Region = FUpdateTextureRegion2D(0, 0, 0, 0, Texture->GetSizeX(), Texture->GetSizeY());
				UpdateData->BufferArray = UncompressedBGRA;
				UpdateData->Pitch = Texture->GetSizeX() * 4;
				UpdateData->Wrapper = ImageWrapper;

				//enqueue texture copy
				ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
					FUpdateTextureData,
					FUpdateTextureData*, UpdateData, UpdateData,
				{
					RHIUpdateTexture2D(
						((FTexture2DResource*)UpdateData->Texture2D->Resource)->GetTexture2DRHI(),
						0,
						UpdateData->Region,
						UpdateData->Pitch,
						UpdateData->BufferArray->GetData()
					);
					delete UpdateData; //now that we've updated the texture data, we can finally release any data we're holding on to
				});//End Enqueue
			}
		});
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid image format cannot decode %d"), (int32)DetectedFormat);
	}

	return Texture;
}

TFuture<UTexture2D*> UCoreUtilityBPLibrary::Conv_BytesToTexture_Async(const TArray<uint8>& InBytes)
{
	//Running this on a background thread
	return Async<UTexture2D*>(EAsyncExecution::Thread,[InBytes]
	{
		//Create wrapper pointer we can share easily across threads
		struct FDataHolder
		{
			UTexture2D* Texture = nullptr;
		};
		TSharedPtr<FDataHolder> Holder = MakeShareable(new FDataHolder);

		FThreadSafeBool bLoadModuleComplete = false;
		IImageWrapperModule* ImageWrapperModule;

		AsyncTask(ENamedThreads::GameThread, [&bLoadModuleComplete, Holder, &ImageWrapperModule]
		{
			ImageWrapperModule = &FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
			bLoadModuleComplete = true; 
		});
		while (!bLoadModuleComplete)
		{
			FPlatformProcess::Sleep(0.001f);
		}

		EImageFormat DetectedFormat = ImageWrapperModule->DetectImageFormat(InBytes.GetData(), InBytes.Num());

		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule->CreateImageWrapper(DetectedFormat);

		if (!(ImageWrapper.IsValid() && ImageWrapper->SetCompressed(InBytes.GetData(), InBytes.Num())))
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid image format cannot decode %d"), (int32)DetectedFormat);
			return (UTexture2D*)nullptr;
		}

		//Create image given sizes

		//Creation of UTexture needs to happen on game thread
		FThreadSafeBool bAllocationComplete = false;
		FIntPoint Size;
		Size.X = ImageWrapper->GetWidth();
		Size.Y = ImageWrapper->GetHeight();
		AsyncTask(ENamedThreads::GameThread, [&bAllocationComplete, Holder, Size]
		{
			Holder->Texture = UTexture2D::CreateTransient(Size.X, Size.Y, PF_B8G8R8A8);
			Holder->Texture->UpdateResource();
			bAllocationComplete = true;
		});

		while (!bAllocationComplete)
		{
			//sleep 10ms intervals
			FPlatformProcess::Sleep(0.001f);
		}

		//Uncompress on a background thread pool
		const TArray<uint8>* UncompressedBGRA = nullptr;
		if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			return (UTexture2D*)nullptr;
		}

		//Update actual bytes on render thread, wrap up all required data
		struct FUpdateTextureData
		{
			UTexture2D* Texture2D;
			FUpdateTextureRegion2D Region;
			uint32 Pitch;
			const TArray<uint8>* BufferArray;
			TSharedPtr<IImageWrapper> Wrapper;	//to keep the uncompressed data alive
		};

		FUpdateTextureData* UpdateData = new FUpdateTextureData;
		UpdateData->Texture2D = Holder->Texture;
		UpdateData->Region = FUpdateTextureRegion2D(0, 0, 0, 0, Size.X, Size.Y);
		UpdateData->BufferArray = UncompressedBGRA;
		UpdateData->Pitch = Size.X * 4;
		UpdateData->Wrapper = ImageWrapper;

		//This command sends it to the render thread
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		FUpdateTextureData,
		FUpdateTextureData*, UpdateData, UpdateData,
		{
			RHIUpdateTexture2D(
				((FTexture2DResource*)UpdateData->Texture2D->Resource)->GetTexture2DRHI(),
				0,
				UpdateData->Region,
				UpdateData->Pitch,
				UpdateData->BufferArray->GetData()
			);
			delete UpdateData; //now that we've updated the texture data, we can finally release any data we're holding on to
		});//End Enqueue

		return Holder->Texture;
	});//End async
}

bool UCoreUtilityBPLibrary::Conv_TextureToBytes(UTexture2D* Texture, TArray<uint8>& OutBuffer, EImageFormatBPType Format /*= EImageFormatBPType::JPEG*/)
{
	if (!Texture || !Texture->IsValidLowLevel())
	{
		return false;
	}

	//Get our wrapper module
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper((EImageFormat)Format);

	int32 Width = Texture->PlatformData->Mips[0].SizeX;
	int32 Height = Texture->PlatformData->Mips[0].SizeY;
	int32 DataLength = Width * Height * 4;

	void* TextureDataPointer = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY);

	ImageWrapper->SetRaw(TextureDataPointer, DataLength, Width, Height, ERGBFormat::BGRA, 8);

	//This part can take a while, has performance implications
	OutBuffer = ImageWrapper->GetCompressed();

	Texture->PlatformData->Mips[0].BulkData.Unlock();

	return true;
}

FString UCoreUtilityBPLibrary::NowUTCString()
{
	return FDateTime::UtcNow().ToString();
}


FString UCoreUtilityBPLibrary::GetLoginId()
{
	return FPlatformMisc::GetLoginId();
}
