// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "MoveableObject.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API AMoveableObject : public AInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(ABasePlayer* _player) override;

	UFUNCTION(BlueprintCallable)
		FVector GetDimensions();

	UFUNCTION(BlueprintCallable)
		bool GetIsVertical();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int unitWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int unitDepth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isVertical;
};
