// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InventoryInterface.h"
#include "BaseInventory.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API ABaseInventory : public AInteractable, public IInventoryInterface
{
	GENERATED_BODY()
	
public:
	virtual void Interact(ABasePlayer* _player) override;

	virtual void SetTargetability(class ABasePlayer* _player = nullptr, bool _targetability = true) override;
};
