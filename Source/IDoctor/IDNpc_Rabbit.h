// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "GameFramework/Character.h"
#include "IDNpc_Rabbit.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnOverlapBeginDelegate);

UCLASS()
class IDOCTOR_API AIDNpc_Rabbit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIDNpc_Rabbit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public : 
	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent* Sphere;

	//Interaction
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FOnOverlapBeginDelegate OnOverlap;
};
