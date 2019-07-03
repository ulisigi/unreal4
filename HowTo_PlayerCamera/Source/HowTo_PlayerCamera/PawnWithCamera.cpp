// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PawnWithCamera.h"
#include "HowTo_PlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create components
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    OurCameraSpringArm->SetupAttachment(RootComponent);
    OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
    OurCameraSpringArm->TargetArmLength = 400.f;
    OurCameraSpringArm->bEnableCameraLag = true;
    OurCameraSpringArm->CameraRotationLagSpeed = 3.0f;
    
    OurCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

    AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    {
        if (bZoomingIn)
        {
            ZoomFactor += DeltaTime / 0.5f;
        }
        else
        {
            ZoomFactor -= DeltaTime / 0.25f;
        }
        ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
        OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
        OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
    }

    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += CameraInput.X;
        SetActorRotation(NewRotation);
    }

    {
        FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
        OurCameraSpringArm->SetWorldRotation(NewRotation);
    }

    {
        if (!MovementInput.IsZero())
        {
            MovementInput = MovementInput.GetSafeNormal() * 100.0f;
            FVector NewLocation = GetActorLocation();
            NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
            NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
            SetActorLocation(NewLocation);
        }
    }
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
    InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

    InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
    InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);
}

// Input functions
void APawnWithCamera::MoveForward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
    bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
    bZoomingIn = false;
}