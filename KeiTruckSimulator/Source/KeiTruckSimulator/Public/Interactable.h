// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractableInterface.h"
#include "Interactable.generated.h"

UCLASS()
class KEITRUCKSIMULATOR_API AInteractable : public APawn, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInteractable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void Interact(ABasePlayer* _player) override;

	virtual void SetInteractability(bool _interactability, FVector playerPos = FVector(0, 0, 0)) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Cube;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UTextRenderComponent* TextRenderer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Rotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* player;

	

public:	
	

};
