// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInventory.h"
#include "BasePlayer.h"

void ABaseInventory::Interact(ABasePlayer* _player) {
	Super::Interact(_player);

	AMoveableObject* heldObject =  _player->GetHeldObject();
}

void ABaseInventory::SetTargetability(ABasePlayer* _player, bool _targetability) {
	targetable = _player->IsHoldingObject();
}