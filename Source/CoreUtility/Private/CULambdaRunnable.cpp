// Copyright 2018-current Getnamo. All Rights Reserved


#include "CULambdaRunnable.h"
#include "Async/Async.h"
#include "Engine/Engine.h"

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

void FCULambdaRunnable::SetTimeout(TFunction<void()>OnDone, float DurationInSec, bool bCallbackOnGameThread /*=true*/)
{
	RunLambdaOnBackGroundThread([OnDone, DurationInSec, bCallbackOnGameThread]()
	{
		FPlatformProcess::Sleep(DurationInSec);

		if (bCallbackOnGameThread)
		{
			RunShortLambdaOnGameThread(OnDone);
		}
		else
		{
			OnDone();
		}
	});
}


FCULatentAction* FCULatentAction::CreateLatentAction(struct FLatentActionInfo& LatentInfo, UObject* WorldContext)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) 
	{
		return nullptr;
	}
	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FCULatentAction *LatentAction = LatentActionManager.FindExistingAction<FCULatentAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	LatentAction = new FCULatentAction(LatentInfo);	//safe to use new since latentactionmanager will delete it
	int32 UUID = LatentInfo.UUID;
	LatentAction->OnCancelNotification = [UUID]()
	{
		UE_LOG(LogTemp, Log, TEXT("%d graph callback cancelled."), UUID);
	};
	LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, LatentAction);
	return LatentAction;
}

FCULatentAction::FCULatentAction(const FLatentActionInfo& LatentInfo) :
	ExecutionFunction(LatentInfo.ExecutionFunction),
	OutputLink(LatentInfo.Linkage),
	CallbackTarget(LatentInfo.CallbackTarget),
	Called(false)
{

}

void FCULatentAction::UpdateOperation(FLatentResponse& Response)
{
	Response.FinishAndTriggerIf(Called, ExecutionFunction, OutputLink, CallbackTarget);
}

void FCULatentAction::Call()
{
	Called = true;
}

void FCULatentAction::Cancel()
{
	if (OnCancelNotification)
	{
		OnCancelNotification();
	}
}

void FCULatentAction::NotifyObjectDestroyed()
{
	Cancel();
}

void FCULatentAction::NotifyActionAborted()
{
	Cancel();
}

#if WITH_EDITOR
FString FCULatentAction::GetDescription() const
{
	{
		if (Called)
		{
			return TEXT("Done.");
		}
		else
		{
			return TEXT("Pending.");
		}
	};
}
#endif