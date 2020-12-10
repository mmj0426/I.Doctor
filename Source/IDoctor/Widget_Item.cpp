// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Item.h"

#include "Components/TextBlock.h"

void UWidget_Item::NativeConstruct()
{
	Super::NativeConstruct();

	UBlueprintGeneratedClass* BPWidget_Item = LoadObject<UBlueprintGeneratedClass>
		(nullptr, TEXT("/Game/Blueprints/UMG/BPWidget_Item.BPWidget_Item_C"));
}

void UWidget_Item::SetItemCount(int32 _count)
{
	Count = _count;
}