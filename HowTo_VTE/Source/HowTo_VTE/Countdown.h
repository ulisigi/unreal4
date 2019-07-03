// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class HOWTO_VTE_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // How long countdown will run
    UPROPERTY(EditAnywhere)
    int32 CountdownTime;
    class UTextRenderComponent* CountdownText;
    void UpdateTimerDisplay();
    void AdvanceTimer();

    UFUNCTION(BlueprintNativeEvent)
    void CountdownHasFinished();
    virtual void CountdownHasFinished_Implementation();
    FTimerHandle CountdownTimerHandle;
};
