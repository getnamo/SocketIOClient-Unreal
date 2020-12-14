// Modifications Copyright 2018-current Getnamo. All Rights Reserved


// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "Delegates/Delegate.h"
#include "Http.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Dom/JsonValue.h"
#include "LatentActions.h"
#include "CULambdaRunnable.h"
#include "Engine/LatentActionManager.h"
#include "SIOJTypes.h"
#include "SIOJRequestJSON.generated.h"

/**
 * @author Original latent action class by https://github.com/unktomi
 */
template <class T> class SIOJSON_API FSIOJLatentAction : public FPendingLatentAction
{
public:
	virtual void Call(const T &Value) 
	{
		Result = Value;
		Called = true;
	}

	void operator()(const T &Value)
	{
		Call(Value);
	}

	void Cancel();
  
	FSIOJLatentAction(FWeakObjectPtr RequestObj, T& ResultParam, const FLatentActionInfo& LatentInfo) :
		Called(false),
		Request(RequestObj),
		ExecutionFunction(LatentInfo.ExecutionFunction),
		OutputLink(LatentInfo.Linkage),
		CallbackTarget(LatentInfo.CallbackTarget),
		Result(ResultParam)
	{
	}
  
	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		Response.FinishAndTriggerIf(Called, ExecutionFunction, OutputLink, CallbackTarget);
	}

	virtual void NotifyObjectDestroyed()
	{
		Cancel();
	}

	virtual void NotifyActionAborted()
	{
		Cancel();
	}

private:
	bool Called;
	FWeakObjectPtr Request;

public:
	const FName ExecutionFunction;
	const int32 OutputLink;
	const FWeakObjectPtr CallbackTarget;
	T &Result;
};


/** Generate a delegates for callback events */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestComplete, class USIOJRequestJSON*, Request);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestFail, class USIOJRequestJSON*, Request);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaticRequestComplete, class USIOJRequestJSON*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaticRequestFail, class USIOJRequestJSON*);


/**
 * General helper class http requests via blueprints
 */
UCLASS(BlueprintType, Blueprintable)
class SIOJSON_API USIOJRequestJSON : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	//////////////////////////////////////////////////////////////////////////
	// Construction

	/** Creates new request (totally empty) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Construct Json Request (Empty)", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Request")
	static USIOJRequestJSON* ConstructRequest(UObject* WorldContextObject);

	/** Creates new request with defined verb and content type */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Construct Json Request", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "SIOJ|Request")
	static USIOJRequestJSON* ConstructRequestExt(UObject* WorldContextObject, ESIORequestVerb Verb, ESIORequestContentType ContentType);

	/** Set verb to the request */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetVerb(ESIORequestVerb Verb);

	/** Set custom verb to the request */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetCustomVerb(FString Verb);

	/** Set content type to the request. If you're using the x-www-form-urlencoded, 
	 * params/constaints should be defined as key=ValueString pairs from Json data */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetContentType(ESIORequestContentType ContentType);

	/** Set content type of the request for binary post data */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetBinaryContentType(const FString &ContentType);

	/** Set content of the request for binary post data */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetBinaryRequestContent(const TArray<uint8> &Content);

	/** Sets optional header info */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetHeader(const FString& HeaderName, const FString& HeaderValue);


	//////////////////////////////////////////////////////////////////////////
	// Destruction and reset

	/** Reset all internal saved data */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility")
	void ResetData();

	/** Reset saved request data */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void ResetRequestData();

	/** Reset saved response data */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	void ResetResponseData();

	/** Cancel latent response waiting  */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	void Cancel();


	//////////////////////////////////////////////////////////////////////////
	// JSON data accessors

	/** Get the Request Json object */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	USIOJsonObject* GetRequestObject();

	/** Set the Request Json object */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	void SetRequestObject(USIOJsonObject* JsonObject);

	/** Get the Response Json object */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	USIOJsonObject* GetResponseObject();

	/** Set the Response Json object */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	void SetResponseObject(USIOJsonObject* JsonObject);


	///////////////////////////////////////////////////////////////////////////
	// Request/response data access

	/** Get url of http request */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	FString GetURL();

	/** Get status of http request */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	ESIORequestStatus GetStatus();

	/** Get the response code of the last query */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	int32 GetResponseCode();

	/** Get value of desired response header */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	FString GetResponseHeader(const FString HeaderName);
	
	/** Get list of all response headers */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Response")
	TArray<FString> GetAllResponseHeaders();

	//////////////////////////////////////////////////////////////////////////
	// URL processing

	/** Open URL with current setup */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request")
	virtual void ProcessURL(const FString& Url = TEXT("http://alyamkin.com"));

	/** Open URL in latent mode */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Request", meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	virtual void ApplyURL(const FString& Url, USIOJsonObject *&Result, UObject* WorldContextObject, struct FLatentActionInfo LatentInfo);

	/** Apply current internal setup to request and process it */
	void ProcessRequest();


	//////////////////////////////////////////////////////////////////////////
	// Request callbacks

private:
	/** Internal bind function for the IHTTPRequest::OnProcessRequestCompleted() event */
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnProcessRequestCompleteBinaryResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	/** Event occured when the request has been completed */
	UPROPERTY(BlueprintAssignable, Category = "SIOJ|Event")
	FOnRequestComplete OnRequestComplete;

	/** Event occured when the request wasn't successfull */
	UPROPERTY(BlueprintAssignable, Category = "SIOJ|Event")
	FOnRequestFail OnRequestFail;
	
	/** Event occured when the request has been completed */
	FOnStaticRequestComplete OnStaticRequestComplete;
	
	/** Event occured when the request wasn't successfull */
	FOnStaticRequestFail OnStaticRequestFail;
	

	//////////////////////////////////////////////////////////////////////////
	// Tags

public:
	/** Add tag to this request */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility")
	void AddTag(FName Tag);

	/** 
	 * Remove tag from this request 
	 *
	 * @return Number of removed elements 
	 */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility")
	int32 RemoveTag(FName Tag);

	/** See if this request contains the supplied tag */
	UFUNCTION(BlueprintCallable, Category = "SIOJ|Utility")
	bool HasTag(FName Tag) const;

protected:
	/** Array of tags that can be used for grouping and categorizing */
	TArray<FName> Tags;


	//////////////////////////////////////////////////////////////////////////
	// Data

public:
	/** Request response stored as a string */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SIOJ|Response")
	FString ResponseContent;

	/** Is the response valid JSON? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SIOJ|Response")
	bool bIsValidJsonResponse;

	/** If this is true it will call back on the binary callback instead of json */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SIOJ|Response")
	bool bShouldHaveBinaryResponse;

	TFunction<void(TArray<uint8>&)> OnProcessURLCompleteCallback;

	TArray<uint8> ResultBinaryData;

protected:
	/** Latent action helper */
	FSIOJLatentAction<USIOJsonObject*>* ContinueAction;

	/** Internal request data stored as JSON */
	UPROPERTY()
	USIOJsonObject* RequestJsonObj;

	UPROPERTY()
	TArray<uint8> RequestBytes;

	UPROPERTY()
	FString BinaryContentType;

	/** Response data stored as JSON */
	UPROPERTY()
	USIOJsonObject* ResponseJsonObj;

	/** Verb for making request (GET,POST,etc) */
	ESIORequestVerb RequestVerb;

	/** Content type to be applied for request */
	ESIORequestContentType RequestContentType;

	/** Mapping of header section to values. Used to generate final header string for request */
	TMap<FString, FString> RequestHeaders;

	/** Cached key/value header pairs. Parsed once request completes */
	TMap<FString, FString> ResponseHeaders;

	/** Http Response code */
	int32 ResponseCode;

	/** Custom verb that will be used with RequestContentType == CUSTOM */
	FString CustomVerb;

	/** Request we're currently processing */
	FHttpRequestRef HttpRequest = FHttpModule::Get().CreateRequest();

};
