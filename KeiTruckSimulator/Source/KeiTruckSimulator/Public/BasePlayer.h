// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "BasePlayer.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Camera")
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CameraRotation;

	UFUNCTION(BlueprintCallable)
		void LookUp(float Speed);


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* BipedalMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ActionMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ActionJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ActionLook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ActionInteract;

	void Move(const FInputActionValue& value);

private:
	
};
