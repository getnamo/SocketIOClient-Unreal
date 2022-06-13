// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "Dom/JsonValue.h"
#include "Dom/JsonObject.h"
#include "sio_client.h"
#include "SIOJsonValue.h"
#include "SIOMessageConvert.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(SocketIO, Log, All);

/** 
* All params defining a connection URL.
*/
USTRUCT(BlueprintType)
struct SOCKETIOCLIENT_API FSIOConnectParams
{
	GENERATED_USTRUCT_BODY();

	/** Default connection address string in form e.g. http://localhost:80. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SocketIOConnectionParams)
	FString AddressAndPort;

	/** A map of query parameters to be added to connection url*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SocketIOConnectionParams)
	TMap<FString, FString> Query;

	/** A map of headers to be added to connection url*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SocketIOConnectionParams)
	TMap<FString, FString> Headers;
	
	/** Optional authorization JSON to send to the server upon initial connection*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SocketIOConnectionParams)
	FString AuthToken;

	/** Optional path part of URL string. Default is 'socket.io'*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SocketIOConnectionParams)
	FString Path;

	FSIOConnectParams()
	{
		AddressAndPort = TEXT("http://localhost:3000");
		Path = TEXT("socket.io");
		AuthToken = TEXT("");
	}
};

/**
 * Static Conversion Utilities
 */
UCLASS()
class SOCKETIOCLIENT_API USIOMessageConvert : public UObject
{
	GENERATED_BODY()
public:

	//To from:

	//sio::message <-> FJsonValue
	static TSharedPtr<FJsonValue> ToJsonValue(const sio::message::ptr& Message);
	static sio::message::ptr ToSIOMessage(const TSharedPtr<FJsonValue>& JsonValue);

	//std::string <-> FString
	static std::string StdString(FString UEString);
	static FString FStringFromStd(std::string StdString);

	static std::map<std::string, std::string> JsonObjectToStdStringMap(TSharedPtr<FJsonObject> InObject);
	static TMap<FString, FString> JsonObjectToFStringMap(TSharedPtr<FJsonObject> InObject);
	static std::map<std::string, std::string> FStringMapToStdStringMap(const TMap<FString, FString>& InMap);
}; 
