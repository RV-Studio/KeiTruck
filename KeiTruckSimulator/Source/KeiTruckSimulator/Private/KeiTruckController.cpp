// Fill out your copyright notice in the Description page of Project Settings.


#include "KeiTruckController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "BasePlayer.h"

AKeiTruckController::AKeiTruckController() {
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Box);

	Camera->SetRelativeLocationAndRotation(FVector(-170.000000, 0.000000, 160.000000), FRotator(0, 350, 0));

	CameraRotation = 0;
}

void AKeiTruckController::Interact(ABasePlayer* _player) {
	Super::Interact(_player);
	_player->GetController()->Possess(this);
}