// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include "Components/Image.h"
#include "Interactable.h"

void UWidgetHUD::NativeConstruct() {
	Super::NativeConstruct();

	//OnSetInteractable.AddDynamic(this, &UWidgetHUD::SetInteractable);
}

void UWidgetHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	FVector SP;
	FVector EP;
	GetLinePoints(SP, EP);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FCollisionQueryParams Params;
	Params.TraceTag = "LineTraceSingleForObjects";
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(GetOwningPlayerPawn());

	FHitResult OutHit;
	if (GetOwningPlayerPawn()->GetWorld()->LineTraceSingleByObjectType(OutHit, SP, EP, ObjectParams, Params)) {
		EndPoint = OutHit.Location;

		AInteractable* hitInteractable = Cast<AInteractable>(OutHit.GetActor());
		if (hitInteractable) {
			if (hitInteractable == InteractableObject) {
				InteractableObject->IsInteractable(GetOwningPlayerPawn()->GetActorLocation());
				return;
			}
			else {
				if (InteractableObject) {
					InteractableObject->IsNotInteractable();
				}
				OnSetInteractable.Broadcast(hitInteractable);
				hitInteractable->IsInteractable(GetOwningPlayerPawn()->GetActorLocation());
				return;
			}
		}
	}

	if (InteractableObject) {
		InteractableObject->IsNotInteractable();
		SetNewInteractable(nullptr);
	}
}

void UWidgetHUD::SetNewInteractable(AInteractable* interactable) {
	InteractableObject = interactable;
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