// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_SpeakDialogue.h"
#include "BaseNPC.h"

UTask_SpeakDialogue::UTask_SpeakDialogue() {
	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

void UTask_SpeakDialogue::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	ABaseNPC* NPC = Cast<ABaseNPC>(ControlledPawn);
	if (NPC) {
		NPC->SpeakToPlayer(Dialogue);
	}


	FinishExecute(true);

}