// Copyright Epic Games, Inc. All Rights Reserved.

#include "IDoctorGameMode.h"
#include "IDPawn.h"
#include "IDCharacter.h"
#include "IDPlayerController.h"

AIDoctorGameMode::AIDoctorGameMode()
{
	//DefaultPawnClass = AIDPawn::StaticClass();	
	//DefaultPawnClass = AIDCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter> PlayerCharacter(TEXT("/Game/Blueprints/Character/BP_IDCharacter.BP_IDCharacter_C"));
	DefaultPawnClass = PlayerCharacter.Class;

	PlayerControllerClass = AIDPlayerController::StaticClass();
}

void AIDoctorGameMode::PostLogin(APlayerController* NewPlayer)
{
	IDLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	IDLOG(Warning, TEXT("PostLogin End"));
}