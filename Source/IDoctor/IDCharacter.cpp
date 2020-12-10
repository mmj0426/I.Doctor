// Fill out your copyright notice in the Description page of Project Settings.


#include "IDCharacter.h"
#include "IDAnimInstance.h"
#include "IDNpc_Rabbit.h"
#include "Widget_Interaction.h"
#include "Widget_Item.h"
#include "MoonItem.h"

#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AIDCharacter::AIDCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));

	Trigger->SetupAttachment(GetCapsuleComponent());
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	Trigger->SetSphereRadius(150.0f);
	Trigger->SetCollisionProfileName("Trigger");

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AIDCharacter::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AIDCharacter::OnOverlapEnd);


	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetCapsuleComponent()->SetCapsuleHalfHeight(80.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	GetCharacterMovement()->JumpZVelocity = 400.0f;

	//메쉬 초기값 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -80.0f), FRotator(0.0f, -90.0f, 0.0f));

	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 60.0f), FRotator(-15.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

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

	//UI_Interaction
	WidgetInteraction = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETINTERACTION"));
	WidgetInteraction->SetupAttachment(GetCapsuleComponent());
	WidgetInteraction->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetInteraction->SetRelativeLocation(FVector(0.0f, 70.0f, 10.0f));
	WidgetInteraction->SetPivot(FVector2D(0.0f, 0.5f));
	WidgetInteraction->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget>
		UI_Interaction(TEXT("/Game/Blueprints/UMG/BPWidget_Interaction.BPWidget_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		WidgetInteraction->SetWidgetClass(UI_Interaction.Class);
		WidgetInteraction->SetDrawAtDesiredSize(true);
	}

	isPicking = false;
	itemCount = 0;

	

}

void AIDCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	IDAnim = Cast<UIDAnimInstance>(GetMesh()->GetAnimInstance());
	IDCHECK(nullptr != IDAnim);

	IDAnim->OnMontageEnded.AddDynamic(this, &AIDCharacter::OnPickupMotageEnded);

	IDAnim->OnPickupCheck.AddLambda([this]()-> void
		{
			CurrentItem->Destroy();
			itemCount++;
			WidgetItem->SetItemCount(itemCount);
			
			
			IDLOG(Warning, TEXT("Item Count : %d "), itemCount);
		});
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

	//PlayerInputComponent->BindAxis or BindAction (TEXT("프로젝트 설정->입력에 설정해놓은 이름"), this, Pawn이 신호받을 수 있도록 바인딩할 UE 오브젝트 인스턴스의 함수 포인터);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AIDCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AIDCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AIDCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AIDCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AIDCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &AIDCharacter::Interact);
}

void AIDCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AIDCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AIDCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AIDCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void AIDCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMoonItem* Item = Cast<AMoonItem>(OtherActor);
	UWidget_Interaction* Widget_Interaction = Cast<UWidget_Interaction>(WidgetInteraction->GetUserWidgetObject());

	if (nullptr != Item)
	{
		if (nullptr != Widget_Interaction)
		{
			Widget_Interaction->SetInteractionText(FString(TEXT("줍기")));
		}

		isItemOverlapped = true;
		WidgetInteraction->SetVisibility(true);
		CurrentItem = Item;
	}


}

void AIDCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Item = Cast<AMoonItem>(OtherActor);
	if (nullptr != Item)
	{
		isItemOverlapped = false;
		WidgetInteraction->SetVisibility(false);
	}
}

// F키 눌렀을 때
void AIDCharacter::Interact()
{
	if (isNpcOverlapped == true)
	{
		WidgetInteraction->SetVisibility(false);
		NpcDialogue();
	}

	if (isItemOverlapped == true)
	{
		Pickup();
	}

}

void AIDCharacter::Pickup()
{
	if (isPicking)return;

	IDAnim->PlayPickupMontage();

	isPicking = true;
}

void AIDCharacter::OnPickupMotageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IDCHECK(isPicking);
	isPicking = false;
}