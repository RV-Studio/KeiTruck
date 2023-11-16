// Fill out your copyright notice in the Description page of Project Settings.


#include "KeiTruckController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"

AKeiTruckController::AKeiTruckController() {
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Box);

	Camera->SetRelativeLocation(FVector(0, 0, 60));

	CameraRotation = 0;
}

void AKeiTruckController::Interact() {
	GetController()->Possess(this);
}