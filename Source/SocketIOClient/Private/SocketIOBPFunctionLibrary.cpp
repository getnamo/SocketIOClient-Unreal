#pragma once

#include "SocketIOClientPrivatePCH.h"
#include "SocketIOBPFunctionLibrary.h"
#include "sio_client.h"
#include <string>

sio::client h;

USocketIOBPFunctionLibrary::USocketIOBPFunctionLibrary(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{
}

std::string StdString(FString UEString)
{
	return std::string(TCHAR_TO_UTF8(*UEString));
}

void USocketIOBPFunctionLibrary::Emit(FString Name, FString Action)
{
	h.socket()->emit(StdString(Name), StdString(Action));
	UE_LOG(LogTemp, Log, TEXT("Emit %s with %s"), *Name, *Action);
}

void USocketIOBPFunctionLibrary::Connect(FString AddressAndPort)
{
	if (!AddressAndPort.IsEmpty())
	{
		h.connect(StdString(AddressAndPort));
	}
	else
	{
		h.connect("http://localhost:3000");
	}
	UE_LOG(LogTemp, Log, TEXT("Connecting to %s"), *AddressAndPort);
}