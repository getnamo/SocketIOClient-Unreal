// Copyright 2018-current Getnamo. All Rights Reserved
// Available under MIT license at https://github.com/getnamo/socketio-client-ue4

#include "LambdaRunnable.h"
#include "Async.h"
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