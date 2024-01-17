// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_EndDialogue.h"
#include "BaseNPC.h"

UTask_EndDialogue::UTask_EndDialogue() {
	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

void UTask_EndDialogue::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	ABaseNPC* NPC = Cast<ABaseNPC>(ControlledPawn);
	if (NPC) {
		NPC->StopSpeakingToPlayer();
	}


	FinishExecute(true);

}