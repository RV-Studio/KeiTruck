// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInventory.h"
#include "BasePlayer.h"

void ABaseInventory::BeginPlay() {
	InventoryCorners = EditableInventoryCorners;

	if (InventoryCorners.Num() == 4) {
		float top = fminf(fminf(InventoryCorners[0].Y, InventoryCorners[1].Y), fminf(InventoryCorners[2].Y, InventoryCorners[3].Y));
		float bottom = fmaxf(fmaxf(InventoryCorners[0].Y, InventoryCorners[1].Y), fmaxf(InventoryCorners[2].Y, InventoryCorners[3].Y));
		float left = fminf(fminf(InventoryCorners[0].X, InventoryCorners[1].X), fminf(InventoryCorners[2].X, InventoryCorners[3].X));
		float right = fmaxf(fmaxf(InventoryCorners[0].X, InventoryCorners[1].X), fmaxf(InventoryCorners[2].X, InventoryCorners[3].X));

		Bounds = FVector4(top, bottom, left, right);
	}
}

void ABaseInventory::Interact(ABasePlayer* _player) {
	Super::Interact(_player);

	AMoveableObject* heldObject =  _player->GetHeldObject();
	AddItemToInventory(heldObject);

	if (AddItemToInventory(heldObject)) { _player->PickupObject(nullptr); }
}

void ABaseInventory::SetTargetability(ABasePlayer* _player, bool _targetability) {
	targetable = _player->IsHoldingObject();
}