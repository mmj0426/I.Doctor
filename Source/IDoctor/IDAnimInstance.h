// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "Animation/AnimInstance.h"
#include "IDAnimInstance.generated.h"

UCLASS()
class IDOCTOR_API UIDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public : 
	UIDAnimInstance();

	//AnimInstance¿« Tick
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void SetPawnSpeed(float NewPawnSpeed) { CurrentPawnSpeed = NewPawnSpeed; }

private : 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;
};
