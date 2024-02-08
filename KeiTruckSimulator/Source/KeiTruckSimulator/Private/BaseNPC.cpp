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

	SetTargetability();
	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsVector("Destination", GetActorLocation());
	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsBool("InteractingWithPlayer", false);
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
	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsBool("InteractingWithPlayer", true);

	GetController<AAIController>()->StopMovement();
		
	//GetController<AAIController>()->GetBrainComponent()->PauseLogic("Talking To Player");

	//player->DisplayDialogue(FText::FromString(FString("Test Dialogue")), this);

	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	//	{
	//		isInteractingWithPlayer = false;
	//		GetController<AAIController>()->GetBlackboardComponent()->SetValueAsBool("InteractingWithPlayer", false);
	//		//GetController<AAIController>()->GetBrainComponent()->ResumeLogic("Finished Talking To Player");
	//	}, 3, false);

	
}

void ABaseNPC::SetInteractability(bool _interactability, FVector playerPos) {
	
}

void ABaseNPC::SpeakToPlayer(FText dialogue) {
	player->DisplayDialogue(dialogue, this);
}

void ABaseNPC::DisplayDialogueOptions(TArray<FString> dialogueOptions) {
	player->DisplayDialogueOptions(dialogueOptions);
}

void ABaseNPC::StopSpeakingToPlayer() {
	isInteractingWithPlayer = false;
	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsBool("InteractingWithPlayer", false);

	player->CloseDialogue();
}

void ABaseNPC::PlayerSelectsOption(int _playerSelection) {
	playersSelectedOption = _playerSelection;

	waitingForPlayerSelection = false;

	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsInt("PlayersSelection", _playerSelection);
	FAIMessage::Send(this, FAIMessage(FName("PlayerChose"), nullptr, true));
}
