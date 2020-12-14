// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Interaction.h"
#include "IDNpc_Rabbit.h"

#include "Components/TextBlock.h"

void UWidget_Interaction::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_Interaction::SetInteractionText(FString _text)
{
	Text = _text;
}