// Fill out your copyright notice in the Description page of Project Settings.


#include "IDPawn.h"

// Sets default values
AIDPawn::AIDPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	//Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	//Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	//RootComponent = Capsule;
	//Mesh->SetupAttachment(Capsule);
	//SpringArm->SetupAttachment(Capsule);
	//Camera->SetupAttachment(SpringArm);

	////캡슐컴포넌트에 캐릭터 넣기(맞추기)
	//Capsule->SetCapsuleHalfHeight(40.0f);
	//Capsule->SetCapsuleRadius(2.0f);

	////IDLOG(Warning, TEXT("CapsuleRadius : %.3f",*Capsule->GetScaledCapsuleRadius()));
	////Mesh의 기준을 정중앙이 아닌 발바닥에 맞추기
	//Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -40.0f), FRotator(0.0f, -90.0f, 0.0f));
	////카메라 지지대 길이 : 400(4m), 컴포넌트의 y축 회전(Pitch, Yaw, Roll)
	//SpringArm->TargetArmLength = 400.0f;
	//SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh>
	//	SK_DEER(TEXT("/Game/CharacterAsset/Meshes/OneMeshCharacter/DeerSK.DeerSK"));
	//if (SK_DEER.Succeeded())
	//{
	//	Mesh->SetSkeletalMesh(SK_DEER.Object);
	//}

}

// Called when the game starts or when spawned
void AIDPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/CharacterAsset/Animations/Idle_NormalAnim.Idle_NormalAnim"));
	//if (AnimAsset != nullptr)
	//{
	//	Mesh->PlayAnimation(AnimAsset, true);
	//}
}

// Called every frame
void AIDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIDPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ID_S(Warning);
}

void AIDPawn::PossessedBy(AController* NewController)
{
	ID_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AIDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIDPawn::MoveForward(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AIDPawn::MoveRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

