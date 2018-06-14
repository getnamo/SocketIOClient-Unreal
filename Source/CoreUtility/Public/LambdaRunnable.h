// Copyright 2018-current Getnamo. All Rights Reserved
// Available under MIT license at https://github.com/getnamo/socketio-client-ue4

#pragma once

/*
*	Convenience wrappers for common thread/task work flow. Run background task on thread, callback via task graph on game thread
*/
class COREUTILITY_API FLambdaRunnable
{
public:

	/*
	Runs the passed lambda on the background thread, new thread per call
	*/
	static void RunLambdaOnBackGroundThread(TFunction< void()> InFunction);

	/*
	Runs the passed lambda on the background thread pool
	*/
	static void RunLambdaOnBackGroundThreadPool(TFunction< void()> InFunction);

	/*
	Runs a short lambda on the game thread via task graph system
	*/
	static FGraphEventRef RunShortLambdaOnGameThread(TFunction< void()> InFunction);
};