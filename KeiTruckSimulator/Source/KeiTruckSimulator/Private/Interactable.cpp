// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rotator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotator"));
	Rotator->SetupAttachment(RootComponent);
	Rotator->SetRelativeLocation(FVector(0, 0, 40));

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderer->SetupAttachment(Rotator);
	TextRenderer->SetRelativeLocation(FVector(70, 30, 30));

	TextRenderer->SetVisibility(false, true);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AInteractable::Cross(FVector v1, FVector v2) {
	float x = (v1.Y * v2.Z) - (v1.Z * v2.Y);
	float y = (v1.Z * v2.X) - (v1.X * v2.Z);
	float z = (v1.X * v2.Y) - (v1.Y * v2.X);
	return FVector(x, y, z);
}

FVector AInteractable::Normalize(FVector v) {
	float length = sqrtf((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z));
	float x = v.X / length;
	float y = v.Y / length;
	float z = v.Z / length;
	return FVector(x, y, z);
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

void AInteractable::Interact() {

}

void AInteractable::IsInteractable(FVector playerPos) {
	Rotator->SetWorldRotation(LookAt(Rotator->GetComponentLocation(), playerPos));

	TextRenderer->SetVisibility(true, true);
}

void AInteractable::IsNotInteractable() {
	TextRenderer->SetVisibility(false, true);
}

FRotator AInteractable::LookAt(FVector eye, FVector center) {
	FVector X = Normalize(center - eye);
	FVector Y = Normalize(Cross(FVector(0, 0, 1), X));
	FVector Z = Normalize(Cross(X, Y));

	FMatrix RotMatrix(X, Y, Z, FVector::ZeroVector);

	return RotMatrix.Rotator();
}

