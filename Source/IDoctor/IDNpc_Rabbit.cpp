// Fill out your copyright notice in the Description page of Project Settings.


#include "IDNpc_Rabbit.h"
#include "IDCharacter.h"
#include "Widget_Interaction.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AIDNpc_Rabbit::AIDNpc_Rabbit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	Sphere->SetSphereRadius(200.0f);
	Sphere->SetCollisionProfileName("Trigger");
	Sphere->SetupAttachment(GetCapsuleComponent());

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AIDNpc_Rabbit::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AIDNpc_Rabbit::OnOverlapEnd);

	GetCapsuleComponent()->SetCapsuleHalfHeight(80.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NPC"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -80.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_RABBIT(TEXT("/Game/CharacterAsset/Meshes/OneMeshCharacter/RabitSK.RabitSK"));

	if (SK_RABBIT.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_RABBIT.Object);
	}

}

// Called when the game starts or when spawned
void AIDNpc_Rabbit::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIDNpc_Rabbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIDNpc_Rabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIDNpc_Rabbit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIDCharacter* PlayerCharacter = Cast<AIDCharacter>(OtherActor);
	UWidget_Interaction* WidgetInteraction = Cast<UWidget_Interaction>(PlayerCharacter->WidgetInteraction->GetUserWidgetObject());

	if (nullptr != PlayerCharacter)
	{
		if (nullptr != WidgetInteraction)
		{
			WidgetInteraction->SetInteractionText(FString(TEXT("대화하기")));
		}

		PlayerCharacter->isNpcOverlapped = true;
		PlayerCharacter->WidgetInteraction->SetVisibility(true);
	}
}

void AIDNpc_Rabbit::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AIDCharacter* PlayerCharacter = Cast<AIDCharacter>(OtherActor);
	if (nullptr != PlayerCharacter)
	{
		PlayerCharacter->isNpcOverlapped = false;
		PlayerCharacter->WidgetInteraction->SetVisibility(false);
	}
}
