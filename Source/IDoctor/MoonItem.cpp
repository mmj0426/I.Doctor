// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonItem.h"
#include "IDCharacter.h"
#include "Widget_Interaction.h"

#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMoonItem::AMoonItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Moon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MOON"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));

	RootComponent = Trigger;
	Moon->SetupAttachment(RootComponent);
	Light->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMoonItem::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMoonItem::OnOverlapEnd);

	//Trigger->SetCollisionProfileName(TEXT("Item"));
	Trigger->SetSphereRadius(150.0f);
	Trigger->SetCollisionProfileName("Trigger");

	//정수가 건드릴 것 : FVector(0.0f,0.0f, 절반크기f);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_Moon(TEXT("/Game/Mesh/MoonItem_SM.MoonItem_SM"));

	if (SM_Moon.Succeeded())
	{
		Moon->SetStaticMesh(SM_Moon.Object);
	}

	//정수가 건드릴 것 : FVector(0.0f,0.0f, 절반크기-10f);
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	Light->SetLightColor(FLinearColor::White, true);
}

// Called when the game starts or when spawned
void AMoonItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoonItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoonItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIDCharacter* PlayerCharacter = Cast<AIDCharacter>(OtherActor);
	UWidget_Interaction* WidgetInteraction = Cast<UWidget_Interaction>(PlayerCharacter->WidgetInteraction->GetUserWidgetObject());

	if (nullptr != PlayerCharacter)
	{
		if (nullptr != WidgetInteraction)
		{
			WidgetInteraction->SetInteractionText(FString(TEXT("줍기")));
		}
		PlayerCharacter->isItemOverlapped = true;
		PlayerCharacter->WidgetInteraction->SetVisibility(true);
	}
}

void AMoonItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AIDCharacter* PlayerCharacter = Cast<AIDCharacter>(OtherActor);
	if (nullptr != PlayerCharacter)
	{
		PlayerCharacter->isItemOverlapped = false;
		PlayerCharacter->WidgetInteraction->SetVisibility(false);
	}
}


