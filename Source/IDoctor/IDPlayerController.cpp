// Fill out your copyright notice in the Description page of Project Settings.


#include "IDPlayerController.h"

void AIDPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ID_S(Warning);
}

void AIDPlayerController::OnPossess(APawn* aPawn)
{
	ID_S(Warning);
	Super::OnPossess(aPawn);
}

void AIDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}