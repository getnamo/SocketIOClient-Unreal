// Copyright 2018-current Getnamo. All Rights Reserved


#include "SIOMessageConvert.h"
#include "SIOJsonValue.h"

DEFINE_LOG_CATEGORY(SocketIO);

TSharedPtr<FJsonValue> USIOMessageConvert::ToJsonValue(const sio::message::ptr& Message)
{
	if (Message == nullptr)
	{
		return MakeShareable(new FJsonValueNull());
	}

	auto flag = Message->get_flag();

	if (flag == sio::message::flag_integer)
	{
		return MakeShareable(new FJsonValueNumber(Message->get_int()));
	}
	else if (flag == sio::message::flag_double)
	{
		return MakeShareable(new FJsonValueNumber(Message->get_double()));
	}
	else if (flag == sio::message::flag_string)
	{
		return MakeShareable(new FJsonValueString(FStringFromStd(Message->get_string())));
	}
	else if (flag == sio::message::flag_binary)
	{
		//convert sio buffer ptr into the array
		TArray<uint8> Buffer;
		Buffer.Append((uint8*)(Message->get_binary()->data()), Message->get_binary()->size());
		
		return MakeShareable(new FJsonValueBinary(Buffer));
	}
	else if (flag == sio::message::flag_array)
	{
		auto MessageVector = Message->get_vector();
		TArray< TSharedPtr<FJsonValue> > InArray;

		InArray.Reset(MessageVector.size());

		for (auto ItemMessage : MessageVector)
		{
			InArray.Add(ToJsonValue(ItemMessage));
		}
		
		return MakeShareable(new FJsonValueArray(InArray));
	}
	else if (flag == sio::message::flag_object)
	{
		auto  MessageMap = Message->get_map();
		TSharedPtr<FJsonObject> InObject = MakeShareable(new FJsonObject());

		for (auto MapPair : MessageMap)
		{
			InObject->SetField(FStringFromStd(MapPair.first), ToJsonValue(MapPair.second));
		}

		return MakeShareable(new FJsonValueObject(InObject));
	}
	else if (flag == sio::message::flag_boolean)
	{
		return MakeShareable(new FJsonValueBoolean(Message->get_bool()));
	}
	else if (flag == sio::message::flag_null)
	{
		return MakeShareable(new FJsonValueNull());
	}
	else 
	{
		return MakeShareable(new FJsonValueNull());
	}
}



sio::message::ptr USIOMessageConvert::ToSIOMessage(const TSharedPtr<FJsonValue>& JsonValue)
{
	if (!JsonValue.IsValid())
	{
		return sio::null_message::create();
	}
	else if (JsonValue->Type == EJson::None)
	{
		return sio::null_message::create();
	}
	else if (JsonValue->Type == EJson::Null)
	{
		return sio::null_message::create();
	}
	else if (JsonValue->Type == EJson::String)
	{
		if (FJsonValueBinary::IsBinary(JsonValue))
		{
			const TArray<uint8> BinaryArray = FJsonValueBinary::AsBinary(JsonValue);
			if (BinaryArray.Num() == 0)
			{
				return sio::binary_message::create(std::make_shared<std::string>());
			}
			return sio::binary_message::create(std::make_shared<std::string>((char*)BinaryArray.GetData(), BinaryArray.Num()));
		}
		else
		{
			return sio::string_message::create(StdString(JsonValue->AsString()));
		}
	}
	else if (JsonValue->Type == EJson::Number)
	{
		return sio::double_message::create(JsonValue->AsNumber());
	}
	else if (JsonValue->Type == EJson::Boolean)
	{
		return sio::bool_message::create(JsonValue->AsBool());
	}
	else if (JsonValue->Type == EJson::Array)
	{
		auto ValueArray = JsonValue->AsArray();
		auto ArrayMessage = sio::array_message::create();

		for (auto ItemValue : ValueArray)
		{
			//must use get_vector() for each
			ArrayMessage->get_vector().push_back(ToSIOMessage(ItemValue));
		}

		return ArrayMessage;
	}
	else if (JsonValue->Type == EJson::Object)
	{
		const auto& ValueTmap = JsonValue->AsObject()->Values;

		auto ObjectMessage = sio::object_message::create();

		for (const auto& ItemPair : ValueTmap)
		{
			//important to use get_map() directly to insert the key in the correct map and not a pointer copy
			ObjectMessage->get_map()[StdString(FString(*ItemPair.Key))] = ToSIOMessage(ItemPair.Value);
		}

		return ObjectMessage;
	}
	else
	{
		return sio::null_message::create();
	}
}

//We assume utf8 in transport
std::string USIOMessageConvert::StdString(const FString& UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));
}

FString USIOMessageConvert::FStringFromStd(const std::string& StdString)
{
	return FString(UTF8_TO_TCHAR(StdString.c_str()));
}

std::map<std::string, std::string> USIOMessageConvert::JsonObjectToStdStringMap(TSharedPtr<FJsonObject> InObject)
{
	std::map<std::string, std::string> ParamMap;

	if (InObject.IsValid())
	{
		for (const auto& Pair : InObject->Values)
		{
			const TSharedPtr<FJsonValue>& Value = Pair.Value;

			//If it's a string value, add it to the std map
			if (Value->Type == EJson::String)
			{
				ParamMap[USIOMessageConvert::StdString(FString(*Pair.Key))] = USIOMessageConvert::StdString(Value->AsString());
			}
		}
	}

	return ParamMap;
}

TMap<FString, FString> USIOMessageConvert::JsonObjectToFStringMap(TSharedPtr<FJsonObject> InObject)
{
	TMap<FString, FString> ParamMap;

	if (InObject.IsValid())
	{
		for (const auto& Pair : InObject->Values)
		{
			const TSharedPtr<FJsonValue>& Value = Pair.Value;

			//If it's a string value, add it to the map
			if (Value->Type == EJson::String)
			{
				ParamMap.Add(FString(*Pair.Key), Value->AsString());
			}
		}
	}

	return ParamMap;
}

std::map<std::string, std::string> USIOMessageConvert::FStringMapToStdStringMap(const TMap<FString, FString>& InMap)
{
	std::map<std::string, std::string> ParamMap;

	for (const auto& Pair : InMap)
	{
		ParamMap[USIOMessageConvert::StdString(Pair.Key)] = USIOMessageConvert::StdString(Pair.Value);
	}

	return ParamMap;
}

sio::message::ptr USIOMessageConvert::ToSIOAuthMessage(const FString& AuthToken, const TMap<FString, FString>& ExtraAuth)
{
	sio::message::ptr AuthMessage = sio::object_message::create();
	if (!AuthToken.IsEmpty())
	{
		AuthMessage->get_map()["token"] = sio::string_message::create(StdString(AuthToken));
	}
	for (const TPair<FString, FString>& Pair : ExtraAuth)
	{
		AuthMessage->get_map()[StdString(Pair.Key)] = sio::string_message::create(StdString(Pair.Value));
	}
	return AuthMessage;
}
