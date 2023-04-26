// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Camera/CameraComponent.h"

ABasePlayer::ABasePlayer() {
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->SetRelativeLocation(FVector(0, 0, 60));

	CameraRotation = 0;
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ABasePlayer::MoveRight);

	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::LookUp);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void ABasePlayer::MoveForward(float Speed) {
	FRotator ControlRotation = GetControlRotation();
	FRotator MakeRotation(0, ControlRotation.Yaw, 0);

	FVector Direction = FRotationMatrix(MakeRotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Speed);
}

void ABasePlayer::MoveRight(float Speed) {
	FRotator ControlRotation = GetControlRotation();
	FRotator MakeRotation(0, ControlRotation.Yaw, 0);

	FVector Direction = FRotationMatrix(MakeRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Speed);
}

void ABasePlayer::LookUp(float Speed) {
	CameraRotation = FMath::Clamp(CameraRotation + Speed, -80, 80);
	FRotator Rotation = this->GetControlRotation();
	Rotation.Pitch = CameraRotation;
	Camera->SetWorldRotation(Rotation);
}

