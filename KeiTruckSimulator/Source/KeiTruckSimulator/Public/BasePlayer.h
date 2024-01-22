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
		void SetInteractable(UObject* interactable);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		UStaticMeshComponent* GetObjectHolderComponent();

	void DisplayDialogue(FText dialogueText, class ABaseNPC* talkingNPC);

	void DisplayDialogueOptions(TArray<FString> dialogueOptions);

	void CloseDialogue();

	void PickupObject(class AMoveableObject* objectToHold);

	bool IsHoldingObject();

	AMoveableObject* GetHeldObject();
	
protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* BipedalMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* DialogueMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* ActionMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* ActionJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* ActionLook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* ActionInteract;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* ActionNavigateOptions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* ActionSelectOption;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UStaticMeshComponent* ObjectHolder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
		class UWidgetHUD* HUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf<UWidgetHUD> HUDClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class APlayerController* AsPlayerController;

	class IInteractableInterface* interactableObject;

	UFUNCTION(BlueprintCallable)
		void Move(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void LookAround(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void LookUp(float Speed);

	UFUNCTION(BlueprintCallable)
		void Interact(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void NavigateOptions(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void SelectOption(const FInputActionValue& value);

		ABaseNPC* talkingNPC;

		class AMoveableObject* heldObject;

private:
	
};
