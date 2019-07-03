// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HowTo_UMGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HOWTO_UMG_API AHowTo_UMGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

    UPROPERTY()
        UUserWidget* CurrentWidget;
};
