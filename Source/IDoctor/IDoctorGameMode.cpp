// Copyright Epic Games, Inc. All Rights Reserved.

#include "IDoctorGameMode.h"
#include "IDoctorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIDoctorGameMode::AIDoctorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
