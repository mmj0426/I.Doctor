// Fill out your copyright notice in the Description page of Project Settings.


#include "IDAnimInstance.h"
#include "IDCharacter.h"

UIDAnimInstance::UIDAnimInstance()
{
	//����  Pawn Speed �ʱ�ȭ
	CurrentPawnSpeed = 0.0f;
	isInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		PICKUP_MONTAGE(TEXT("/Game/Animations/AnimMontage_Pickup.AnimMontage_Pickup"));
	if (PICKUP_MONTAGE.Succeeded())
	{
		PickupMontage = PICKUP_MONTAGE.Object;
	}
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
			isInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UIDAnimInstance::PlayPickupMontage()
{
	Montage_Play(PickupMontage, 1.0f);
}

void UIDAnimInstance::AnimNotify_PickupCheck()
{
	OnPickupCheck.Broadcast();
}