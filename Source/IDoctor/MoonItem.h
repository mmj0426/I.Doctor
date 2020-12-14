// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "GameFramework/Actor.h"
#include "MoonItem.generated.h"

UCLASS()
class IDOCTOR_API AMoonItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoonItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public : 
	UPROPERTY(VisibleAnywhere, Category = Item)
		USphereComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Item)
		UStaticMeshComponent* Moon;

	UPROPERTY(VisibleAnywhere, Category = Item)
		UPointLightComponent* Light;

	//Interaction
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private : 

};
