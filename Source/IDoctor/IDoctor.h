// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(IDoctor, Log, All); 

#define ID_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define ID_S(Verbosity) UE_LOG(IDoctor, Verbosity, TEXT("%s"), *ID_CALLINFO)

#define IDLOG(Verbosity,Format, ...) UE_LOG(IDoctor, Verbosity, TEXT("%s %s"), *ID_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

//ABCHECK 매크로를 추가 : 런타임에서 문제가 발생할 때 붉은색 에러로그 뿌리고 함수 반환
#define ABCHECK(Expr, ...){if(!(Expr)) {IDLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}
