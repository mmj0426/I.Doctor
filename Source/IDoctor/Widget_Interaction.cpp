// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Interaction.h"
#include "IDNpc_Rabbit.h"

void UWidget_Interaction::BindOnOverlap(AIDNpc_Rabbit* NewNpcOverlap)
{
	//������ ��... �ذ��ʿ�
	IDCHECK(nullptr != NewNpcOverlap);

	CurrentNpcOverlap = NewNpcOverlap;
	NewNpcOverlap->OnOverlap.AddLambda([this]()->void
		{
			if (CurrentNpcOverlap.IsValid())
			{
				IDLOG(Warning, TEXT("Rabbit!!!!"));
			}
		});
}