// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableObject.h"
#include "BasePlayer.h"

void AMoveableObject::Interact(ABasePlayer* _player) {
	Super::Interact(_player);

	AttachToComponent(_player->GetObjectHolderComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetActorEnableCollision(false);
}

FVector AMoveableObject::GetDimensions() {
	return FVector(unitWidth, unitDepth, 0);
}

bool AMoveableObject::GetIsVertical() {
	return isVertical;
}