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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector EndPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector HitEndPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float InteractionDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AInteractable* InteractableObject;

public:
	UFUNCTION()
		void SetInteractable(AInteractable* interactable);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void GetLinePoints(FVector& _StartPoint, FVector& _EndPoint);
	UFUNCTION()
		bool DeprojectScreenToWorld(APlayerController const* Player, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection);

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Event Dispatchers")
		FEventDispatcherInteractable OnSetInteractable;
};
