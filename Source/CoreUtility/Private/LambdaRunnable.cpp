// Copyright 2018-current Getnamo. All Rights Reserved


#include "LambdaRunnable.h"
#include "Runtime/Core/Public/Async/Async.h"
#include "CoreUtilityPrivatePCH.h"

void FLambdaRunnable::RunLambdaOnBackGroundThread(TFunction< void()> InFunction)
{
	Async(EAsyncExecution::Thread, InFunction);
}

void FLambdaRunnable::RunLambdaOnBackGroundThreadPool(TFunction< void()> InFunction)
{
	Async(EAsyncExecution::ThreadPool, InFunction);
}

FGraphEventRef FLambdaRunnable::RunShortLambdaOnGameThread(TFunction< void()> InFunction)
{
	return FFunctionGraphTask::CreateAndDispatchWhenReady(InFunction, TStatId(), nullptr, ENamedThreads::GameThread);
}