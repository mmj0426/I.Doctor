// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(IDoctor, Log, All); 

#define ID_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define ID_S(Verbosity) UE_LOG(IDoctor, Verbosity, TEXT("%s"), *ID_CALLINFO)

#define IDLOG(Verbosity,Format, ...) UE_LOG(IDoctor, Verbosity, TEXT("%s %s"), *ID_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

//IDCHECK ��ũ�θ� �߰� : ��Ÿ�ӿ��� ������ �߻��� �� ������ �����α� �Ѹ��� �Լ� ��ȯ
#define IDCHECK(Expr, ...){if(!(Expr)) {IDLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}
