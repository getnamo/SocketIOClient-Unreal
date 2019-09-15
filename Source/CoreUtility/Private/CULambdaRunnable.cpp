// Copyright 2018-current Getnamo. All Rights Reserved


#include "CULambdaRunnable.h"
#include "Runtime/Core/Public/Async/Async.h"

void FCULambdaRunnable::RunLambdaOnBackGroundThread(TFunction< void()> InFunction)
{
	Async(EAsyncExecution::Thread, InFunction);
}

void FCULambdaRunnable::RunLambdaOnBackGroundThreadPool(TFunction< void()> InFunction)
{
	Async(EAsyncExecution::ThreadPool, InFunction);
}

FGraphEventRef FCULambdaRunnable::RunShortLambdaOnGameThread(TFunction< void()> InFunction)
{
	return FFunctionGraphTask::CreateAndDispatchWhenReady(InFunction, TStatId(), nullptr, ENamedThreads::GameThread);
}

FGraphEventRef FCULambdaRunnable::RunShortLambdaOnBackGroundTask(TFunction< void()> InFunction)
{
	return FFunctionGraphTask::CreateAndDispatchWhenReady(InFunction, TStatId(), nullptr, ENamedThreads::AnyThread);
}

void FCULambdaRunnable::SetTimeout(TFunction<void()>OnDone, float DurationInSec)
{
	RunLambdaOnBackGroundThread([OnDone, DurationInSec]()
	{
		FPlatformProcess::Sleep(DurationInSec);

		RunShortLambdaOnGameThread(OnDone);
	});
}
