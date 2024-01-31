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

	virtual void SetTargetability(class ABasePlayer* _player = nullptr, bool _targetability = true) override;

	UFUNCTION(BlueprintCallable)
		FVector GetDimensions();

	UFUNCTION(BlueprintCallable)
		TArray<FVector> GetCorners();

	UFUNCTION(BlueprintCallable)
		FVector4 GetMaxBounds();

	UFUNCTION(BlueprintCallable)
		void PlaceObject(FVector placement, float rotation, APawn* _container);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int UnitWidth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int UnitDepth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector> Corners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	APawn* Container;
};
