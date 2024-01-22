// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableObject.h"
#include "BasePlayer.h"
#include "BaseInventory.h"

void AMoveableObject::Interact(ABasePlayer* _player) {
	Super::Interact(_player);

	if (Container != nullptr) {
		Container->RemoveItemFromIventory(this);
	}

	AttachToComponent(_player->GetObjectHolderComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetActorEnableCollision(false);
}

FVector AMoveableObject::GetDimensions() {
	return FVector(UnitWidth, UnitDepth, 0);
}

TArray<FVector> AMoveableObject::GetCorners()
{
	return Corners;
}

FVector4 AMoveableObject::GetMaxBounds() {
	float top = fmaxf(fmaxf(Corners[0].Y, Corners[1].Y), fmaxf(Corners[2].Y, Corners[3].Y));
	float bottom = fminf(fminf(Corners[0].Y, Corners[1].Y), fminf(Corners[2].Y, Corners[3].Y));
	float left = fminf(fminf(Corners[0].X, Corners[1].X), fminf(Corners[2].X, Corners[3].X));
	float right = fmaxf(fmaxf(Corners[0].X, Corners[1].X), fmaxf(Corners[2].X, Corners[3].X));

	return FVector4(top, bottom, left, right);
}

void AMoveableObject::PlaceObject(FVector _placement, float _rotation, TScriptInterface<IInventoryInterface> _container) {
	SetActorLocation(_placement);
	SetActorRotation(FRotator(0, _rotation, 0));
	Container = _container;
}
