// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InteractableInterface.h"
#include "BaseNPC.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API ABaseNPC : public ABaseCharacter, public IInteractableInterface
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class ABaseAIController> AIClass;

		bool isInteractingWithPlayer = false;

		class ABasePlayer* player;

public:
	// Sets default values for this character's properties
	ABaseNPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ABasePlayer* _player) override;

	virtual void SetInteractability(bool _interactability, FVector playerPos = FVector(0, 0, 0));
};
