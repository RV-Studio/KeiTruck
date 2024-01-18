// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_WaitForPlayerResponse.h"
#include "BaseNPC.h"
#include <BehaviorTree/BTFunctionLibrary.h>

UTask_WaitForPlayerResponse::UTask_WaitForPlayerResponse() {
	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

void UTask_WaitForPlayerResponse::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	ABaseNPC* NPC = Cast<ABaseNPC>(ControlledPawn);
	if (NPC) {
		NPC->DisplayDialogueOptions(PlayerOptions);
		NPC->waitingForPlayerSelection = true;
	}

	SetFinishOnMessage("PlayerChose");
}