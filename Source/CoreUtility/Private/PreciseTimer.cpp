#include "PreciseTimer.h"

static TMap<FString, TSharedPtr<FPreciseTimer>> FPreciseTimerInternalMap;

void FPreciseTimer::Tick(const FString& LogMsg /*= TEXT("TimeTaken")*/)
{
	TSharedPtr<FPreciseTimer> Timer = MakeShareable(new FPreciseTimer);
	FPreciseTimerInternalMap.Add(LogMsg, Timer);
	Timer->Then = FPlatformTime::Seconds();	//start timer last so we don't measure anything else
}

void FPreciseTimer::Tock(const FString& LogMsg /*= TEXT("TimeTaken")*/)
{
	double Now = FPlatformTime::Seconds();
	TSharedPtr<FPreciseTimer> Timer = FPreciseTimerInternalMap[LogMsg];
	double Elapsed = (Now - Timer->Then) * 1000.0;
	UE_LOG(LogTemp, Log, TEXT("%s %1.3f ms"), *LogMsg, Elapsed);
	FPreciseTimerInternalMap.Remove(LogMsg);
}