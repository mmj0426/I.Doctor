// Fill out your copyright notice in the Description page of Project Settings.


#include "IDCharacter.h"
#include "IDAnimInstance.h"

// Sets default values
AIDCharacter::AIDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetCapsuleComponent()->SetCapsuleHalfHeight(40.0f);
	GetCapsuleComponent()->SetCapsuleRadius(20.0f);

	GetCharacterMovement()->JumpZVelocity = 400.0f;

	//�޽� �ʱⰪ ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -40.0f), FRotator(0.0f, 0.0f, 0.0f));
	
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 60.0f), FRotator(0.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_DEER(TEXT("/Game/CharacterAsset/Meshes/OneMeshCharacter/DeerSK.DeerSK"));
	if (SK_DEER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_DEER.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimBP_DEER(TEXT("/Game/Animations/AnimBP_Deer.AnimBP_Deer_C"));
	if (AnimBP_DEER.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBP_DEER.Class);
	}
}

// Called when the game starts or when spawned
void AIDCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AIDAnimInstance = Cast<UIDAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr != AIDAnimInstance)
	{
		AIDAnimInstance->SetPawnSpeed(GetVelocity().Size());
	}
}

// Called to bind functionality to input
void AIDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis or BindAction (TEXT("������Ʈ ����->�Է¿� �����س��� �̸�"), this, Pawn�� ��ȣ���� �� �ֵ��� ���ε��� UE ������Ʈ �ν��Ͻ��� �Լ� ������);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AIDCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AIDCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AIDCharacter::Jump);
}

void AIDCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AIDCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}