// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDoctor.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Item.generated.h"

/**
 * 
 */
UCLASS()
class IDOCTOR_API UWidget_Item : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItemCount(int32 _count);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Count;

	virtual void NativeConstruct() override;

};
