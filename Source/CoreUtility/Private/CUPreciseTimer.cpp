#include "CUPreciseTimer.h"
#include "Core.h"

//Toggle to enable/disable code
#define ENABLE_PRECISE_TIMER 1

#if ENABLE_PRECISE_TIMER
static TMap<FString, TSharedPtr<FCUPreciseTimer>> FPreciseTimerInternalMap;
#endif

void FCUPreciseTimer::Tick(const FString& LogMsg /*= TEXT("TimeTaken")*/)
{
#if ENABLE_PRECISE_TIMER
	TSharedPtr<FCUPreciseTimer> Timer = MakeShareable(new FCUPreciseTimer);
	FPreciseTimerInternalMap.Add(LogMsg, Timer);
	Timer->Then = FPlatformTime::Seconds();	//start timer last so we don't measure anything else
#endif
}

void FCUPreciseTimer::Tock(const FString& LogMsg /*= TEXT("TimeTaken")*/)
{
#if ENABLE_PRECISE_TIMER
	double Now = FPlatformTime::Seconds();
	if (!FPreciseTimerInternalMap.Contains(LogMsg))
	{
		UE_LOG(LogTemp, Warning, TEXT("FPreciseTimer::Tock error: <%s> no such category ticked."), *LogMsg);
		return;
	}
	TSharedPtr<FCUPreciseTimer> Timer = FPreciseTimerInternalMap[LogMsg];
	double Elapsed = (Now - Timer->Then) * 1000.0;
	UE_LOG(LogTemp, Log, TEXT("%s %1.3f ms"), *LogMsg, Elapsed);
	FPreciseTimerInternalMap.Remove(LogMsg);
#endif
}