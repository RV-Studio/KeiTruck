// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

void IInteractableInterface::SetTargetability(class ABasePlayer* _player, bool _targetability) {
	targetable = _targetability;
}

bool IInteractableInterface::IsTargetable() {
	return targetable;
}
