// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPC.h"
#include <BrainComponent.h>
#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MathLibrary.h"
#include "BasePlayer.h"

ABaseNPC::ABaseNPC() {
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AIClass;
}


void ABaseNPC::BeginPlay() {
	Super::BeginPlay();
}

void ABaseNPC::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (isInteractingWithPlayer) {
		SetActorRotation(MathLibrary::TurnTo(GetTransform().ToMatrixWithScale(), player->GetActorLocation(), 5).Rotator());
	}
}

void ABaseNPC::Interact(ABasePlayer* _player) {
	player = _player;

	GetController<AAIController>()->GetBrainComponent()->PauseLogic("Talking To Player");

	//SetActorRotation(MathLibrary::TurnTo(GetTransform().ToMatrixWithScale(), _player->GetActorLocation(), 5).Rotator());
}

void ABaseNPC::SetInteractability(bool _interactability, FVector playerPos) {
	
}
