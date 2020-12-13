// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "GameFramework/Actor.h"
#include "NextLevelVolume.generated.h"

UCLASS()
class IDOCTOR_API ANextLevelVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANextLevelVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private : 
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FName TransferLevelName;

	UPROPERTY()
		class UBoxComponent* TransferVolume;

};
