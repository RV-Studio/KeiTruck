// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableObject.h"
#include "BasePlayer.h"
#include "BaseInventory.h"

void AMoveableObject::BeginPlay() {
	Super::BeginPlay();

	FVector minExtents = FVector();
	FVector maxExtents = FVector();

	Cube->GetLocalBounds(minExtents, maxExtents);

	maxExtents *= Cube->GetRelativeScale3D();

	UnitWidth = maxExtents.X * 2;
	UnitDepth = maxExtents.Y * 2;
	UnitHeight = maxExtents.Z;

	Corners.Add(FVector(maxExtents.X, maxExtents.Y, 0));
	Corners.Add(FVector(maxExtents.X, -maxExtents.Y, 0));
	Corners.Add(FVector(-maxExtents.X, maxExtents.Y, 0));
	Corners.Add(FVector(-maxExtents.X, -maxExtents.Y, 0));

}

void AMoveableObject::Interact(ABasePlayer* _player) {
	Super::Interact(_player);

	if (Container != nullptr) {
		Cast<IInventoryInterface>(Container)->RemoveItemFromIventory(this);
	}
	_player->PickupObject(this);
	SetActorEnableCollision(false);
	Cube->SetSimulatePhysics(false);
	AttachToComponent(_player->GetObjectHolderComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMoveableObject::SetTargetability(ABasePlayer* _player, bool _targetability) {
	targetable = !_player->IsHoldingObject();
}

FVector AMoveableObject::GetDimensions() {
	return FVector(UnitWidth, UnitDepth, 0);
}

TArray<FVector> AMoveableObject::GetCorners()
{
	return Corners;
}

FVector4 AMoveableObject::GetMaxBounds() {
	float top = fminf(fminf(Corners[0].Y, Corners[1].Y), fminf(Corners[2].Y, Corners[3].Y));
	float bottom = fmaxf(fmaxf(Corners[0].Y, Corners[1].Y), fmaxf(Corners[2].Y, Corners[3].Y));
	float left = fminf(fminf(Corners[0].X, Corners[1].X), fminf(Corners[2].X, Corners[3].X));
	float right = fmaxf(fmaxf(Corners[0].X, Corners[1].X), fmaxf(Corners[2].X, Corners[3].X));

	return FVector4(top, bottom, left, right);
}

void AMoveableObject::PlaceObject(FVector _placement, float _rotation, APawn* _container) {
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	FAttachmentTransformRules attachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	AttachToActor(_container, attachmentRules);
	_placement.Z = UnitHeight;
	SetActorRelativeLocation(_placement);
	SetActorRelativeRotation(FRotator(0, _rotation, 0));
	SetActorEnableCollision(true);
	Container = _container;

}
