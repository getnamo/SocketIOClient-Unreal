// Copyright 2018-current Getnamo. All Rights Reserved


#include "CoreUtilityBPLibrary.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "LambdaRunnable.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/Core/Public/Async/Async.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Core/Public/HAL/ThreadSafeBool.h"
#include "Runtime/RHI/Public/RHI.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Engine/Public/OpusAudioInfo.h"
#include "Developer/TargetPlatform/Public/Interfaces/IAudioFormat.h"
#include "CoreMinimal.h"
#include "Engine/Engine.h"

#define WITH_OPUS (PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_XBOXONE || PLATFORM_ANDROID)

#if WITH_OPUS
#include "opus.h"
#include "ogg/ogg.h"
#endif

#pragma warning( push )
#pragma warning( disable : 5046)

//Render thread wrapper struct
struct FUpdateTextureData
{
	UTexture2D* Texture2D;
	FUpdateTextureRegion2D Region;
	uint32 Pitch;
	const TArray<uint8>* BufferArray;
	TSharedPtr<IImageWrapper> Wrapper;	//to keep the uncompressed data alive
};

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

//TSharedPtr<IStreamedCompressedInfo> Coder;


TArray<uint8> UCoreUtilityBPLibrary::Conv_OpusBytesToWav(const TArray<uint8>& InBytes)
{
	TArray<uint8> RawBytes;

	OpusDecoder* Decoder;
	int32 OpusErr;

	// Frame size must be one of 2.5, 5, 10, 20, 40 or 60 ms
	const int32 FrameSizeMs = 60;
	const int32 SampleRate = 16000;
	const int32 Channels = 1;
	int32 FrameSize = (SampleRate * FrameSizeMs) / 1000;
	const int32 BitRate = 24000;	//voip bitrate (64kbs for mp3 if used)

	const int32 MaxFrameSize = 6 * FrameSize;
	const int32 MaxPacketSize = (3 * 1276);
	bool bLittleEndian = FGenericPlatformProperties::IsLittleEndian(); //technically endian is defined by data not platform, but this is an ok fallback

	Decoder = opus_decoder_create(SampleRate, Channels, &OpusErr);

	TArray<opus_int16> In;
	In.AddUninitialized(Channels*FrameSize);

	TArray<uint8> TempBuffer;
	TempBuffer.SetNum(MaxFrameSize);

	int32 Offset = 0;

	while (Offset<InBytes.Num())
	{
		//todo: correct for endian
		//convert from little-endian
		if (bLittleEndian)
		{
			for (int i = 0; i < Channels*FrameSize; i++)
			{
				//In[i] = PCMBytes[2 * i + 1] << 8 | PCMBytes[2 * i];
			}
		}

		int32 DecodedSamples = opus_decode(Decoder, InBytes.GetData() + Offset, FrameSize, (opus_int16*)TempBuffer.GetData(), MaxFrameSize, 0);
		

		if (DecodedSamples > 0)
		{
			RawBytes.Append(TempBuffer.GetData(), DecodedSamples);
		}
		else if (DecodedSamples < 0)
		{
			switch (DecodedSamples)
			{
			case OPUS_BAD_ARG:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_BAD_ARG, One or more invalid/out of range arguments"));
				break;
			case OPUS_BUFFER_TOO_SMALL:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_BUFFER_TOO_SMALL, The mode struct passed is invalid"));
				break;
			case OPUS_INTERNAL_ERROR:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_INTERNAL_ERROR,  An internal error was detected"));
				break;
			case OPUS_INVALID_PACKET:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_INVALID_PACKET, The compressed data passed is corrupted (Offset: %d, FrameSize: %d)"), Offset, FrameSize);
				break;
			case OPUS_UNIMPLEMENTED:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_UNIMPLEMENTED, Invalid/unsupported request number"));
				break;
			case OPUS_ALLOC_FAIL:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_ALLOC_FAIL, Memory allocation has failed"));
				break;
			case OPUS_INVALID_STATE:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: OPUS_INVALID_STATE, An encoder or decoder structure is invalid or already freed"));
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("opus_decode err: %d"), FrameSize);
				break;
			}
			
			return RawBytes;
		}

		Offset += FrameSize;
	}

	TArray<uint8> WavBytes;
	SerializeWaveFile(WavBytes, RawBytes.GetData(), RawBytes.Num(), Channels, SampleRate);

	return WavBytes;
}


TArray<uint8> UCoreUtilityBPLibrary::Conv_WavBytesToOpus(const TArray<uint8>& InBytes)
{
	TArray<uint8> OpusBytes;

	FWaveModInfo WaveInfo;


	if (!WaveInfo.ReadWaveInfo(InBytes.GetData(), InBytes.Num()))
	{
		return OpusBytes;
	}

	TArray<uint8> PCMBytes;
	PCMBytes.Append(WaveInfo.SampleDataStart, WaveInfo.SampleDataSize);

	OpusEncoder* Encoder;
	int32 OpusErr;
	const int32 Channels = *WaveInfo.pChannels;

	Encoder = opus_encoder_create(*WaveInfo.pSamplesPerSec, Channels, OPUS_APPLICATION_AUDIO, &OpusErr);

	if (OpusErr < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("opus_encoder_create err"));
		return OpusBytes;
	}

	// Frame size must be one of 2.5, 5, 10, 20, 40 or 60 ms
	const int32 FrameSizeMs = 60;

	// Calculate frame size required by Opus
	const int32 FrameSize = (*WaveInfo.pSamplesPerSec * FrameSizeMs) / 1000;

	const int32 BitRate = 64000;	//voip bitrate (64kbs for mp3 if used)
	const int32 MaxPacketSize = (3 * 1276);
	bool bLittleEndian = FGenericPlatformProperties::IsLittleEndian();

	TArray<opus_int16> In;
	In.AddUninitialized(Channels*FrameSize);

	OpusErr = opus_encoder_ctl(Encoder, OPUS_SET_BITRATE(BitRate));

	//This needs to loop until we're done
	
	int32 BytesLeft = WaveInfo.SampleDataSize;
	int32 Offset = 0;

	while (BytesLeft > 0)
	{
		if (OpusBytes.Num() < Offset + MaxPacketSize)
		{
			OpusBytes.AddUninitialized(MaxPacketSize);
		}
		//endian flip
		if (bLittleEndian)
		{
			//convert from little-endian
			for (int i = 0; i < *WaveInfo.pChannels*FrameSize; i++)
			{
				In[i] = PCMBytes[2 * i + 1] << 8 | PCMBytes[2 * i];
			}
		}

		int32 BytesWritten = opus_encode(Encoder, In.GetData(), FrameSize, OpusBytes.GetData(), MaxPacketSize);
		if (BytesWritten < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_encode err"));
			return OpusBytes;
		}
		Offset += BytesWritten;
		BytesLeft -= FrameSize;
	}

	OpusBytes.SetNumUninitialized(Offset);

	opus_encoder_destroy(Encoder);

	return OpusBytes;
}

USoundWave* UCoreUtilityBPLibrary::Conv_WavBytesToSoundWave(const TArray<uint8>& InBytes)
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

TArray<uint8> UCoreUtilityBPLibrary::Conv_SoundWaveToWavBytes(USoundWave* SoundWave)
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

void UCoreUtilityBPLibrary::SetSoundWaveFromWavBytes(USoundWaveProcedural* InSoundWave, const TArray<uint8>& InBytes)
{
	FWaveModInfo WaveInfo;

	if (WaveInfo.ReadWaveInfo(InBytes.GetData(), InBytes.Num()))
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

void UCoreUtilityBPLibrary::CallFunctionOnThread(const FString& FunctionName, ESIOCallbackType ThreadType, UObject* WorldContextObject /*= nullptr*/)
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
			FLambdaRunnable::RunShortLambdaOnGameThread([Function, Target]
			{
				if (Target->IsValidLowLevel())
				{
					Target->ProcessEvent(Function, nullptr);
				}
			});
		}
		break;
	case CALLBACK_BACKGROUND_THREADPOOL:
		FLambdaRunnable::RunLambdaOnBackGroundThreadPool([Function, Target]
		{
			if (Target->IsValidLowLevel())
			{
				Target->ProcessEvent(Function, nullptr);
			}
		});
		break;
	case CALLBACK_BACKGROUND_TASKGRAPH:
		FLambdaRunnable::RunShortLambdaOnBackGroundTask([Function, Target]
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

#pragma warning( pop )