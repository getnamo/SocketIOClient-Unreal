// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "sio_client.h"
#include "SocketIOClientComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIOCOnEventSignature, FString, Name, FString, Data);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOCKETIOCLIENT_API USocketIOClientComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USocketIOClientComponent();

	UPROPERTY(BlueprintAssignable, Category = "SocketIO Events")
	FSIOCOnEventSignature On;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category="SocketIO Functions")
	void Connect(FString AddressAndPort);

	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Emit(FString Name, FString Data);

	UFUNCTION(BlueprintCallable, Category = "SocketIO Functions")
	void Bind(FString Name);
	
protected:
	sio::client PrivateClient;
};
