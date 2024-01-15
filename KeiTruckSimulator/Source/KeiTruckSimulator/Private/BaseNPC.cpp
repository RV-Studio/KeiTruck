// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPC.h"
#include <BrainComponent.h>
#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseNPC::ABaseNPC() {
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AIClass;
}


void ABaseNPC::BeginPlay() {
	Super::BeginPlay();
}

void ABaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}