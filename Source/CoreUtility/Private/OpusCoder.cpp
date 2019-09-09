#include "OpusCoder.h"
#include "CoreMinimal.h"

FOpusCoder::FOpusCoder()
{
	Encoder = nullptr;
	Decoder = nullptr;
	SampleRate = 16000;
	Channels = 1;
	BitRate = 64000;
	MaxPacketSize = (3 * 1276);
	SetFrameSizeMs(60);
	bApplicationVoip = true;
}

FOpusCoder::~FOpusCoder()
{
	if (Encoder)
	{
		opus_encoder_destroy(Encoder);
		Encoder = nullptr;
	}
	if (Decoder)
	{
		opus_decoder_destroy(Decoder);
		Decoder = nullptr;
	}
}

void FOpusCoder::SetSampleRate(int32 InSamplesPerSec)
{
	SampleRate = InSamplesPerSec;
	SetFrameSizeMs(FrameSizeMs);
}

void FOpusCoder::SetChannels(int32 InChannels)
{
	Channels = InChannels;
}

void FOpusCoder::SetBitrate(int32 InBitrate)
{
	BitRate = InBitrate;
}

void FOpusCoder::SetFrameSizeMs(int32 Ms)
{
	FrameSize = Ms;
	FrameSize = (SampleRate * FrameSizeMs) / 1000;
}

bool FOpusCoder::EncodeStream(const TArray<uint8>& InPCMBytes, TArray<uint8>& OutCompressed)
{
	int32 ErrorCode;
	if (!Encoder)
	{
		int32 ApplicationCode = OPUS_APPLICATION_AUDIO;
		if (bApplicationVoip)
		{
			ApplicationCode = OPUS_APPLICATION_VOIP;
		}
		Encoder = opus_encoder_create(SampleRate, Channels, ApplicationCode, &ErrorCode);
		if (ErrorCode < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_encoder_create err: %d"), ErrorCode);
			return false;
		}
		ErrorCode = opus_encoder_ctl(Encoder, OPUS_SET_BITRATE(BitRate));
		if (ErrorCode < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_encoder_ctl err: %d"), ErrorCode);
			return false;
		}
	}

	//bool bLittleEndian = FGenericPlatformProperties::IsLittleEndian();

	//TArray<opus_int16> In;
	//In.AddUninitialized(Channels*FrameSize);

	//This needs to loop until we're done

	int32 BytesLeft = InPCMBytes.Num();
	int32 Offset = 0;

	while (BytesLeft > 0)
	{
		if (OutCompressed.Num() < Offset + MaxPacketSize)
		{
			OutCompressed.AddUninitialized(MaxPacketSize);
		}
		//endian flip
		/*if (bLittleEndian)
		{
			//convert from little-endian
			for (int i = 0; i < *WaveInfo.pChannels*FrameSize; i++)
			{
				In[i] = PCMBytes[2 * i + 1] << 8 | PCMBytes[2 * i];
			}
		}*/

		int32 SamplesWritten = opus_encode(Encoder, (const opus_int16*)InPCMBytes.GetData(), FrameSize, OutCompressed.GetData(), MaxPacketSize);
		if (SamplesWritten < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_encode err"));
			return false;
		}
		Offset += SamplesWritten; //*2?
		BytesLeft -= FrameSize;
	}

	//trim the bytes to fit total
	//OpusBytes.SetNumUninitialized(Offset);

	return true;
}

bool FOpusCoder::DecodeStream(const TArray<uint8>& InCompressedFrame, TArray<uint8>& OutPCMFrame)
{
	int32 ErrorCode;
	
	if (!Decoder)
	{
		Decoder = opus_decoder_create(SampleRate, Channels, &ErrorCode);
		if (ErrorCode < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_decoder_create err: %d"), ErrorCode);
			return false;
		}
	}

	const int32 MaxFrameSize = 6 * FrameSize;
	bool bLittleEndian = FGenericPlatformProperties::IsLittleEndian(); //technically endian is defined by data not platform, but this is an ok fallback

	Decoder = opus_decoder_create(SampleRate, Channels, &ErrorCode);

	//TArray<opus_int16> In;
	//In.AddUninitialized(Channels*FrameSize);

	TArray<uint8> TempBuffer;
	TempBuffer.SetNum(MaxFrameSize);

	int32 Offset = 0;

	while (Offset < InCompressedFrame.Num())
	{
		//todo: correct for endian
		//convert from little-endian
		/*if (bLittleEndian)
		{
			for (int i = 0; i < Channels*FrameSize; i++)
			{
				//In[i] = PCMBytes[2 * i + 1] << 8 | PCMBytes[2 * i];
			}
		}*/

		int32 DecodedSamples = opus_decode(Decoder, InCompressedFrame.GetData() + Offset, FrameSize, (opus_int16*)TempBuffer.GetData(), MaxFrameSize, 0);


		if (DecodedSamples > 0)
		{
			OutPCMFrame.Append(TempBuffer.GetData(), DecodedSamples);
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

			return false;
		}

		Offset += FrameSize;
	}
	return true;
}

bool FOpusCoder::EncodeFrame(const TArray<uint8>& InPCMFrame, TArray<uint8>& OutCompressed)
{
	return false;
}

bool FOpusCoder::DecodeFrame(const TArray<uint8>& InCompressedFrame, TArray<uint8>& OutPCMFrame)
{
	return false;
}

