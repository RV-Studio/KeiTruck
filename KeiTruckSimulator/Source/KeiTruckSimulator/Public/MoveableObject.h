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
		TArray<FVector> GetCorners();

	UFUNCTION(BlueprintCallable)
		FVector4 GetMaxBounds();

	UFUNCTION(BlueprintCallable)
		void PlaceObject(FVector placement, float rotation, TScriptInterface<class IInventoryInterface> _container);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int UnitWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int UnitDepth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector> Corners;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TScriptInterface<IInventoryInterface> Container;
};
