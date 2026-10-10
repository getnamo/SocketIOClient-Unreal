// Copyright 2026-current Getnamo. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Async/TaskGraphInterfaces.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Misc/ScopeLock.h"
#include "WebSocketLibClient.h"

namespace WebSocketTest
{
	/** Poll until Condition holds. bPumpGameThread runs queued game thread tasks, which is where game thread callbacks land. */
	inline bool WaitFor(TFunctionRef<bool()> Condition, float TimeoutSeconds = 5.f, bool bPumpGameThread = false)
	{
		const double End = FPlatformTime::Seconds() + TimeoutSeconds;
		while (true)
		{
			if (bPumpGameThread)
			{
				FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
			}
			if (Condition())
			{
				return true;
			}
			if (FPlatformTime::Seconds() > End)
			{
				return false;
			}
			FPlatformProcess::Sleep(0.002f);
		}
	}

	/** Keep running game thread tasks for a while, to see that nothing else arrives */
	inline void Settle(float Seconds, bool bPumpGameThread = false)
	{
		WaitFor([]() { return false; }, Seconds, bPumpGameThread);
	}

	/** Records FWebSocketLibClient callbacks, which arrive on the network thread */
	class FLibRecorder : public TSharedFromThis<FLibRecorder, ESPMode::ThreadSafe>
	{
	public:
		FWebSocketLibCallbacks MakeCallbacks()
		{
			TSharedRef<FLibRecorder, ESPMode::ThreadSafe> Self = AsShared();
			FWebSocketLibCallbacks Callbacks;
			Callbacks.OnOpen = [Self](const FString& InProtocol)
			{
				FScopeLock Guard(&Self->Lock);
				Self->Opens++;
				Self->Protocol = InProtocol;
			};
			Callbacks.OnFail = [Self](const FString& Error, int32 HttpStatus)
			{
				FScopeLock Guard(&Self->Lock);
				Self->Fails++;
				Self->FailError = Error;
				Self->FailHttpStatus = HttpStatus;
			};
			Callbacks.OnClose = [Self](int32 StatusCode, const FString& Reason, bool bWasClean)
			{
				FScopeLock Guard(&Self->Lock);
				Self->Closes++;
				Self->CloseCode = StatusCode;
				Self->CloseReason = Reason;
				Self->bCloseClean = bWasClean;
			};
			Callbacks.OnText = [Self](const FString& Message)
			{
				FScopeLock Guard(&Self->Lock);
				Self->Texts.Add(Message);
			};
			Callbacks.OnBinary = [Self](const TArray<uint8>& Bytes)
			{
				FScopeLock Guard(&Self->Lock);
				Self->Binaries.Add(Bytes);
			};
			return Callbacks;
		}

		/** Copy a recorded value under the lock */
		template<typename ValueType>
		ValueType Get(ValueType FLibRecorder::* Member) const
		{
			FScopeLock Guard(&Lock);
			return this->*Member;
		}

		int32 NumTexts() const { FScopeLock Guard(&Lock); return Texts.Num(); }
		int32 NumBinaries() const { FScopeLock Guard(&Lock); return Binaries.Num(); }

		int32 Opens = 0;
		FString Protocol;
		int32 Fails = 0;
		FString FailError;
		int32 FailHttpStatus = 0;
		int32 Closes = 0;
		int32 CloseCode = 0;
		FString CloseReason;
		bool bCloseClean = false;
		TArray<FString> Texts;
		TArray<TArray<uint8>> Binaries;

	private:
		mutable FCriticalSection Lock;
	};

	typedef TSharedRef<FLibRecorder, ESPMode::ThreadSafe> FLibRecorderRef;

	inline FLibRecorderRef MakeRecorder()
	{
		return MakeShared<FLibRecorder, ESPMode::ThreadSafe>();
	}

	inline TArray<uint8> MakeBytes(int32 Num, int32 Seed = 0)
	{
		TArray<uint8> Bytes;
		Bytes.SetNumUninitialized(Num);
		for (int32 Index = 0; Index < Num; Index++)
		{
			Bytes[Index] = (uint8)((Index * 31 + Seed) % 251);
		}
		return Bytes;
	}
}
