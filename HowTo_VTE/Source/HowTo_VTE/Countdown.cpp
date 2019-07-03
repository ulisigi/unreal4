// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "Countdown.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(150.0f);
    RootComponent = CountdownText;
    CountdownTime = 3;

}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
    UpdateTimerDisplay();
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::UpdateTimerDisplay()
{
    CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        // Stop running timer
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void ACountdown::CountdownHasFinished_Implementation()
{
    // Change to a special readout
    CountdownText->SetText(TEXT("GO!"));
}

