// Modifications Copyright 2018-current Getnamo. All Rights Reserved


// Copyright 2016 Vladimir Alyamkin. All Rights Reserved.

#include "SIOJLibrary.h"
#include "ISIOJson.h"
#include "Json/Public/Dom/JsonObject.h"
#include "Json/Public/Dom/JsonValue.h"
#include "SIOJsonValue.h"
#include "SIOJsonObject.h"
#include "Misc/Base64.h"
#include "Engine/Engine.h"

//////////////////////////////////////////////////////////////////////////
// Helpers

FString USIOJLibrary::PercentEncode(const FString& Source)
{
	FString OutText = Source;

	OutText = OutText.Replace(TEXT(" "), TEXT("%20"));
	OutText = OutText.Replace(TEXT("!"), TEXT("%21"));
	OutText = OutText.Replace(TEXT("\""), TEXT("%22"));
	OutText = OutText.Replace(TEXT("#"), TEXT("%23"));
	OutText = OutText.Replace(TEXT("$"), TEXT("%24"));
	OutText = OutText.Replace(TEXT("&"), TEXT("%26"));
	OutText = OutText.Replace(TEXT("'"), TEXT("%27"));
	OutText = OutText.Replace(TEXT("("), TEXT("%28"));
	OutText = OutText.Replace(TEXT(")"), TEXT("%29"));
	OutText = OutText.Replace(TEXT("*"), TEXT("%2A"));
	OutText = OutText.Replace(TEXT("+"), TEXT("%2B"));
	OutText = OutText.Replace(TEXT(","), TEXT("%2C"));
	OutText = OutText.Replace(TEXT("/"), TEXT("%2F"));
	OutText = OutText.Replace(TEXT(":"), TEXT("%3A"));
	OutText = OutText.Replace(TEXT(";"), TEXT("%3B"));
	OutText = OutText.Replace(TEXT("="), TEXT("%3D"));
	OutText = OutText.Replace(TEXT("?"), TEXT("%3F"));
	OutText = OutText.Replace(TEXT("@"), TEXT("%40"));
	OutText = OutText.Replace(TEXT("["), TEXT("%5B"));
	OutText = OutText.Replace(TEXT("]"), TEXT("%5D"));
	OutText = OutText.Replace(TEXT("{"), TEXT("%7B"));
	OutText = OutText.Replace(TEXT("}"), TEXT("%7D"));

	return OutText;
}

FString USIOJLibrary::Base64Encode(const FString& Source)
{
	return FBase64::Encode(Source);
}

FString USIOJLibrary::Base64EncodeBytes(const TArray<uint8>& Source)
{
	return FBase64::Encode(Source);
}

bool USIOJLibrary::Base64Decode(const FString& Source, FString& Dest)
{
	return FBase64::Decode(Source, Dest);
}


bool USIOJLibrary::Base64DecodeBytes(const FString& Source, TArray<uint8>& Dest)
{
	return FBase64::Decode(Source, Dest);
}

bool USIOJLibrary::StringToJsonValueArray(const FString& JsonString, TArray<USIOJsonValue*>& OutJsonValueArray)
{
	TArray < TSharedPtr<FJsonValue>> RawJsonValueArray;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(*JsonString);
	FJsonSerializer::Deserialize(Reader, RawJsonValueArray);

	for (auto Value : RawJsonValueArray)
	{
		auto SJsonValue = NewObject<USIOJsonValue>();
		SJsonValue->SetRootValue(Value);
		OutJsonValueArray.Add(SJsonValue);
	}

	return OutJsonValueArray.Num() > 0;
}

//////////////////////////////////////////////////////////////////////////
// Easy URL processing

TMap<USIOJRequestJSON*, FSIOJCallResponse> USIOJLibrary::RequestMap;


FString USIOJLibrary::Conv_SIOJsonObjectToString(USIOJsonObject* InObject)
{
	if(InObject)
	{
		return InObject->EncodeJson();
	}

	return "";
}


USIOJsonObject* USIOJLibrary::Conv_JsonValueToJsonObject(class USIOJsonValue* InValue)
{
	if(InValue)
	{
		return InValue->AsObject();
	}

	return nullptr;
}

USIOJsonValue* USIOJLibrary::Conv_ArrayToJsonValue(const TArray<USIOJsonValue*>& InArray)
{
	return USIOJsonValue::ConstructJsonValueArray(nullptr, InArray);
}


USIOJsonValue* USIOJLibrary::Conv_JsonObjectToJsonValue(USIOJsonObject* InObject)
{
	return USIOJsonValue::ConstructJsonValueObject(InObject, nullptr);
}


USIOJsonValue* USIOJLibrary::Conv_BytesToJsonValue(const TArray<uint8>& InBytes)
{
	return USIOJsonValue::ConstructJsonValueBinary(nullptr, InBytes);
}


USIOJsonValue* USIOJLibrary::Conv_StringToJsonValue(const FString& InString)
{
	return USIOJsonValue::ConstructJsonValueString(nullptr, InString);
}


USIOJsonValue* USIOJLibrary::Conv_IntToJsonValue(int32 InInt)
{
	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueNumber(InInt));

	USIOJsonValue* NewValue = NewObject<USIOJsonValue>();
	NewValue->SetRootValue(NewVal);

	return NewValue;
}

USIOJsonValue* USIOJLibrary::Conv_FloatToJsonValue(float InFloat)
{
	return USIOJsonValue::ConstructJsonValueNumber(nullptr, InFloat);
}


USIOJsonValue* USIOJLibrary::Conv_BoolToJsonValue(bool InBool)
{
	return USIOJsonValue::ConstructJsonValueBool(nullptr, InBool);
}


FString USIOJLibrary::Conv_SIOJsonValueToString(class USIOJsonValue* InValue)
{
	if (InValue)
	{
		return InValue->AsString();
	}

	return TEXT("");
}

int32 USIOJLibrary::Conv_JsonValueToInt(USIOJsonValue* InValue)
{
	if(InValue)
	{
		return (int32)InValue->AsNumber();
	}

	return 0;
}


float USIOJLibrary::Conv_JsonValueToFloat(USIOJsonValue* InValue)
{
	if (InValue)
	{
		return InValue->AsNumber();
	}

	return 0.f;
}


bool USIOJLibrary::Conv_JsonValueToBool(USIOJsonValue* InValue)
{
	if (InValue)
	{
		return InValue->AsBool();
	}

	return false;
}


TArray<uint8> USIOJLibrary::Conv_JsonValueToBytes(USIOJsonValue* InValue)
{
	if (InValue)
	{
		return InValue->AsBinary();
	}

	return TArray<uint8>();
}

void USIOJLibrary::CallURL(UObject* WorldContextObject, const FString& URL, ESIORequestVerb Verb, ESIORequestContentType ContentType, USIOJsonObject* SIOJJson, const FSIOJCallDelegate& Callback)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr)
	{
		UE_LOG(LogSIOJ, Error, TEXT("USIOJLibrary: Wrong world context"))
		return;
	}

	// Check we have valid data json
	if (SIOJJson == nullptr)
	{
		SIOJJson = USIOJsonObject::ConstructJsonObject(WorldContextObject);
	}
	
	USIOJRequestJSON* Request = NewObject<USIOJRequestJSON>();
	
	Request->SetVerb(Verb);
	Request->SetContentType(ContentType);
	Request->SetRequestObject(SIOJJson);
	
	FSIOJCallResponse Response;
	Response.Request = Request;
	Response.WorldContextObject = WorldContextObject;
	Response.Callback = Callback;
	
	Response.CompleteDelegateHandle = Request->OnStaticRequestComplete.AddStatic(&USIOJLibrary::OnCallComplete);
	Response.FailDelegateHandle = Request->OnStaticRequestFail.AddStatic(&USIOJLibrary::OnCallComplete);
	
	RequestMap.Add(Request, Response);
	
	Request->ResetResponseData();
	Request->ProcessURL(URL);
}

void USIOJLibrary::GetURLBinary(UObject* WorldContextObject, const FString& URL, ESIORequestVerb Verb, ESIORequestContentType ContentType, TArray<uint8>& OutResultData, struct FLatentActionInfo LatentInfo)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr)
	{
		UE_LOG(LogSIOJ, Error, TEXT("USIOJLibrary: Wrong world context"))
			return;
	}

	USIOJRequestJSON* Request = NewObject<USIOJRequestJSON>();
	FCULatentAction *LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, WorldContextObject);

	Request->SetVerb(Verb);
	Request->SetContentType(ContentType);
	Request->bShouldHaveBinaryResponse = true;
	Request->OnProcessURLCompleteCallback = [LatentAction, &OutResultData](TArray<uint8>& ResultData)
	{
		if (LatentAction)
		{
			OutResultData = ResultData;
			LatentAction->Call();	//resume the latent action
		}
	};

	Request->ResetResponseData();
	Request->ProcessURL(URL);

	
}

void USIOJLibrary::OnCallComplete(USIOJRequestJSON* Request)
{
	if (!RequestMap.Contains(Request))
	{
		return;
	}
	
	FSIOJCallResponse* Response = RequestMap.Find(Request);
	
	Request->OnStaticRequestComplete.Remove(Response->CompleteDelegateHandle);
	Request->OnStaticRequestFail.Remove(Response->FailDelegateHandle);
	
	Response->Callback.ExecuteIfBound(Request);
	
	Response->WorldContextObject = nullptr;
	Response->Request = nullptr;
	RequestMap.Remove(Request);
}
