// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventDispatcherHolder.h"
#include "WidgetHUD.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Crosshair;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UBorder* DialogueTextBorder;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* DialogueTextBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* DialogueOptionHolder;
	UPROPERTY(BlueprintReadOnly)
		TSubclassOf<UBorder> BorderPrefab;

		UBorder* DialogueOptionHighlighter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector EndPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector HitEndPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float InteractionDistance;

		class IInteractableInterface* InteractableObject;

		TArray<UTextBlock*> DialogueOptionTexts;
		int selectedIndex = 0;

		void UpdateDialogueOption();

		class ABaseNPC* TalkingNPC;

public:
	UFUNCTION()
		void SetInteractable(UObject* interactable);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void GetLinePoints(FVector& _StartPoint, FVector& _EndPoint);
	UFUNCTION()
		bool DeprojectScreenToWorld(APlayerController const* Player, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection);
	UFUNCTION()
		void DisplayDialogue(FText dialogueText, class ABaseNPC* talkingNPC);
	UFUNCTION()
		void DisplayDialogueOptions(TArray<FString> dialogueOptions);
	UFUNCTION()
		void ScrollOptionsDown();
	UFUNCTION()
		void ScrollOptionsUp();
	UFUNCTION()
		void SelectOption();
	UFUNCTION()
		void CloseDialogue();

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Event Dispatchers")
		FEventDispatcherInteractable OnSetInteractable;
};
