// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Rabit.h"

// Sets default values
ANPC_Rabit::ANPC_Rabit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(RootComponent);

	Capsule->SetCapsuleHalfHeight(40.0f);
	Capsule->SetCapsuleRadius(20.0f);

	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -40.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_RABBIT((TEXT("/Game/CharacterAsset/CharacterSM/RabitSK.RabitSK")));
	if (SK_RABBIT.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_RABBIT.Object);
	}

}

// Called when the game starts or when spawned
void ANPC_Rabit::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/CharacterAsset/Animations/SleepingAnim.SleepingAnim"));
	if (AnimAsset != nullptr)
	{
		Mesh->PlayAnimation(AnimAsset, true);
	}
	
}

// Called every frame
void ANPC_Rabit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC_Rabit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

