// Copyright 2018-current Getnamo. All Rights Reserved


#include "CUBlueprintLibrary.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Core/Public/Modules/ModuleManager.h"
#include "Core/Public/Async/Async.h"
#include "Engine/Classes/Engine/Texture2D.h"
#include "Core/Public/HAL/ThreadSafeBool.h"
#include "RHI/Public/RHI.h"
#include "Core/Public/Misc/FileHelper.h"
#include "Engine/Public/OpusAudioInfo.h"
#include "Launch/Resources/Version.h"
#include "Developer/TargetPlatform/Public/Interfaces/IAudioFormat.h"
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "CULambdaRunnable.h"
#include "CUOpusCoder.h"
#include "CUMeasureTimer.h"
#include "Hash/CityHash.h"

#pragma warning( push )
#pragma warning( disable : 5046)

//Render thread wrapper struct
struct FUpdateTextureData
{
	UTexture2D* Texture2D;
	FUpdateTextureRegion2D Region;
	uint32 Pitch;
	TArray64<uint8> BufferArray;
	TSharedPtr<IImageWrapper> Wrapper;	//to keep the uncompressed data alive
};

FString UCUBlueprintLibrary::Conv_BytesToString(const TArray<uint8>& InArray)
{
	FString ResultString;
	FFileHelper::BufferToString(ResultString, InArray.GetData(), InArray.Num());
	return ResultString;
}

TArray<uint8> UCUBlueprintLibrary::Conv_StringToBytes(FString InString)
{
	TArray<uint8> ResultBytes;
	ResultBytes.Append((uint8*)TCHAR_TO_UTF8(*InString), InString.Len());
	return ResultBytes;
}

UTexture2D* UCUBlueprintLibrary::Conv_BytesToTexture(const TArray<uint8>& InBytes)
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
		FCULambdaRunnable::RunLambdaOnBackGroundThreadPool([ImageWrapper, Texture] {
			TArray64<uint8> UncompressedBGRA;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{

				FUpdateTextureData* UpdateData = new FUpdateTextureData;
				UpdateData->Texture2D = Texture;
				UpdateData->Region = FUpdateTextureRegion2D(0, 0, 0, 0, Texture->GetSizeX(), Texture->GetSizeY());
				UpdateData->BufferArray = UncompressedBGRA;
				UpdateData->Pitch = Texture->GetSizeX() * 4;
				UpdateData->Wrapper = ImageWrapper;

				//enqueue texture copy
				ENQUEUE_RENDER_COMMAND(BytesToTextureCommand)(
					[UpdateData](FRHICommandList& CommandList)
				{
					RHIUpdateTexture2D(
						((FTextureResource*)UpdateData->Texture2D->GetResource())->TextureRHI->GetTexture2D(),
						0,
						UpdateData->Region,
						UpdateData->Pitch,
						UpdateData->BufferArray.GetData()
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

//one static coder, created based on need
TSharedPtr<FCUOpusCoder> OpusCoder;

TArray<uint8> UCUBlueprintLibrary::Conv_OpusBytesToWav(const TArray<uint8>& InBytes)
{
	//FCUScopeTimer Timer(TEXT("Conv_OpusBytesToWav"));

	TArray<uint8> WavBytes;
	//Early exit condition
	if (InBytes.Num() == 0) 
	{
		return WavBytes;
	}
	if (!OpusCoder)
	{
		OpusCoder = MakeShareable(new FCUOpusCoder());
	}

	TArray<uint8> PCMBytes;
	FCUOpusMinimalStream OpusStream;
	OpusCoder->DeserializeMinimal(InBytes, OpusStream);
	if (OpusCoder->DecodeStream(OpusStream, PCMBytes))
	{
		SerializeWaveFile(WavBytes, PCMBytes.GetData(), PCMBytes.Num(), OpusCoder->Channels, OpusCoder->SampleRate);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OpusMinimal to Wave Failed. DecodeStream returned false"));
	}

	return WavBytes;
}

TArray<uint8> UCUBlueprintLibrary::Conv_WavBytesToOpus(const TArray<uint8>& InBytes)
{
	//FCUScopeTimer Timer(TEXT("Conv_WavBytesToOpus"));

	TArray<uint8> OpusBytes;

	FWaveModInfo WaveInfo;

	if (!WaveInfo.ReadWaveInfo(InBytes.GetData(), InBytes.Num()))
	{
		return OpusBytes;
	}

	if (!OpusCoder)
	{
		OpusCoder = MakeShareable(new FCUOpusCoder());
	}

	TArray<uint8> PCMBytes = TArray<uint8>(WaveInfo.SampleDataStart, WaveInfo.SampleDataSize);

	FCUOpusMinimalStream OpusStream;

	OpusCoder->EncodeStream(PCMBytes, OpusStream);

	TArray<uint8> SerializedBytes;
	OpusCoder->SerializeMinimal(OpusStream, SerializedBytes);

	return SerializedBytes;
}

USoundWave* UCUBlueprintLibrary::Conv_WavBytesToSoundWave(const TArray<uint8>& InBytes)
{
	USoundWave* SoundWave;

	//Allocate based on thread
	if (IsInGameThread())
	{
		SoundWave = NewObject<USoundWaveProcedural>(USoundWaveProcedural::StaticClass());
		SetSoundWaveFromWavBytes((USoundWaveProcedural*)SoundWave, InBytes);
	}
	else
	{
		//We will go to another thread, copy our bytes
		TArray<uint8> CopiedBytes = InBytes;
		FThreadSafeBool bAllocationComplete = false;
		AsyncTask(ENamedThreads::GameThread, [&bAllocationComplete, &SoundWave]
		{
			SoundWave = NewObject<USoundWaveProcedural>(USoundWaveProcedural::StaticClass());
			bAllocationComplete = true;
		});

		//block while not complete
		while (!bAllocationComplete)
		{
			//100micros sleep, this should be very quick
			FPlatformProcess::Sleep(0.0001f);
		};

		SetSoundWaveFromWavBytes((USoundWaveProcedural*)SoundWave, CopiedBytes);
	}

	return SoundWave;
}

TArray<uint8> UCUBlueprintLibrary::Conv_SoundWaveToWavBytes(USoundWave* SoundWave)
{
	TArray<uint8> PCMBytes;
	TArray<uint8> WavBytes;

	//memcpy raw data from soundwave, hmm this won't work for procedurals...
	const void* LockedData = SoundWave->RawData.LockReadOnly();
	PCMBytes.SetNumUninitialized(SoundWave->RawData.GetBulkDataSize());
	FMemory::Memcpy(PCMBytes.GetData(), LockedData, PCMBytes.Num());
	SoundWave->RawData.Unlock();

	//add wav header
	SerializeWaveFile(WavBytes, PCMBytes.GetData(), PCMBytes.Num(), SoundWave->NumChannels, SoundWave->GetSampleRateForCurrentPlatform());

	return WavBytes;
}

void UCUBlueprintLibrary::Conv_CompactBytesToTransforms(const TArray<uint8>& InCompactBytes, TArray<FTransform>& OutTransforms)
{	
	TArray<float> FloatView;
	FloatView.SetNumUninitialized(InCompactBytes.Num() / 4);
	FPlatformMemory::Memcpy(FloatView.GetData(), InCompactBytes.GetData(), InCompactBytes.Num());

	//is our float array exactly divisible by 9?
	if (FloatView.Num() % 9 != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Conv_CompactBytesToTransforms::float array is not divisible by 9"));
		return;
	}

	int32 TransformNum = FloatView.Num() / 9;
	OutTransforms.SetNumUninitialized(TransformNum);

	for (int i = 0; i < FloatView.Num() - 8; i += 9)
	{
		OutTransforms[i/9] = FTransform(FRotator(FloatView[i], FloatView[i+1], FloatView[i+2]), FVector(FloatView[i+3], FloatView[i + 4], FloatView[i + 5]), FVector(FloatView[i+6], FloatView[i+7], FloatView[i+8]));
	}
}

void UCUBlueprintLibrary::Conv_CompactPositionBytesToTransforms(const TArray<uint8>& InCompactBytes, TArray<FTransform>& OutTransforms)
{
	TArray<float> FloatView;
	FloatView.SetNumUninitialized(InCompactBytes.Num() / 4);
	FPlatformMemory::Memcpy(FloatView.GetData(), InCompactBytes.GetData(), InCompactBytes.Num());

	//is our float array exactly divisible by 3?
	if (FloatView.Num() % 3 != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Conv_CompactPositionBytesToTransforms::float array is not divisible by 3"));
		return;
	}

	int32 TransformNum = FloatView.Num() / 3;
	OutTransforms.SetNumUninitialized(TransformNum);

	for (int i = 0; i < FloatView.Num() - 2; i += 3)
	{
		OutTransforms[i / 3] = FTransform(FVector(FloatView[i], FloatView[i + 1], FloatView[i + 2]));
	}
}

void UCUBlueprintLibrary::SetSoundWaveFromWavBytes(USoundWaveProcedural* InSoundWave, const TArray<uint8>& InBytes)
{
	FWaveModInfo WaveInfo;

	FString ErrorReason;
	if (WaveInfo.ReadWaveInfo(InBytes.GetData(), InBytes.Num(), &ErrorReason))
	{
		//copy header info
		int32 DurationDiv = *WaveInfo.pChannels * *WaveInfo.pBitsPerSample * *WaveInfo.pSamplesPerSec;
		if (DurationDiv)
		{
			InSoundWave->Duration = *WaveInfo.pWaveDataSize * 8.0f / DurationDiv;
		}
		else
		{
			InSoundWave->Duration = 0.0f;
		}

		InSoundWave->SetSampleRate(*WaveInfo.pSamplesPerSec);
		InSoundWave->NumChannels = *WaveInfo.pChannels;
		//SoundWaveProc->RawPCMDataSize = WaveInfo.SampleDataSize;
		InSoundWave->bLooping = false;
		InSoundWave->SoundGroup = ESoundGroup::SOUNDGROUP_Default;

		//Queue actual audio data
		InSoundWave->QueueAudio(WaveInfo.SampleDataStart, WaveInfo.SampleDataSize);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SetSoundWaveFromWavBytes::WaveRead error: %s"), *ErrorReason);
	}
}

TFuture<UTexture2D*> UCUBlueprintLibrary::Conv_BytesToTexture_Async(const TArray<uint8>& InBytes)
{
	//Running this on a background thread
	return Async(EAsyncExecution::Thread, [InBytes]
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
		TArray64<uint8> UncompressedBGRA;
		if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			return (UTexture2D*)nullptr;
		}

		FUpdateTextureData* UpdateData = new FUpdateTextureData;
		UpdateData->Texture2D = Holder->Texture;
		UpdateData->Region = FUpdateTextureRegion2D(0, 0, 0, 0, Size.X, Size.Y);
		UpdateData->BufferArray = UncompressedBGRA;
		UpdateData->Pitch = Size.X * 4;
		UpdateData->Wrapper = ImageWrapper;

		//This command sends it to the render thread
		ENQUEUE_RENDER_COMMAND(BytesToTextureAsyncCommand)(
			[UpdateData](FRHICommandList& CommandList)
		{
			RHIUpdateTexture2D(
				((FTextureResource*)UpdateData->Texture2D->GetResource())->TextureRHI->GetTexture2D(),
				0,
				UpdateData->Region,
				UpdateData->Pitch,
				UpdateData->BufferArray.GetData()
			);
			delete UpdateData; //now that we've updated the texture data, we can finally release any data we're holding on to
		});//End Enqueue

		return Holder->Texture;
	});//End async
}

bool UCUBlueprintLibrary::Conv_TextureToBytes(UTexture2D* Texture, TArray<uint8>& OutBuffer, EImageFormatBPType Format /*= EImageFormatBPType::JPEG*/)
{
	if (!Texture || !Texture->IsValidLowLevel())
	{
		return false;
	}

	//Get our wrapper module
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper((EImageFormat)Format);

	int32 Width = Texture->GetPlatformData()->Mips[0].SizeX;
	int32 Height = Texture->GetPlatformData()->Mips[0].SizeY;
	int32 DataLength = Width * Height * 4;

	void* TextureDataPointer = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_ONLY);

	ImageWrapper->SetRaw(TextureDataPointer, DataLength, Width, Height, ERGBFormat::BGRA, 8);

	//This part can take a while, has performance implications
	OutBuffer = ImageWrapper->GetCompressed();

	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

	return true;
}

FString UCUBlueprintLibrary::NowUTCString()
{
	return FDateTime::UtcNow().ToString();
}

FString UCUBlueprintLibrary::GetLoginId()
{
	return FPlatformMisc::GetLoginId();
}

int32 UCUBlueprintLibrary::ToHashCode(const FString& String)
{
	return (int32)CityHash32(TCHAR_TO_ANSI(*String), String.Len());
}

void UCUBlueprintLibrary::MeasureTimerStart(const FString& Category /*= TEXT("TimeTaken")*/)
{
	FCUMeasureTimer::Tick(Category);
}

float UCUBlueprintLibrary::MeasureTimerStop(const FString& Category /*= TEXT("TimeTaken")*/, bool bShouldLogResult /*= true*/)
{
	return (float)FCUMeasureTimer::Tock(Category, bShouldLogResult);
}

void UCUBlueprintLibrary::CallFunctionOnThread(const FString& FunctionName, ESIOCallbackType ThreadType, UObject* WorldContextObject /*= nullptr*/)
{
	UObject* Target = WorldContextObject;

	if (!Target->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("CallFunctionOnThread: Target not found for '%s'"), *FunctionName);
		return;
	}

	UFunction* Function = Target->FindFunction(FName(*FunctionName));
	if (nullptr == Function)
	{
		UE_LOG(LogTemp, Warning, TEXT("CallFunctionOnThread: Function not found '%s'"), *FunctionName);
		return;
	}

	switch (ThreadType)
	{
	case CALLBACK_GAME_THREAD:
		if (IsInGameThread())
		{
			Target->ProcessEvent(Function, nullptr);
		}
		else
		{
			FCULambdaRunnable::RunShortLambdaOnGameThread([Function, Target]
			{
				if (Target->IsValidLowLevel())
				{
					Target->ProcessEvent(Function, nullptr);
				}
			});
		}
		break;
	case CALLBACK_BACKGROUND_THREADPOOL:
		FCULambdaRunnable::RunLambdaOnBackGroundThreadPool([Function, Target]
		{
			if (Target->IsValidLowLevel())
			{
				Target->ProcessEvent(Function, nullptr);
			}
		});
		break;
	case CALLBACK_BACKGROUND_TASKGRAPH:
		FCULambdaRunnable::RunShortLambdaOnBackGroundTask([Function, Target]
		{
			if (Target->IsValidLowLevel())
			{
				Target->ProcessEvent(Function, nullptr);
			}
		});
		break;
	default:
		break;
	}
}

void UCUBlueprintLibrary::CallFunctionOnThreadGraphReturn(const FString& FunctionName, ESIOCallbackType ThreadType, struct FLatentActionInfo LatentInfo, UObject* WorldContextObject /*= nullptr*/)
{
	UObject* Target = WorldContextObject;
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, Target);

	if (!Target->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("CallFunctionOnThread: Target not found for '%s'"), *FunctionName);
		LatentAction->Call();
		return;
	}

	UFunction* Function = Target->FindFunction(FName(*FunctionName));
	if (nullptr == Function)
	{
		UE_LOG(LogTemp, Warning, TEXT("CallFunctionOnThread: Function not found '%s'"), *FunctionName);
		LatentAction->Call();
		return;
	}

	switch (ThreadType)
	{
	case CALLBACK_GAME_THREAD:
		if (IsInGameThread())
		{
			Target->ProcessEvent(Function, nullptr);
			LatentAction->Call();
		}
		else
		{
			FCULambdaRunnable::RunShortLambdaOnGameThread([Function, Target, LatentAction]
			{
				if (Target->IsValidLowLevel())
				{
					Target->ProcessEvent(Function, nullptr);
					LatentAction->Call();
				}
			});
		}
		break;
	case CALLBACK_BACKGROUND_THREADPOOL:
		FCULambdaRunnable::RunLambdaOnBackGroundThreadPool([Function, Target, LatentAction]
		{
			if (Target->IsValidLowLevel())
			{
				Target->ProcessEvent(Function, nullptr);
				LatentAction->Call();
			}
		});
		break;
	case CALLBACK_BACKGROUND_TASKGRAPH:
		FCULambdaRunnable::RunShortLambdaOnBackGroundTask([Function, Target, LatentAction]
		{
			if (Target->IsValidLowLevel())
			{
				Target->ProcessEvent(Function, nullptr);
				LatentAction->Call();
			}
		});
		break;
	default:
		break;
	}
}

#pragma warning( pop )
