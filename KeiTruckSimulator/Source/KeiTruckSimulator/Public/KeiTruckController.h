// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "KeiTruckController.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API AKeiTruckController : public AInteractable
{
	GENERATED_BODY()

	AKeiTruckController();

public:
	virtual void Interact(ABasePlayer* _player) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Camera")
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* KeiMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* ActionMove;

	UFUNCTION(BlueprintCallable)
		void Move(const FInputActionValue& value);
	
};
