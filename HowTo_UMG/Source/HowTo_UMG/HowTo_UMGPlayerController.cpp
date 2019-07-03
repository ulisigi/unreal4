// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HowTo_UMGPlayerController.h"

void AHowTo_UMGPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}