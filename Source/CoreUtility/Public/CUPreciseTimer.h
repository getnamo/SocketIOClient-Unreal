#pragma once

#include "CoreMinimal.h"

//Toggle to enable/disable timing code logs
#define ENABLE_CUPRECISE_TIMER 1

/** C++ Utility Timer class. 
Usage: 
FCUPreciseTimer::Tick(TEXT("MyMeasurementCategory");
//Your code
FCUPreciseTimer::Tock(TEXT("MyMeasurementCategory"); //This will log the time taken in miliseconds

optionally get the result and handle logging manually
double Elapsed = FCUPreciseTimer::Tock(TEXT("MyMeasurementCategory", false);
*/
class FCUPreciseTimer
{
public:
	static void Tick(const FString& LogMsg = TEXT("TimeTaken"));

	//returns time taken in milliseconds (to micro precision). This function will also log the time taken
	static double Tock(const FString& LogMsg = TEXT("TimeTaken"), bool bShouldLogResult = true);

private:
	double Then;
};