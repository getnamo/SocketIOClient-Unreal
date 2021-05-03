// Copyright 2019-current Getnamo. All Rights Reserved

#include "SocketIOFunctionLibrary.h"
#include "CULambdaRunnable.h"
#include "Engine/Engine.h"

USocketIOClientComponent* USocketIOFunctionLibrary::ConstructSocketIOComponent(UObject* WorldContextObject)
{
	USocketIOClientComponent* SpawnedComponent = NewObject<USocketIOClientComponent>(WorldContextObject, TEXT("SocketIOClientComponent"));

	if (SpawnedComponent)
	{
		//Check if we got spawned by an object with an owner context (e.g. game mode) or not (e.g. game instance)
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
		AActor* MyOwner = SpawnedComponent->GetOwner();
		bool bOwnerHasValidWorld = (MyOwner ? MyOwner->GetWorld() : nullptr) != nullptr;

		SpawnedComponent->StaticInitialization(WorldContextObject, bOwnerHasValidWorld);

		//Register component if it was spawned by world owning context object, e.g. game mode
		if (bOwnerHasValidWorld)
		{
			//Delay by 1 tick so that we can adjust bShouldAutoConnect/etc
			FCULambdaRunnable::RunShortLambdaOnGameThread([SpawnedComponent]()
			{
				if (SpawnedComponent->IsValidLowLevel())
				{
					SpawnedComponent->RegisterComponent();
				}
			});
		}

		//Otherwise we don't need to register our component for the networking logic to work.
	}
	return SpawnedComponent;
}

namespace 
{
	struct FDynamicArgs
	{
		void* Arg01 = nullptr;
	};
}

bool USocketIOFunctionLibrary::CallFunctionByName(const FString& FunctionName, UObject* Target, UObject* WorldContextObject, USIOJsonValue* Param)
{
	if (Target == nullptr)
	{
		Target = WorldContextObject;
	}

	UFunction* Function = Target->FindFunction(FName(*FunctionName));
	if (nullptr == Function)
	{
		UE_LOG(SocketIO, Warning, TEXT("CallFunctionByName: Function not found '%s'"), *FunctionName);
		return false;
	}

	//Check function signature
	TFieldIterator<FProperty> Iterator(Function);

	TArray<FProperty*> Properties;
	while (Iterator && (Iterator->PropertyFlags & CPF_Parm))
	{
		FProperty* Prop = *Iterator;
		Properties.Add(Prop);
		++Iterator;
	}

	//bool bTargetParamsNonZero = Properties.Num() > 0;
	bool bTargetParamsZero = Properties.Num() == 0;
	bool bNullParamPassed = Param->IsNull();

	//UE_LOG(SocketIO, Warning, TEXT("CallFunctionByName: Target %d, %s"), Target, *FunctionName);

	if (bTargetParamsZero && bNullParamPassed)
	{
		Target->ProcessEvent(Function, nullptr);
	}
	
	else{

		//function has too few params
		if (bTargetParamsZero)
		{
			UE_LOG(SocketIO, Warning, TEXT("CallFunctionByName: Function '%s' has too few parameters, callback parameter ignored : <%s>"), *FunctionName, *Param->EncodeJson());
			Target->ProcessEvent(Function, nullptr);
			return true;
		}

		
		//create the container
		FDynamicArgs Args = FDynamicArgs();

		//add the full response array as second param
		const FString& FirstParam = Properties[0]->GetCPPType();

		FStructProperty* StructProperty = CastField<FStructProperty>(Properties[0]);
		if (StructProperty)
		{
			//StructProperty->getcon
		}

		//Is first param...
		//SIOJsonValue?
		if (FirstParam.Equals("USIOJsonValue*"))
		{
			Args.Arg01 = Param;
			Target->ProcessEvent(Function, &Args);
			return true;
		}
		//SIOJsonObject?
		else if (FirstParam.Equals("USIOJsonObject*"))
		{	
			//convenience wrapper, response is a single object
			Args.Arg01 = Param->AsObject();
			Target->ProcessEvent(Function, &Args);
			return true;
		}
		//String?
		else if (FirstParam.Equals("FString"))
		{
			FString	StringValue = Param->AsString();
			
			Target->ProcessEvent(Function, &StringValue);
			return true;
		}
		//Float?
		else if (FirstParam.Equals("float"))
		{
			float NumberValue = (float)Param->AsNumber();
			Target->ProcessEvent(Function, &NumberValue);
			return true;
		}
		//Int?
		else if (FirstParam.Equals("int32"))
		{
			int NumberValue = (int)Param->AsNumber();
			Target->ProcessEvent(Function, &NumberValue);
			return true;
		}
		//bool?
		else if (FirstParam.Equals("bool"))
		{
			bool BoolValue = Param->AsBool();
			Target->ProcessEvent(Function, &BoolValue);
			return true;
		}
		//array?
		else if (FirstParam.Equals("TArray"))
		{
			FArrayProperty* ArrayProp = CastField<FArrayProperty>(Properties[0]);

			FString Inner;
			ArrayProp->GetCPPMacroType(Inner);

			//byte array is the only supported version
			if (Inner.Equals("uint8"))
			{
				TArray<uint8> Bytes = Param->AsBinary();
				Target->ProcessEvent(Function, &Bytes);
				return true;
			}
		}
	}
	return false;
}
