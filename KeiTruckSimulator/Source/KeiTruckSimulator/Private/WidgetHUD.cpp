// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetTree.h"
#include "Interactable.h"
#include "BasePlayer.h"
#include "BaseNPC.h"

void UWidgetHUD::NativeConstruct() {
	Super::NativeConstruct();

	OnSetInteractable.AddDynamic(this, &UWidgetHUD::SetInteractable);
	OnSetInteractable.AddDynamic(Cast<ABasePlayer>(GetOwningPlayerPawn()), &ABasePlayer::SetInteractable);

	DialogueTextBorder->SetVisibility(ESlateVisibility::Hidden);

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
		// We are looking at a interactable object
		if (hitInteractable) {
			// We are looking at the same object we were looking at last frame
			if (hitInteractable == InteractableObject) {
				InteractableObject->SetInteractability(true, GetOwningPlayerPawn()->GetActorLocation());
				return;
			}
			// We are looking at a different object
			else {
				// We were previously looking at a different object
				if (InteractableObject) {
					InteractableObject->SetInteractability(false);
				}
				// We are able to interact with this object
				hitInteractable->SetTargetability(Cast<ABasePlayer>(GetOwningPlayerPawn()));
				if (hitInteractable->IsTargetable()) {
					OnSetInteractable.Broadcast(Cast<UObject>(hitInteractable));
					hitInteractable->SetInteractability(true, GetOwningPlayerPawn()->GetActorLocation());
					return;
				}
				else {
					hitInteractable->SetInteractability(false);
					OnSetInteractable.Broadcast(nullptr);
				}
			}
		}
	}

	if (InteractableObject) {
		InteractableObject->SetInteractability(false);
		OnSetInteractable.Broadcast(nullptr);
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

void UWidgetHUD::DisplayDialogue(FText dialogueText, ABaseNPC* talkingNPC) {
	TalkingNPC = talkingNPC;
	DialogueTextBorder->SetVisibility(ESlateVisibility::Visible);

	DialogueTextBox->SetText(dialogueText);
}

void UWidgetHUD::DisplayDialogueOptions(TArray<FString> dialogueOptions) {
	DialogueOptionHolder->ClearChildren();
	DialogueOptionHolder->SetVisibility(ESlateVisibility::Visible);
	selectedIndex = 0;
	DialogueOptionHighlighter = WidgetTree->ConstructWidget<UBorder>(BorderPrefab);
	DialogueOptionHolder->AddChildToVerticalBox(DialogueOptionHighlighter);

	UTextBlock* dialogueOption;
	for (int i = 0; i < dialogueOptions.Num(); ++i) {
		dialogueOption = WidgetTree->ConstructWidget<UTextBlock>();
		dialogueOption->SetText(FText::FromString(dialogueOptions[i]));
		DialogueOptionHolder->AddChildToVerticalBox(dialogueOption);

		DialogueOptionTexts.Add(dialogueOption);
	}
	DialogueOptionHighlighter->AddChild(DialogueOptionTexts[0]);
}

void UWidgetHUD::ScrollOptionsDown() {
	++selectedIndex;
	if (selectedIndex >= DialogueOptionTexts.Num()) { selectedIndex = 0; }

	UpdateDialogueOption();
}

void UWidgetHUD::ScrollOptionsUp() {
	--selectedIndex;
	if (selectedIndex < 0) { selectedIndex = DialogueOptionTexts.Num() - 1; }

	UpdateDialogueOption();
}

void UWidgetHUD::UpdateDialogueOption() {
	DialogueOptionHolder->ClearChildren();
	DialogueOptionHighlighter->ClearChildren();
	for (int i = 0; i < DialogueOptionTexts.Num(); ++i) {
		if (i == selectedIndex) {
			DialogueOptionHolder->AddChildToVerticalBox(DialogueOptionHighlighter);
			DialogueOptionHighlighter->AddChild(DialogueOptionTexts[i]);
		}
		else { DialogueOptionHolder->AddChildToVerticalBox(DialogueOptionTexts[i]); }
	}
}

void UWidgetHUD::SelectOption() {
	TalkingNPC->PlayerSelectsOption(selectedIndex);

	DialogueOptionHolder->SetVisibility(ESlateVisibility::Hidden);
	DialogueOptionTexts.Empty();
}

void UWidgetHUD::CloseDialogue() {
	DialogueTextBorder->SetVisibility(ESlateVisibility::Hidden);
}
