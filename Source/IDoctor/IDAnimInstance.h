// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "Animation/AnimInstance.h"
#include "IDAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPickupCheckDelegate);

UCLASS()
class IDOCTOR_API UIDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public : 
	UIDAnimInstance();

	//AnimInstance¿« Tick
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void SetPawnSpeed(float NewPawnSpeed) { CurrentPawnSpeed = NewPawnSpeed; }

	//Pickup
	void PlayPickupMontage();

	FOnPickupCheckDelegate OnPickupCheck;

private : 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool isInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup, Meta = (AllowPrivateAccess = true))
		UAnimMontage* PickupMontage;

	UFUNCTION()
		void AnimNotify_PickupCheck();
};
