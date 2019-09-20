// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "Runtime/Engine/Public/LatentActions.h"
#include "Runtime/Core/Public/Async/TaskGraphInterfaces.h"

//A simple latent action where we don't hold the value, expect capturing value in lambdas
class COREUTILITY_API FCUPendingLatentAction : public FPendingLatentAction
{
public:
	TFunction<void()> OnCancelNotification = nullptr;

	FCUPendingLatentAction(const FLatentActionInfo& LatentInfo) :
		ExecutionFunction(LatentInfo.ExecutionFunction),
		OutputLink(LatentInfo.Linkage),
		CallbackTarget(LatentInfo.CallbackTarget),
		Called(false)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		Response.FinishAndTriggerIf(Called, ExecutionFunction, OutputLink, CallbackTarget);
	}

	void Call()
	{
		Called = true;
	}

	void Cancel()
	{
		if (OnCancelNotification)
		{
			OnCancelNotification();
		}
	}

	virtual void NotifyObjectDestroyed() override
	{
		Cancel();
	}

	virtual void NotifyActionAborted() override
	{
		Cancel();
	}


#if WITH_EDITOR
	virtual FString GetDescription() const override
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
#endif


	const FName ExecutionFunction;
	const int32 OutputLink;
	const FWeakObjectPtr CallbackTarget;

private:
	bool Called;
};

/**
*	Convenience wrappers for common thread/task work flow. Run background task on thread, callback via task graph on game thread
*/
class COREUTILITY_API FCULambdaRunnable
{
public:

	/**
	*	Runs the passed lambda on the background thread, new thread per call
	*/
	static void RunLambdaOnBackGroundThread(TFunction< void()> InFunction);

	/**
	*	Runs the passed lambda on the background thread pool
	*/
	static void RunLambdaOnBackGroundThreadPool(TFunction< void()> InFunction);

	/**
	*	Runs a short lambda on the game thread via task graph system
	*/
	static FGraphEventRef RunShortLambdaOnGameThread(TFunction< void()> InFunction);

	/**
	*	Runs a short lambda on background thread via task graph system
	*/
	static FGraphEventRef RunShortLambdaOnBackGroundTask(TFunction< void()> InFunction);

	/** 
	*	Runs a thread with idle for duration before calling back on game thread. 
	*	Due to context cost recommended for >0.1sec durations.
	*/
	static void SetTimeout(TFunction<void()>OnDone, float DurationInSec, bool bCallbackOnGameThread = true);
};