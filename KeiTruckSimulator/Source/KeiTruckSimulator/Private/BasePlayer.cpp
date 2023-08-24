// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABasePlayer::ABasePlayer() {
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->SetRelativeLocation(FVector(0, 0, 60));

	CameraRotation = 0;
}

void ABasePlayer::BeginPlay() {
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(BipedalMappingContext, 0);
		}
	}

}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		 
	}





	/*PlayerInputComponent->BindAxis("Forward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ABasePlayer::MoveRight);*/

	PlayerInputComponent->BindAxis("TurnTo", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::LookUp);

	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void ABasePlayer::Move(const FInputActionValue& value) {
	
	FVector2D currentValue = value.Get<FVector2D>();

	// Forward Direction
	FRotator ControlRotation = GetControlRotation();
	FRotator MakeRotation(0, ControlRotation.Yaw, 0);

	FVector Direction = FRotationMatrix(MakeRotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, currentValue.Y);

	//Sideways Direction
	ControlRotation = GetControlRotation();
	FRotator MakeRotation2(0, ControlRotation.Yaw, 0);

	Direction = FRotationMatrix(MakeRotation2).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, currentValue.X);
}

void ABasePlayer::LookUp(float Speed) {
	CameraRotation = FMath::Clamp(CameraRotation + Speed, -80, 80);
	FRotator Rotation = this->GetControlRotation();
	Rotation.Pitch = CameraRotation;
	Camera->SetWorldRotation(Rotation);
}

