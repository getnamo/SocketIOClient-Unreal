// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once
#include "Engine/Classes/Engine/LatentActionManager.h"
#include "LatentActions.h"
#include "Async/TaskGraphInterfaces.h"

/** A simple latent action where we don't hold the value, expect capturing value in lambdas */
class COREUTILITY_API FCULatentAction : public FPendingLatentAction
{
public:
	TFunction<void()> OnCancelNotification = nullptr;

	/** Note that you need to use the resulting call to cleanly exit */
	static FCULatentAction* CreateLatentAction(struct FLatentActionInfo& LatentInfo, UObject* WorldContext);

	FCULatentAction(const FLatentActionInfo& LatentInfo);

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void Call();
	void Cancel();

	virtual void NotifyObjectDestroyed() override;
	virtual void NotifyActionAborted() override;

#if WITH_EDITOR
	virtual FString GetDescription() const override;
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