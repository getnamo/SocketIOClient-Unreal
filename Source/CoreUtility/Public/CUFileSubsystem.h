#pragma once

#include "Subsystems/EngineSubsystem.h"
#include "CUFileSubsystem.generated.h"

UCLASS(ClassGroup = "WRCoreAI")
class COREUTILITY_API UCUFileSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	
	virtual	void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};