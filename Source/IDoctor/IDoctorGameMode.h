// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IDoctor.h"
#include "GameFramework/GameModeBase.h"
#include "IDoctorGameMode.generated.h"

UCLASS(minimalapi)
class AIDoctorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AIDoctorGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};



