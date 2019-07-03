// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectGameModeBase.h"
#include "FPSProject.h"


void AFPSProjectGameModeBase::StartPlay()
{
    Super::StartPlay();
    if (GEngine)
    {
        // display debug message for 5 seconds
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
    }
}