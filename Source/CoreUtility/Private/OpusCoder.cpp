#include "OpusCoder.h"
#include "CoreMinimal.h"

#define DEBUG_OPUS_LOG 0

FOpusCoder::FOpusCoder()
{
	Encoder = nullptr;
	Decoder = nullptr;
	SampleRate = 16000;
	Channels = 1;
	BitRate = 24000;
	MaxPacketSize = (3 * 1276);
	SetFrameSizeMs(60);
	bApplicationVoip = false;
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
	ResetCoderIfInitialized();
}

void FOpusCoder::SetChannels(int32 InChannels)
{
	Channels = InChannels;
	ResetCoderIfInitialized();
}

void FOpusCoder::SetBitrate(int32 InBitrate)
{
	BitRate = InBitrate;
	ResetCoderIfInitialized();
}

void FOpusCoder::SetFrameSizeMs(int32 Ms)
{
	FrameSizeMs = Ms;
	FrameSize = (SampleRate * FrameSizeMs) / 1000;
	MaxFrameSize = FrameSize * 6;
	ResetCoderIfInitialized();
}

bool FOpusCoder::EncodeStream(const TArray<uint8>& InPCMBytes, TArray<uint8>& OutCompressed, TArray<int32>& OutCompressedFrameSizes)
{
	if (!InitEncoderIfNeeded())
	{
		return false;
	}

#if DEBUG_OPUS_LOG
	DebugLogEncoder();
#endif

	int32 BytesLeft = InPCMBytes.Num();
	int32 Offset = 0;
	int32 BytesWritten = 0;
	const int32 BytesPerFrame = FrameSize * Channels * sizeof(opus_int16);
	TArray<uint8> TempBuffer;
	TArray<uint8> FinalPacket;
	TempBuffer.SetNumUninitialized(MaxPacketSize);
	int32 EncodedBytes = 0;
	opus_int16* PCMDataPtr = 0;

	while (BytesLeft > 0)
	{
		//Final packet requires zero padding
		if(BytesLeft<BytesPerFrame)
		{
			FinalPacket.Append(InPCMBytes.GetData() + Offset, BytesLeft);
			FinalPacket.AddZeroed(BytesPerFrame - BytesLeft);
			PCMDataPtr = (opus_int16*)FinalPacket.GetData();
		}
		else
		{
			PCMDataPtr = (opus_int16*)(InPCMBytes.GetData() + Offset);
		}
		EncodedBytes = opus_encode(Encoder, (const opus_int16*)PCMDataPtr, FrameSize, TempBuffer.GetData(), MaxPacketSize);

#if DEBUG_OPUS_LOG
		DebugLogFrame(TempBuffer.GetData(), EncodedBytes, SampleRate, true);
#endif

		if (EncodedBytes < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_encode err: %s"), opus_strerror(EncodedBytes));
			return false;
		}
		OutCompressed.Append(TempBuffer.GetData(), EncodedBytes);

		OutCompressedFrameSizes.Add(EncodedBytes);
		Offset += BytesPerFrame;
		BytesLeft -= BytesPerFrame;
		BytesWritten += EncodedBytes;
	}

#if DEBUG_OPUS_LOG
	UE_LOG(LogTemp, Log, TEXT("Total packets encoded: %d, total bytes: %d=%d"), OutCompressedFrameSizes.Num(), BytesWritten, OutCompressed.Num());
#endif

	return true;
}

bool FOpusCoder::DecodeStream(const TArray<uint8>& InCompressedBytes, const TArray<int32>& CompressedFrameSizes, TArray<uint8>& OutPCMFrame)
{	
	if (!InitDecoderIfNeeded())
	{
		return false;
	}

#if DEBUG_OPUS_LOG
	DebugLogDecoder();
#endif

	const int32 BytesPerFrame = FrameSize * Channels * sizeof(opus_int16);

	TArray<uint8> TempBuffer;
	TempBuffer.SetNum(MaxFrameSize);

	int32 CompressedOffset = 0;

	for (int FrameIndex = 0; CompressedOffset < InCompressedBytes.Num(); FrameIndex++)
	{

		int32 DecodedSamples = opus_decode(Decoder, InCompressedBytes.GetData() + CompressedOffset, CompressedFrameSizes[FrameIndex], (opus_int16*)TempBuffer.GetData(), FrameSize, 0);

#if DEBUG_OPUS_LOG
		DebugLogFrame(InCompressedBytes.GetData(), CompressedFrameSizes[FrameIndex], SampleRate, false);
		UE_LOG(LogTemp, Log, TEXT("Decoded Samples: %d"), DecodedSamples);
#endif

		if (DecodedSamples > 0)
		{
			OutPCMFrame.Append(TempBuffer.GetData(), DecodedSamples*Channels*sizeof(opus_int16));
		}
		else if (DecodedSamples < 0)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), opus_strerror(DecodedSamples));
			return false;
		}

		CompressedOffset += CompressedFrameSizes[FrameIndex];
	}

#if DEBUG_OPUS_LOG
	UE_LOG(LogTemp, Log, TEXT("decoded into %d bytes"), OutPCMFrame.Num());
#endif
	return true;
}

static void WriteUInt32ToByteArrayLE(TArray<uint8>& InByteArray, int32& Index, const uint32 Value)
{
	InByteArray[Index++] = (uint8)(Value >> 0);
	InByteArray[Index++] = (uint8)(Value >> 8);
	InByteArray[Index++] = (uint8)(Value >> 16);
	InByteArray[Index++] = (uint8)(Value >> 24);
}

bool FOpusCoder::SerializeMinimal(const TArray<uint8>& CompressedBytes, const TArray<int32>& CompressedFrameSizes, TArray<uint8>& OutSerializedBytes)
{
	OutSerializedBytes.SetNumUninitialized(sizeof(int32) + (CompressedFrameSizes.Num() * sizeof(int32)) + CompressedBytes.Num());
	
	//Write total number of packets as int32 first
	int32 Index = 0;
	WriteUInt32ToByteArrayLE(OutSerializedBytes, Index, CompressedFrameSizes.Num());

	//write the compressed frame sizes
	FMemory::Memcpy(&OutSerializedBytes[sizeof(int32)], CompressedFrameSizes.GetData(), CompressedFrameSizes.Num() * sizeof(int32));

	//write the compressed bytes
	FMemory::Memcpy(&OutSerializedBytes[sizeof(int32)*(1 + CompressedFrameSizes.Num())], CompressedBytes.GetData(), CompressedBytes.Num());

	return true;
}

bool FOpusCoder::DeserializeMinimal(const TArray<uint8>& InSerializedMinimalBytes, TArray<uint8>& OutCompressedBytes, TArray<int32>& OutCompressedFrameSizes)
{
	int32 PacketCount = InSerializedMinimalBytes[0];

	//get our packet info
	OutCompressedFrameSizes.SetNumUninitialized(PacketCount);
	FMemory::Memcpy(OutCompressedFrameSizes.GetData(), &InSerializedMinimalBytes[sizeof(int32)], PacketCount*sizeof(int32));

	//get our compressed data
	int32 RemainingBytes = InSerializedMinimalBytes.Num() - ((PacketCount + 1) * sizeof(int32));
	OutCompressedBytes.Append(&InSerializedMinimalBytes[(1 + PacketCount) * sizeof(int32)], RemainingBytes);
	
	return true;
}

int32 FOpusCoder::EncodeFrame(const TArray<uint8>& InPCMFrame, TArray<uint8>& OutCompressed)
{
	return opus_encode(Encoder, (const opus_int16*)InPCMFrame.GetData(), FrameSize, OutCompressed.GetData(), MaxPacketSize);
}

int32 FOpusCoder::DecodeFrame(const TArray<uint8>& InCompressedFrame, TArray<uint8>& OutPCMFrame)
{
	return opus_decode(Decoder, InCompressedFrame.GetData(), InCompressedFrame.Num(), (opus_int16*)OutPCMFrame.GetData(), FrameSize, 0);
}


bool FOpusCoder::InitEncoderIfNeeded()
{
	if (!Encoder)
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

			//Turn on some settings
			//opus_encoder_ctl(Encoder, OPUS_SET_BITRATE(BitRate));
			/*opus_encoder_ctl(Encoder, OPUS_SET_VBR(1));				//variable bit rate encoding
			opus_encoder_ctl(Encoder, OPUS_SET_VBR_CONSTRAINT(0));	//constrained VBR
			opus_encoder_ctl(Encoder, OPUS_SET_COMPLEXITY(1));		//complexity
			opus_encoder_ctl(Encoder, OPUS_SET_INBAND_FEC(0));		//forward error correction
			*/
		}
	}
	return true;
}

bool FOpusCoder::InitDecoderIfNeeded()
{
	if (!Decoder)
	{
		int32 ErrorCode;
		Decoder = opus_decoder_create(SampleRate, Channels, &ErrorCode);
		if (ErrorCode < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("opus_decoder_create err: %d"), ErrorCode);
			return false;
		}
	}
	return true;
}

void FOpusCoder::ResetCoderIfInitialized()
{
	if (Encoder)
	{
		opus_encoder_destroy(Encoder);
		Encoder = nullptr;
		InitEncoderIfNeeded();
	}
	if (Decoder)
	{
		opus_decoder_destroy(Decoder);
		Decoder = nullptr;
		InitDecoderIfNeeded();
	}
}

//Debug utilities
void FOpusCoder::DebugLogEncoder()
{
	int32 ErrCode = 0;
	int32 BitRateLocal = 0;
	int32 Vbr = 0;
	int32 SampleRateLocal = 0;
	int32 Application = 0;
	int32 Signal = 0;
	int32 Complexity = 0;

	ErrCode = opus_encoder_ctl(Encoder, OPUS_GET_BITRATE(&BitRateLocal));
	ErrCode = opus_encoder_ctl(Encoder, OPUS_GET_VBR(&Vbr));
	ErrCode = opus_encoder_ctl(Encoder, OPUS_GET_SAMPLE_RATE(&SampleRateLocal));	
	ErrCode = opus_encoder_ctl(Encoder, OPUS_GET_APPLICATION(&Application));
	ErrCode = opus_encoder_ctl(Encoder, OPUS_GET_SIGNAL(&Signal));
	ErrCode = opus_encoder_ctl(Encoder, OPUS_GET_COMPLEXITY(&Complexity));

	UE_LOG(LogTemp, Log, TEXT("Opus Encoder Details"));
	UE_LOG(LogTemp, Log, TEXT("- Application: %d"), Application);
	UE_LOG(LogTemp, Log, TEXT("- Signal: %d"), Signal);
	UE_LOG(LogTemp, Log, TEXT("- BitRate: %d"), BitRateLocal);
	UE_LOG(LogTemp, Log, TEXT("- SampleRate: %d"), SampleRateLocal);
	UE_LOG(LogTemp, Log, TEXT("- Vbr: %d"), Vbr);
	UE_LOG(LogTemp, Log, TEXT("- Complexity: %d"), Complexity);
}

void FOpusCoder::DebugLogDecoder()
{
	int32 ErrCode = 0;
	int32 Gain = 0;
	int32 Pitch = 0;

	ErrCode = opus_decoder_ctl(Decoder, OPUS_GET_GAIN(&Gain));
	ErrCode = opus_decoder_ctl(Decoder, OPUS_GET_PITCH(&Pitch));

	UE_LOG(LogTemp, Log, TEXT("Opus Decoder Details"));
	UE_LOG(LogTemp, Log, TEXT("- Gain: %d"), Gain);
	UE_LOG(LogTemp, Log, TEXT("- Pitch: %d"), Pitch);
}

void FOpusCoder::DebugLogFrame(const uint8* PacketData, uint32 PacketLength, uint32 InSampleRate, bool bEncode)
{
	// Frame Encoding see http://tools.ietf.org/html/rfc6716#section-3.1
	int32 NumFrames = opus_packet_get_nb_frames(PacketData, PacketLength);
	if (NumFrames == OPUS_BAD_ARG || NumFrames == OPUS_INVALID_PACKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("opus_packet_get_nb_frames: Invalid voice packet data!"));
	}

	int32 NumSamples = opus_packet_get_nb_samples(PacketData, PacketLength, InSampleRate);
	if (NumSamples == OPUS_BAD_ARG || NumSamples == OPUS_INVALID_PACKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("opus_packet_get_nb_samples: Invalid voice packet data!"));
	}

	int32 NumSamplesPerFrame = opus_packet_get_samples_per_frame(PacketData, InSampleRate);
	int32 Bandwidth = opus_packet_get_bandwidth(PacketData);

	const TCHAR* BandwidthStr = nullptr;
	switch (Bandwidth)
	{
	case OPUS_BANDWIDTH_NARROWBAND: // Narrowband (4kHz bandpass)
		BandwidthStr = TEXT("NB");
		break;
	case OPUS_BANDWIDTH_MEDIUMBAND: // Mediumband (6kHz bandpass)
		BandwidthStr = TEXT("MB");
		break;
	case OPUS_BANDWIDTH_WIDEBAND: // Wideband (8kHz bandpass)
		BandwidthStr = TEXT("WB");
		break;
	case OPUS_BANDWIDTH_SUPERWIDEBAND: // Superwideband (12kHz bandpass)
		BandwidthStr = TEXT("SWB");
		break;
	case OPUS_BANDWIDTH_FULLBAND: // Fullband (20kHz bandpass)
		BandwidthStr = TEXT("FB");
		break;
	case OPUS_INVALID_PACKET:
	default:
		BandwidthStr = TEXT("Invalid");
		break;
	}

	uint8 TOC = 0;
	const uint8* frames[48];
	int16 size[48];
	int32 payload_offset = 0;
	int32 NumFramesParsed = opus_packet_parse(PacketData, PacketLength, &TOC, frames, size, &payload_offset);

	int32 TOCEncoding = (TOC & 0xf8) >> 3;
	bool TOCStereo = (TOC & 0x4) != 0 ? true : false;
	int32 TOCMode = TOC & 0x3;

	if (bEncode)
	{
		UE_LOG(LogTemp, Log, TEXT("PacketLength: %d NumFrames: %d NumSamples: %d Bandwidth: %s Encoding: %d Stereo: %d FrameDesc: %d"),
			PacketLength, NumFrames, NumSamples, BandwidthStr, TOCEncoding, TOCStereo, TOCMode);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("PacketLength: %d NumFrames: %d NumSamples: %d Bandwidth: %s Encoding: %d Stereo: %d FrameDesc: %d"),
			PacketLength, NumFrames, NumSamples, BandwidthStr, TOCEncoding, TOCStereo, TOCMode);
	}
}

