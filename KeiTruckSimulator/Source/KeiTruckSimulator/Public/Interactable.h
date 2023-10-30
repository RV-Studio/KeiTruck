// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interactable.generated.h"

UCLASS()
class KEITRUCKSIMULATOR_API AInteractable : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UTextRenderComponent* TextRenderer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Rotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool interactable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float interactionTimer;

	FVector Cross(FVector v1, FVector v2);

	FVector Normalize(FVector v);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void IsInteractable(FVector playerPos);

	UFUNCTION(BlueprintCallable)
	void IsNotInteractable();

	UFUNCTION(BlueprintCallable)
	FRotator LookAt(FVector eye, FVector center);

};
