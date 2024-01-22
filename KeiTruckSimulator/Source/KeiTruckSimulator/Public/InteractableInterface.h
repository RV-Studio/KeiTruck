// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KEITRUCKSIMULATOR_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(class ABasePlayer* _player) = 0;

	virtual void SetInteractability(bool _interactability, FVector playerPos = FVector(0, 0 ,0)) = 0;

	virtual void SetTargetability(class ABasePlayer* _player = nullptr, bool _targetability = true);

	virtual bool IsTargetable();


protected:
	bool targetable; 
};
