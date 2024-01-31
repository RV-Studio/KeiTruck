// Fill out your copyright notice in the Description page of Project Settings.


#include "KeiTruckController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BasePlayer.h"
#include "MathLibrary.h"

AKeiTruckController::AKeiTruckController() {
	PrimaryActorTick.bCanEverTick = true;

	Rotator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotator"));
	Rotator->SetupAttachment(GetMesh());
	Rotator->SetRelativeLocation(FVector(0, 0, 40));

	CabBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CabBody"));
	CabBody->SetupAttachment(GetMesh());
	CabBody->SetRelativeLocation(FVector(0, 0, 40));

	EnterVehiclePosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnterVehiclePosition"));
	EnterVehiclePosition->SetupAttachment(CabBody);
	EnterVehiclePosition->SetRelativeLocation(FVector((260, 130, 110)));

	ExitVehiclePosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExitVehiclePosition"));
	ExitVehiclePosition->SetupAttachment(CabBody);
	ExitVehiclePosition->SetRelativeLocation(FVector((250, 310, 30)));

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderer->SetupAttachment(Rotator);
	TextRenderer->SetRelativeLocation(FVector(70, 0, 30));

	TextRenderer->SetText(FText::FromString(TEXT("Press \"F\" to Interact")));
	TextRenderer->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	TextRenderer->SetVisibility(false, true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 650.0f;
	SpringArm->SetRelativeLocation(FVector(0.f, 80.f, 90.f));

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	ThirdPersonCamera->SetRelativeLocationAndRotation(FVector(-170.000000, 0.000000, 160.000000), FRotator(0, 350, 0));
	ThirdPersonCamera->Activate();

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh());
	FirstPersonCamera->Deactivate();
}

void AKeiTruckController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	float dampeningAmount = ChaosWheeledVehicleMovementComponent->IsMovingOnGround() ? 0 : 3;

	GetMesh()->SetAngularDamping(dampeningAmount);
	//InterpsToOriginalRotation(DeltaTime);
}

void AKeiTruckController::BeginPlay() {
	Super::BeginPlay();

	SetTargetability();

	ChaosWheeledVehicleMovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
}

void AKeiTruckController::InterpsToOriginalRotation(float _deltaTime) {
	FRotator relRot = SpringArm->GetRelativeRotation();
	float newYaw = MathLibrary::FInpterpTo(relRot.Yaw, 0, _deltaTime, 1);
	SpringArm->SetRelativeRotation(FRotator(0, newYaw, 0));
}

void AKeiTruckController::Interact(ABasePlayer* _player) {
	_player->GetController()->Possess(this);
	player = _player;

	player->AttachToComponent(EnterVehiclePosition, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	player->SetActorEnableCollision(false);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(KeiMappingContext, 0);
		}
	}
}

void AKeiTruckController::SetInteractability(bool _interactability, FVector playerPos) {
	if (_interactability) {
		Rotator->SetWorldRotation(MathLibrary::LookAt(Rotator->GetComponentLocation(), playerPos).Rotator());
	}

	TextRenderer->SetVisibility(_interactability, true);
}

void AKeiTruckController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ActionBrake, ETriggerEvent::Triggered, this, &AKeiTruckController::Brake);
		EnhancedInputComponent->BindAction(ActionBrake, ETriggerEvent::Completed, this, &AKeiTruckController::Brake);
		EnhancedInputComponent->BindAction(ActionExitVehicle, ETriggerEvent::Triggered, this, &AKeiTruckController::ExitVehicle);
		EnhancedInputComponent->BindAction(ActionHandbrake, ETriggerEvent::Triggered, this, &AKeiTruckController::HandbrakeStart);
		EnhancedInputComponent->BindAction(ActionHandbrake, ETriggerEvent::Completed, this, &AKeiTruckController::HandbrakeEnd);
		EnhancedInputComponent->BindAction(ActionLookAround, ETriggerEvent::Triggered, this, &AKeiTruckController::LookAround);
		EnhancedInputComponent->BindAction(ActionReset, ETriggerEvent::Triggered, this, &AKeiTruckController::Reset);
		EnhancedInputComponent->BindAction(ActionSteering, ETriggerEvent::Triggered, this, &AKeiTruckController::Steering);
		EnhancedInputComponent->BindAction(ActionSteering, ETriggerEvent::Completed, this, &AKeiTruckController::Steering);
		EnhancedInputComponent->BindAction(ActionThrottle, ETriggerEvent::Triggered, this, &AKeiTruckController::Throttle);
		EnhancedInputComponent->BindAction(ActionThrottle, ETriggerEvent::Completed, this, &AKeiTruckController::Throttle);
		EnhancedInputComponent->BindAction(ActionToggleCamera, ETriggerEvent::Triggered, this, &AKeiTruckController::ToggleCamera);
	}
}

void AKeiTruckController::Brake(const FInputActionValue& value) {
	GetVehicleMovementComponent()->SetBrakeInput(value.Get<float>());
}

void AKeiTruckController::ExitVehicle(const FInputActionValue& value) {
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		PlayerController->Possess(player);
	}
	player->ExitVehicle();
	player->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	player->SetActorLocation(ExitVehiclePosition->GetComponentLocation());
	player->SetActorEnableCollision(true);
}

void AKeiTruckController::HandbrakeStart(const FInputActionValue& value) {
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AKeiTruckController::HandbrakeEnd(const FInputActionValue& value) {
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AKeiTruckController::LookAround(const FInputActionValue& value) {
	float YawChange = value.Get<float>(); // Adjust the sensitivity here

	// Get the current rotation of the spring arm
	FRotator CurrentRotation = SpringArm->GetRelativeRotation();

	// Modify the yaw (Z-axis rotation) based on the input
	FRotator NewRotation = FRotator(0, YawChange, 0) + CurrentRotation;

	// Output the resulting rotation for debugging
	UE_LOG(LogTemp, Warning, TEXT("New Rotation: %s"), *NewRotation.ToString());

	// Set the new rotation to the spring arm
	SpringArm->SetRelativeRotation(NewRotation);
}

void AKeiTruckController::Reset(const FInputActionValue& value) {

}

void AKeiTruckController::Steering(const FInputActionValue& value) {
	GetVehicleMovementComponent()->SetSteeringInput(value.Get<float>());
}

void AKeiTruckController::Throttle(const FInputActionValue& value) {
	GetVehicleMovementComponent()->SetThrottleInput(value.Get<float>());
}

void AKeiTruckController::ToggleCamera(const FInputActionValue& value) {
	FirstPersonCamera->Deactivate();
	ThirdPersonCamera->Deactivate();

	ActiveCamera = !ActiveCamera;

	if (ActiveCamera) {
		FirstPersonCamera->Activate();
	}
	else {
		ThirdPersonCamera->Activate();
	}
}
