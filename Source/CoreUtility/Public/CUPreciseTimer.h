#pragma once

#include "CoreMinimal.h"

//Toggle to enable/disable timing code logs
#define ENABLE_CUPRECISE_TIMER 1

/** 
*	C++ Utility Timer class. Multiple categories can be used simultaneously.
*
*	Usage: 
*	FCUPreciseTimer::Tick(TEXT("MyMeasurementCategory");
*	//Your code
*	FCUPreciseTimer::Tock(TEXT("MyMeasurementCategory"); //This will log the time taken in miliseconds
*
*	optionally get the result and handle logging manually
*	double Elapsed = FCUPreciseTimer::Tock(TEXT("MyMeasurementCategory", false);
*/
class COREUTILITY_API FCUPreciseTimer
{
public:
	/**
	*	Start a timer for given category
	*/
	static void Tick(const FString& LogMsg = TEXT("TimeTaken"));

	/**
	*	Returns time taken in milliseconds (to micro precision). This function will also log the time taken
	*/
	static double Tock(const FString& LogMsg = TEXT("TimeTaken"), bool bShouldLogResult = true);

private:
	double Then;
};

/** 
*	Wrapper for FCUPreciseTimer calls. 
*
*	Usage:
*	{
*		//code you do not wish to measure
*
*		FCUScopeTimer Timer(TEXT("My Message"));
*
*		//your code
*	}
*	It will log duration when you exit the scope
*/
class COREUTILITY_API FCUScopeTimer
{
public:
	FCUScopeTimer(const FString& InLogMsg);
	~FCUScopeTimer();
private:
	FString LogMessage;
};