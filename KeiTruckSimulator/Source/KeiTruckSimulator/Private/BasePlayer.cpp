// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WidgetHUD.h"
#include "Interactable.h"

ABasePlayer::ABasePlayer() {
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->SetRelativeLocation(FVector(0, 0, 60));

	CameraRotation = 0;

	ObjectHolder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectHolder"));
	ObjectHolder->SetupAttachment(Camera);
	ObjectHolder->SetRelativeLocation(FVector(30, 10, 0));
}

void ABasePlayer::BeginPlay() {
	AsPlayerController = Cast<APlayerController>(GetController());
	HUD = CreateWidget<UWidgetHUD>(AsPlayerController, HUDClass);

	Super::BeginPlay();

	HUD->AddToViewport();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(BipedalMappingContext, 0);
			Subsystem->AddMappingContext(DialogueMappingContext, 1);
		}
	}

}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ABasePlayer::LookAround);
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, this, &ABasePlayer::Interact);

		EnhancedInputComponent->BindAction(ActionNavigateOptions, ETriggerEvent::Triggered, this, &ABasePlayer::NavigateOptions);
		EnhancedInputComponent->BindAction(ActionSelectOption, ETriggerEvent::Triggered, this, &ABasePlayer::SelectOption);
	}
}

void ABasePlayer::Interact(const FInputActionValue& value) {
	if (interactableObject) {
		interactableObject->Interact(this);
	}
}

void ABasePlayer::NavigateOptions(const FInputActionValue& value) {
	float currentValue = value.Get<float>();
	if (currentValue < 0) { HUD->ScrollOptionsDown(); }
	else if (currentValue > 0) { HUD->ScrollOptionsUp(); }
}

void ABasePlayer::SelectOption(const FInputActionValue& value) {
	if (talkingNPC) { HUD->SelectOption(); }
}

void ABasePlayer::SetInteractable(UObject* interactable) {
	interactableObject = Cast< IInteractableInterface>(interactable);
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

void ABasePlayer::LookAround(const FInputActionValue& value) {
	FVector2D currentValue = value.Get<FVector2D>();

	AddControllerYawInput(currentValue.X);

	LookUp(currentValue.Y);
}

void ABasePlayer::LookUp(float Speed) {
	CameraRotation = FMath::Clamp(CameraRotation + Speed, -80, 80);
	FRotator Rotation = this->GetControlRotation();
	Rotation.Pitch = CameraRotation;
	Camera->SetWorldRotation(Rotation);
}

UStaticMeshComponent* ABasePlayer::GetObjectHolderComponent() {
	return ObjectHolder;
}

void ABasePlayer::DisplayDialogue(FText dialogueText, ABaseNPC* _talkingNPC) {
	HUD->DisplayDialogue(dialogueText, _talkingNPC);
	talkingNPC = _talkingNPC;
}

void ABasePlayer::DisplayDialogueOptions(TArray<FString> dialogueOptions) {
	HUD->DisplayDialogueOptions(dialogueOptions);
}

void ABasePlayer::CloseDialogue() {
	HUD->CloseDialogue();
}

void ABasePlayer::PickupObject(AMoveableObject* objectToHold) {
	heldObject = objectToHold;
}

bool ABasePlayer::IsHoldingObject() { return (heldObject != nullptr); }

AMoveableObject* ABasePlayer::GetHeldObject() {
	return heldObject;
}