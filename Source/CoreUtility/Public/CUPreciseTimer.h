#pragma once

class FCUPreciseTimer
{
public:
	static void Tick(const FString& LogMsg = TEXT("TimeTaken"));

	//returns time taken in milliseconds (to micro precision)
	static void Tock(const FString& LogMsg = TEXT("TimeTaken"));

private:
	double Then;
};