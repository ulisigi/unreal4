// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
        void MoveForward(float Value);

    UFUNCTION()
        void MoveRight(float Value);

    UFUNCTION()
        void StartJump();

    UFUNCTION()
        void StopJump();

    UFUNCTION()
        void Fire();

    // FPS Camera
    UPROPERTY(VisibleAnywhere)
        class UCameraComponent* FPSCameraComponent;

    // First person mesh
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
       class USkeletalMeshComponent* FPSMesh;

    // Gun muzzle offset
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
        FVector MuzzleOffset;

    // Projectile class to spawn
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
       class TSubclassOf<class AFPSProjectile> ProjectileClass;
};
