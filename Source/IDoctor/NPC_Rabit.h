// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "GameFramework/Pawn.h"
#include "NPC_Rabit.generated.h"

UCLASS()
class IDOCTOR_API ANPC_Rabit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANPC_Rabit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public : 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	

	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMeshComponent* Mesh;

};
