#pragma once

#include "SocketIOClientPrivatePCH.h"
#include "SIOLambdaRunnable.h"

uint64 FSIOLambdaRunnable::ThreadNumber = 0;

FSIOLambdaRunnable::FSIOLambdaRunnable(TFunction< void()> InFunction)
{
	FunctionPointer = InFunction;
	Finished = false;
	Number = ThreadNumber;

	FString threadStatGroup = FString::Printf(TEXT("FSIOLambdaRunnable%d"), ThreadNumber);
	Thread = NULL;
	Thread = FRunnableThread::Create(this, *threadStatGroup, 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
	ThreadNumber++;

	//Runnables.Add(this);
}

FSIOLambdaRunnable::~FSIOLambdaRunnable()
{
	if (Thread == NULL)
	{
		delete Thread;
		Thread = NULL;
	}

	//Runnables.Remove(this);
}

//Init
bool FSIOLambdaRunnable::Init()
{
	//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable %d Init"), Number);
	return true;
}

//Run
uint32 FSIOLambdaRunnable::Run()
{
	if (FunctionPointer != nullptr)
	{
		FunctionPointer();
	}
	//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable %d Run complete"), Number);
	return 0;
}

//stop
void FSIOLambdaRunnable::Stop()
{
	Finished = true;
}

void FSIOLambdaRunnable::Kill()
{
	Thread->Kill(false);
	Finished = true;
}

void FSIOLambdaRunnable::Exit()
{
	Finished = true;
	//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable %d Exit"), Number);

	//delete ourselves when we're done
	delete this;
}

void FSIOLambdaRunnable::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

FSIOLambdaRunnable* FSIOLambdaRunnable::RunLambdaOnBackGroundThread(TFunction< void()> InFunction)
{
	FSIOLambdaRunnable* Runnable;
	if (FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FSIOLambdaRunnable(InFunction);
		//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable RunLambdaBackGroundThread"));
		return Runnable;
	}
	else
	{
		return nullptr;
	}
}

FGraphEventRef FSIOLambdaRunnable::RunShortLambdaOnGameThread(TFunction< void()> InFunction)
{
	return FFunctionGraphTask::CreateAndDispatchWhenReady(InFunction, TStatId(), nullptr, ENamedThreads::GameThread);
}

void FSIOLambdaRunnable::ShutdownThreads()
{
	/*for (auto Runnable : Runnables)
	{
	if (Runnable != nullptr)
	{
	delete Runnable;
	}
	Runnable = nullptr;
	}*/
}