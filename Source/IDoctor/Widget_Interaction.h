// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class IDOCTOR_API UWidget_Interaction : public UUserWidget
{
	GENERATED_BODY()
	
public : 
	void SetInteractionText(FString _text);

protected :

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString Text;

	virtual void NativeConstruct() override;

};
