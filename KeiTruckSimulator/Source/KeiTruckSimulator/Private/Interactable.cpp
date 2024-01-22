// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MathLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractable::AInteractable()
{
	SetTargetability();

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetCollisionProfileName(FName("Pawn"));
	Box->SetupAttachment(RootComponent);

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetupAttachment(Box);

	Rotator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotator"));
	Rotator->SetupAttachment(Box);
	Rotator->SetRelativeLocation(FVector(0, 0, 40));

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderer->SetupAttachment(Rotator);
	TextRenderer->SetRelativeLocation(FVector(70, 0, 30));

	TextRenderer->SetText(FText::FromString(TEXT("Press \"F\" to Interact")));
	TextRenderer->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	TextRenderer->SetVisibility(false, true);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInteractable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AInteractable::Interact(ABasePlayer* _player) {
	player = _player;
	UE_LOG(LogTemp, Warning, TEXT("Interacted"));
}

void AInteractable::SetInteractability(bool _interactability, FVector playerPos) {
	if (_interactability) {
		Rotator->SetWorldRotation(MathLibrary::LookAt(Rotator->GetComponentLocation(), playerPos).Rotator());
	}

	TextRenderer->SetVisibility(_interactability, true);
}


