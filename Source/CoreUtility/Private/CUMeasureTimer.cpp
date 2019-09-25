#include "CUMeasureTimer.h"
#include "HAL/PlatformTime.h"

#if ENABLE_CUPRECISE_TIMER
static TMap<FString, TSharedPtr<FCUMeasureTimer>> FPreciseTimerInternalMap;
#endif

void FCUMeasureTimer::Tick(const FString& LogMsg /*= TEXT("TimeTaken")*/)
{
#if ENABLE_CUPRECISE_TIMER
	TSharedPtr<FCUMeasureTimer> Timer = MakeShareable(new FCUMeasureTimer);
	FPreciseTimerInternalMap.Add(LogMsg, Timer);
	Timer->Then = FPlatformTime::Seconds();	//start timer last so we don't measure anything else
#endif
}

double FCUMeasureTimer::Tock(const FString& LogMsg /*= TEXT("TimeTaken")*/, bool bShouldLogResult /*= true*/)
{
#if ENABLE_CUPRECISE_TIMER
	double Now = FPlatformTime::Seconds();
	if (!FPreciseTimerInternalMap.Contains(LogMsg))
	{
		UE_LOG(LogTemp, Warning, TEXT("FCUMeasureTimer::Tock error: <%s> no such category ticked."), *LogMsg);
		return 0.0;
	}
	TSharedPtr<FCUMeasureTimer> Timer = FPreciseTimerInternalMap[LogMsg];
	double Elapsed = (Now - Timer->Then) * 1000.0;
	if (bShouldLogResult)
	{
		UE_LOG(LogTemp, Log, TEXT("%s %1.3f ms"), *LogMsg, Elapsed);
	}
	FPreciseTimerInternalMap.Remove(LogMsg);
#else
	return 0.0;
#endif
	return Elapsed;
}

FCUScopeTimer::FCUScopeTimer(const FString& LogMsg)
{
	LogMessage = LogMsg;
	FCUMeasureTimer::Tick(LogMsg);
}

FCUScopeTimer::~FCUScopeTimer()
{
	FCUMeasureTimer::Tock(LogMessage);
}
