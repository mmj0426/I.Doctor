// Fill out your copyright notice in the Description page of Project Settings.


#include "IDAnimInstance.h"

UIDAnimInstance::UIDAnimInstance()
{
	//����  Pawn Speed �ʱ�ȭ
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
}

void UIDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}

	}
}
