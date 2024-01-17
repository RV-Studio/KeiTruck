// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Interactable.h"
#include "BasePlayer.h"

void UWidgetHUD::NativeConstruct() {
	Super::NativeConstruct();

	OnSetInteractable.AddDynamic(this, &UWidgetHUD::SetInteractable);
	OnSetInteractable.AddDynamic(Cast<ABasePlayer>(GetOwningPlayerPawn()), &ABasePlayer::SetInteractable);
}

void UWidgetHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	FVector SP;
	FVector EP;
	GetLinePoints(SP, EP);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Vehicle);

	FCollisionQueryParams Params;
	Params.TraceTag = "LineTraceSingleForObjects";
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(GetOwningPlayerPawn());

	FHitResult OutHit;
	if (GetOwningPlayerPawn()->GetWorld()->LineTraceSingleByObjectType(OutHit, SP, EP, ObjectParams, Params)) {
		EndPoint = OutHit.Location;

		IInteractableInterface* hitInteractable = Cast< IInteractableInterface>(OutHit.GetActor());
		if (hitInteractable) {
			if (hitInteractable == InteractableObject) {
				InteractableObject->SetInteractability(true, GetOwningPlayerPawn()->GetActorLocation());
				return;
			}
			else {
				if (InteractableObject) {
					InteractableObject->SetInteractability(false);
				}
				OnSetInteractable.Broadcast(Cast<UObject>(hitInteractable));
				hitInteractable->SetInteractability(true, GetOwningPlayerPawn()->GetActorLocation());
				return;
			}
		}
	}

	if (InteractableObject) {
		InteractableObject->SetInteractability(false);
		SetInteractable(nullptr);
	}
}

void UWidgetHUD::SetInteractable(UObject* interactable) {
	InteractableObject = Cast< IInteractableInterface>(interactable);
}

void UWidgetHUD::GetLinePoints(FVector& _StartPoint, FVector& _EndPoint) {
	FVector2D PP;
	FVector2D VP;
	FVector EP;
	USlateBlueprintLibrary::LocalToViewport(GetOwningPlayerPawn()->GetWorld(), Crosshair->GetCachedGeometry(), FVector2D(0, 0), PP, VP);

	DeprojectScreenToWorld(GetOwningPlayer(), PP, _StartPoint, EP);
	EP *= InteractionDistance;
	EP += _StartPoint;
	EndPoint = _EndPoint = EP;

}

bool UWidgetHUD::DeprojectScreenToWorld(APlayerController const* Player, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection)
{
	ULocalPlayer* const LP = Player ? Player->GetLocalPlayer() : nullptr;
	if (LP && LP->ViewportClient)
	{
		// get the projection data
		FSceneViewProjectionData ProjectionData;
		if (LP->GetProjectionData(LP->ViewportClient->Viewport,/*out*/ ProjectionData))
		{
			FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
			FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ WorldPosition, /*out*/ WorldDirection);
			return true;
		}
	}

	// something went wrong, zero things and return false
	WorldPosition = FVector::ZeroVector;
	WorldDirection = FVector::ZeroVector;
	return false;
}

void UWidgetHUD::DisplayDialogue(FText dialogueText) {
	DialogueTextBox->SetText(dialogueText);
}
