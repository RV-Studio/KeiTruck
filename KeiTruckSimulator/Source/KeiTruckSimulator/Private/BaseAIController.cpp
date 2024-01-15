// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController() {
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	Config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Config"));

	Config->DetectionByAffiliation.bDetectEnemies = false;
	Config->DetectionByAffiliation.bDetectNeutrals = true;
	Config->DetectionByAffiliation.bDetectFriendlies = false;

	AIPerception->ConfigureSense(*Config);

	TargetKey = "Target";

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::HandleTargetPerceptionUpdated);
}

void ABaseAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	RunBehaviorTree(BTAsset);
}

void ABaseAIController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed()) {
		Blackboard->SetValueAsObject(TargetKey, Actor);
	}
	else {
		Blackboard->ClearValue(TargetKey);
	}
}