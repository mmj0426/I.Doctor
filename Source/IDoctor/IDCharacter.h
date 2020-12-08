// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "GameFramework/Character.h"
#include "IDCharacter.generated.h"


UCLASS()
class IDOCTOR_API AIDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIDCharacter();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public : 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

	//Dialogue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact , Meta = (AllowPrivateAccess = true))
		bool isInteracted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interact, Meta = (AllowPrivateAccess = true))
		bool isNpcOverlapped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interact, Meta = (AllowPrivateAccess = true))
		bool isItemOverlapped;

	UFUNCTION(BlueprintImplementableEvent, Category = Dialogue)
		void NpcDialogue();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
		class UWidgetComponent* WidgetInteraction;


private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	UFUNCTION()
		void Interact();

};
