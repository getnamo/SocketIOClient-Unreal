// Copyright 2019-current Getnamo. All Rights Reserved

#pragma once

#define WITH_OPUS (PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_XBOXONE || PLATFORM_ANDROID)

#if WITH_OPUS
#include "opus.h"
#include "ogg/ogg.h"
#endif

//Bare minimum struct for transferring opus bytes.
struct FOpusMinimalStream
{
	TArray<int16> PacketSizes;  // Maximum packet size is 32768 (much larger than typical packet)
	TArray<uint8> CompressedBytes;
};


//Symmetric coder for e.g. voip written from raw libopus due to how hidden the opus coder is in the engine (requires online subsystem)
class FOpusCoder
{
public:
	FOpusCoder();
	~FOpusCoder();

	/** Set Encoder and Decoder Samples per sec */
	void SetSampleRate(int32 InSampleRate);
	void SetChannels(int32 Channels);
	void SetBitrate(int32 Bitrate);
	void SetFrameSizeMs(int32 FrameSizeInMs);

	/** Expects raw PCM data, outputs compressed raw opus data along with compressed frame sizes*/
	bool EncodeStream(const TArray<uint8>& InPCMBytes, FOpusMinimalStream& OutStream);
	bool DecodeStream(const FOpusMinimalStream& InStream, TArray<uint8>& OutPCMFrame);


	//Format: PacketCount, PacketSizes, CompressedOpusBytes. Expects settings set in a different stream
	bool SerializeMinimal(const FOpusMinimalStream& InStream, TArray<uint8>& OutSerializedBytes);
	bool DeserializeMinimal(const TArray<uint8>& InSerializedMinimalBytes, FOpusMinimalStream& OutStream);

	//Handle a single frame
	int32 EncodeFrame(const TArray<uint8>& InPCMFrame, TArray<uint8>& OutCompressed);
	int32 DecodeFrame(const TArray<uint8>& InCompressedFrame, TArray<uint8>& OutPCMFrame);

	//Todo: add ogg file format wrapper for raw opus bytes

	//Intended to be Read-only
	int32 Channels;
	int32 SampleRate;

	//Whether we should reset the conder per stream
	bool bResetBetweenEncoding;

	void ResetCoderIfInitialized();

protected:
	//Call this if some settings need to be reflected (all setters all this)
	bool InitEncoderIfNeeded();
	bool InitDecoderIfNeeded();

private:
	OpusEncoder* Encoder;
	OpusDecoder* Decoder;

	int32 BitRate;
	int32 MaxPacketSize;
	int32 FrameSizeMs;
	int32 FrameSize;
	int32 MaxFrameSize;
	bool bApplicationVoip;

	//Debug utilities
	void DebugLogEncoder();
	void DebugLogDecoder();
	void DebugLogFrame(const uint8* PacketData, uint32 PacketLength, uint32 SampleRate, bool bEncode);
};