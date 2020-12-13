// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelVolume.h"
#include "IDCharacter.h"

#include "Components/BoxComponent.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
ANextLevelVolume::ANextLevelVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("LevelVolume"));

}

// Called when the game starts or when spawned
void ANextLevelVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANextLevelVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ANextLevelVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AIDCharacter* Character = Cast<AIDCharacter>(OtherActor);
	if (nullptr != Character)
	{
		UGameplayStatics::OpenLevel(this, TransferLevelName);
	}
}
