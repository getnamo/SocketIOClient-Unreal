// Modifications Copyright 2018-current Getnamo. All Rights Reserved


// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJRequestJSON.h"
#include "ISIOJson.h"
#include "SIOJLibrary.h"
#include "SIOJsonValue.h"
#include "SIOJsonObject.h"

template <class T> void FSIOJLatentAction<T>::Cancel()
{
	UObject *Obj = Request.Get();
	if (Obj != nullptr)
	{
		((USIOJRequestJSON*)Obj)->Cancel();
	}
}

USIOJRequestJSON::USIOJRequestJSON(const class FObjectInitializer& PCIP)
  : Super(PCIP),
    BinaryContentType(TEXT("application/octet-stream"))
{
	RequestVerb = ESIORequestVerb::GET;
	RequestContentType = ESIORequestContentType::x_www_form_urlencoded_url;
	bShouldHaveBinaryResponse = false;
	OnProcessURLCompleteCallback = nullptr;

	ResetData();
}

USIOJRequestJSON* USIOJRequestJSON::ConstructRequest(UObject* WorldContextObject)
{
	return NewObject<USIOJRequestJSON>();
}

USIOJRequestJSON* USIOJRequestJSON::ConstructRequestExt(
	UObject* WorldContextObject, 
	ESIORequestVerb Verb, 
	ESIORequestContentType ContentType)
{
	USIOJRequestJSON* Request = ConstructRequest(WorldContextObject);

	Request->SetVerb(Verb);
	Request->SetContentType(ContentType);

	return Request;
}

void USIOJRequestJSON::SetVerb(ESIORequestVerb Verb)
{
	RequestVerb = Verb;
}

void USIOJRequestJSON::SetCustomVerb(FString Verb)
{
	CustomVerb = Verb;
}

void USIOJRequestJSON::SetContentType(ESIORequestContentType ContentType)
{
	RequestContentType = ContentType;
}

void USIOJRequestJSON::SetBinaryContentType(const FString &ContentType)
{
	BinaryContentType = ContentType;
}

void USIOJRequestJSON::SetBinaryRequestContent(const TArray<uint8> &Bytes)
{
	RequestBytes = Bytes;
}

void USIOJRequestJSON::SetHeader(const FString& HeaderName, const FString& HeaderValue)
{
	RequestHeaders.Add(HeaderName, HeaderValue);
}


//////////////////////////////////////////////////////////////////////////
// Destruction and reset

void USIOJRequestJSON::ResetData()
{
	ResetRequestData();
	ResetResponseData();
}

void USIOJRequestJSON::ResetRequestData()
{
	if (RequestJsonObj != nullptr)
	{
		RequestJsonObj->Reset();
	}
	else
	{
		RequestJsonObj = NewObject<USIOJsonObject>();
	}

	HttpRequest = FHttpModule::Get().CreateRequest();
}

void USIOJRequestJSON::ResetResponseData()
{
	if (ResponseJsonObj != nullptr)
	{
		ResponseJsonObj->Reset();
	}
	else
	{
		ResponseJsonObj = NewObject<USIOJsonObject>();
	}

	ResponseHeaders.Empty();
	ResponseCode = -1;

	bIsValidJsonResponse = false;
}

void USIOJRequestJSON::Cancel()
{
	ContinueAction = nullptr;

	ResetResponseData();
}


//////////////////////////////////////////////////////////////////////////
// JSON data accessors

USIOJsonObject* USIOJRequestJSON::GetRequestObject()
{
	return RequestJsonObj;
}

void USIOJRequestJSON::SetRequestObject(USIOJsonObject* JsonObject)
{
	RequestJsonObj = JsonObject;
}

USIOJsonObject* USIOJRequestJSON::GetResponseObject()
{
	return ResponseJsonObj;
}

void USIOJRequestJSON::SetResponseObject(USIOJsonObject* JsonObject)
{
	ResponseJsonObj = JsonObject;
}


///////////////////////////////////////////////////////////////////////////
// Response data access

FString USIOJRequestJSON::GetURL()
{
	return HttpRequest->GetURL();
}

ESIORequestStatus USIOJRequestJSON::GetStatus()
{
	return ESIORequestStatus((uint8)HttpRequest->GetStatus());
}

int32 USIOJRequestJSON::GetResponseCode()
{
	return ResponseCode;
}

FString USIOJRequestJSON::GetResponseHeader(const FString HeaderName)
{
	FString Result;

	FString* Header = ResponseHeaders.Find(HeaderName);
	if (Header != nullptr)
	{
		Result = *Header;
	}

	return Result;
}

TArray<FString> USIOJRequestJSON::GetAllResponseHeaders()
{
	TArray<FString> Result;
	for (TMap<FString, FString>::TConstIterator It(ResponseHeaders); It; ++It)
	{
		Result.Add(It.Key() + TEXT(": ") + It.Value());
	}
	return Result;
}


//////////////////////////////////////////////////////////////////////////
// URL processing

void USIOJRequestJSON::ProcessURL(const FString& Url)
{
	HttpRequest->SetURL(Url);

	ProcessRequest();
}

void USIOJRequestJSON::ApplyURL(const FString& Url, USIOJsonObject *&Result, UObject* WorldContextObject, FLatentActionInfo LatentInfo)
{
	HttpRequest->SetURL(Url);

	// Prepare latent action
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FSIOJLatentAction<USIOJsonObject*> *Kont = LatentActionManager.FindExistingAction<FSIOJLatentAction<USIOJsonObject*>>(LatentInfo.CallbackTarget, LatentInfo.UUID);


		if (Kont != nullptr)
		{
			Kont->Cancel();
			LatentActionManager.RemoveActionsForObject(LatentInfo.CallbackTarget);
		}

		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, ContinueAction = new FSIOJLatentAction<USIOJsonObject*>(this, Result, LatentInfo));
	}

	ProcessRequest();
}

void USIOJRequestJSON::ProcessRequest()
{
	// Set verb
	switch (RequestVerb)
	{
	case ESIORequestVerb::GET:
		HttpRequest->SetVerb(TEXT("GET"));
		break;

	case ESIORequestVerb::POST:
		HttpRequest->SetVerb(TEXT("POST"));
		break;

	case ESIORequestVerb::PUT:
		HttpRequest->SetVerb(TEXT("PUT"));
		break;
			
	case ESIORequestVerb::DEL:
		HttpRequest->SetVerb(TEXT("DELETE"));
		break;

	case ESIORequestVerb::CUSTOM:
		HttpRequest->SetVerb(CustomVerb);
		break;

	default:
		break;
	}

	// Set content-type
	switch (RequestContentType)
	{
	case ESIORequestContentType::x_www_form_urlencoded_url:
	{
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

		FString UrlParams = "";
		uint16 ParamIdx = 0;

		// Loop through all the values and prepare additional url part
		for (auto RequestIt = RequestJsonObj->GetRootObject()->Values.CreateIterator(); RequestIt; ++RequestIt)
		{
			FString Key = RequestIt.Key();
			FString Value = RequestIt.Value().Get()->AsString();

			if (!Key.IsEmpty() && !Value.IsEmpty())
			{
				UrlParams += ParamIdx == 0 ? "?" : "&";
				UrlParams += USIOJLibrary::PercentEncode(Key) + "=" + USIOJLibrary::PercentEncode(Value);
			}

			ParamIdx++;
		}

		// Apply params
		HttpRequest->SetURL(HttpRequest->GetURL() + UrlParams);

		UE_LOG(LogSIOJ, Log, TEXT("Request (urlencoded): %s %s %s"), *HttpRequest->GetVerb(), *HttpRequest->GetURL(), *UrlParams);

		break;
	}
	case ESIORequestContentType::x_www_form_urlencoded_body:
	{
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

		FString UrlParams = "";
		uint16 ParamIdx = 0;

		// Loop through all the values and prepare additional url part
		for (auto RequestIt = RequestJsonObj->GetRootObject()->Values.CreateIterator(); RequestIt; ++RequestIt)
		{
			FString Key = RequestIt.Key();
			FString Value = RequestIt.Value().Get()->AsString();

			if (!Key.IsEmpty() && !Value.IsEmpty())
			{
				UrlParams += ParamIdx == 0 ? "" : "&";
				UrlParams += USIOJLibrary::PercentEncode(Key) + "=" + USIOJLibrary::PercentEncode(Value);
			}

			ParamIdx++;
		}

		// Apply params
		HttpRequest->SetContentAsString(UrlParams);

		UE_LOG(LogSIOJ, Log, TEXT("Request (url body): %s %s %s"), *HttpRequest->GetVerb(), *HttpRequest->GetURL(), *UrlParams);

		break;
	}
	case ESIORequestContentType::binary:
	{
		HttpRequest->SetHeader(TEXT("Content-Type"), BinaryContentType);
		HttpRequest->SetContent(RequestBytes);

		UE_LOG(LogSIOJ, Log, TEXT("Request (binary): %s %s"), *HttpRequest->GetVerb(), *HttpRequest->GetURL());

		break;
	}
	case ESIORequestContentType::json:
	{
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

		// Serialize data to json string
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(RequestJsonObj->GetRootObject().ToSharedRef(), Writer);

		// Set Json content
		HttpRequest->SetContentAsString(OutputString);

		UE_LOG(LogSIOJ, Log, TEXT("Request (json): %s %s %s"), *HttpRequest->GetVerb(), *HttpRequest->GetURL(), *OutputString);

		break;
	}

	default:
		break;
	}

	// Apply additional headers
	for (TMap<FString, FString>::TConstIterator It(RequestHeaders); It; ++It)
	{
		HttpRequest->SetHeader(It.Key(), It.Value());
	}
	
	// Bind event
	if (bShouldHaveBinaryResponse)
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &USIOJRequestJSON::OnProcessRequestCompleteBinaryResult);
	}
	else
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &USIOJRequestJSON::OnProcessRequestComplete);
	}

	// Execute the request
	HttpRequest->ProcessRequest();
}


//////////////////////////////////////////////////////////////////////////
// Request callbacks

void USIOJRequestJSON::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Be sure that we have no data from previous response
	ResetResponseData();

	// Check we have a response and save response code as int32
	if(Response.IsValid())
	{
		ResponseCode = Response->GetResponseCode();
	}

	// Check we have result to process futher
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogSIOJ, Error, TEXT("Request failed (%d): %s"), ResponseCode, *Request->GetURL());

		// Broadcast the result event
		OnRequestFail.Broadcast(this);
		OnStaticRequestFail.Broadcast(this);

		return;
	}

	// Save response data as a string
	ResponseContent = Response->GetContentAsString();

	// Log response state
	UE_LOG(LogSIOJ, Log, TEXT("Response (%d): %s"), ResponseCode, *ResponseContent);

	// Process response headers
	TArray<FString> Headers = Response->GetAllHeaders();
	for (FString Header : Headers)
	{
		FString Key;
		FString Value;
		if (Header.Split(TEXT(": "), &Key, &Value))
		{
			ResponseHeaders.Add(Key, Value);
		}
	}

	// Try to deserialize data to JSON
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseContent);
	FJsonSerializer::Deserialize(JsonReader, ResponseJsonObj->GetRootObject());

	// Decide whether the request was successful
	bIsValidJsonResponse = bWasSuccessful && ResponseJsonObj->GetRootObject().IsValid();

	// Log errors
	if (!bIsValidJsonResponse)
	{
		if (!ResponseJsonObj->GetRootObject().IsValid())
		{
			// As we assume it's recommended way to use current class, but not the only one,
			// it will be the warning instead of error
			UE_LOG(LogSIOJ, Warning, TEXT("JSON could not be decoded!"));
		}
	}

	// Broadcast the result event
	OnRequestComplete.Broadcast(this);
	OnStaticRequestComplete.Broadcast(this);

	// Finish the latent action
	if (ContinueAction)
	{
          FSIOJLatentAction<USIOJsonObject*> *K = ContinueAction;
          ContinueAction = nullptr;

          K->Call(ResponseJsonObj);
	}
}


void USIOJRequestJSON::OnProcessRequestCompleteBinaryResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Be sure that we have no data from previous response
	ResetResponseData();

	// Check we have a response and save response code as int32
	if (Response.IsValid())
	{
		ResponseCode = Response->GetResponseCode();
	}

	// Check we have result to process futher
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogSIOJ, Error, TEXT("Request failed (%d): %s"), ResponseCode, *Request->GetURL());

		// Broadcast the result event
		OnRequestFail.Broadcast(this);
		OnStaticRequestFail.Broadcast(this);

		return;
	}

	ResultBinaryData = Response->GetContent();

	// Broadcast the result event
	OnRequestComplete.Broadcast(this);
	OnStaticRequestComplete.Broadcast(this);

	if (OnProcessURLCompleteCallback)
	{
		OnProcessURLCompleteCallback(ResultBinaryData);
	}
}

//////////////////////////////////////////////////////////////////////////
// Tags

void USIOJRequestJSON::AddTag(FName Tag)
{
	if (Tag != NAME_None)
	{
		Tags.AddUnique(Tag);
	}
}

int32 USIOJRequestJSON::RemoveTag(FName Tag)
{
	return Tags.Remove(Tag);
}

bool USIOJRequestJSON::HasTag(FName Tag) const
{
	return (Tag != NAME_None) && Tags.Contains(Tag);
}
