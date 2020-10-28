// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "GameFramework/PlayerController.h"
#include "IDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class IDOCTOR_API AIDPlayerController : public APlayerController
{
	GENERATED_BODY()

public : 
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

protected :
	virtual void BeginPlay() override;
};
