// Copyright 2019-current Getnamo. All Rights Reserved


#pragma once
#include "CoreMinimal.h"

//Toggle to enable/disable timing code logs. Overridable from a build script: defining it
//unconditionally here meant Tock's #else branch could never compile, so the off mode the
//header advertises was never actually reachable.
#ifndef ENABLE_CUPRECISE_TIMER
#define ENABLE_CUPRECISE_TIMER 1
#endif

/** 
*	C++ Utility Timer class. Multiple categories can be used simultaneously.
*
*	Usage: 
*	FCUMeasureTimer::Tick(TEXT("MyMeasurementCategory"));
*	//Your code
*	FCUMeasureTimer::Tock(TEXT("MyMeasurementCategory")); //This will log the time taken in miliseconds
*
*	optionally get the result and handle logging manually
*	double Elapsed = FCUMeasureTimer::Tock(TEXT("MyMeasurementCategory", false);
*/
class COREUTILITY_API FCUMeasureTimer
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
*	Wrapper for FCUMeasureTimer calls. 
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