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

	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsVector("Destination", GetActorLocation());
}

void ABaseNPC::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (isInteractingWithPlayer) {
		SetActorRotation(MathLibrary::TurnTo(GetTransform().ToMatrixWithScale(), player->GetActorLocation(), turnToPlayerSpeed * DeltaTime).Rotator());
	}
}

void ABaseNPC::Interact(ABasePlayer* _player) {
	player = _player;
	isInteractingWithPlayer = true;

	GetController<AAIController>()->StopMovement();
		
	GetController<AAIController>()->GetBrainComponent()->PauseLogic("Talking To Player");

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			isInteractingWithPlayer = false;
			GetController<AAIController>()->GetBrainComponent()->ResumeLogic("Finished Talking To Player");
		}, 3, false);

	
}

void ABaseNPC::SetInteractability(bool _interactability, FVector playerPos) {
	
}
