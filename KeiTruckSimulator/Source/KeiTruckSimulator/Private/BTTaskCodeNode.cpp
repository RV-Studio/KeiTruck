// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskCodeNode.h"
#include "AIController.h"

void UBTTaskCodeNode::SetOwner(AActor* InActorOwner)
{
	ActorOwner = InActorOwner;
	AIOwner = Cast<AAIController>(InActorOwner);
}

void UBTTaskCodeNode::SetFinishOnMessage(FName MessageName)
{
	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
	if (OwnerComp)
	{
		OwnerComp->RegisterMessageObserver(this, MessageName);
	}
}

void UBTTaskCodeNode::FinishExecute(bool bSuccess)
{
	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
	EBTNodeResult::Type NodeResult(bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);

	if (bStoreFinishResult)
	{
		CurrentCallResult = NodeResult;
	}
	else if (OwnerComp)
	{
		FinishLatentTask(*OwnerComp, NodeResult);
	}
}

EBTNodeResult::Type UBTTaskCodeNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// fail when task doesn't react to execution (start or tick)
	CurrentCallResult = EBTNodeResult::InProgress;

	bStoreFinishResult = true;

	ReceiveExecuteAI(AIOwner, AIOwner->GetPawn());

	bStoreFinishResult = false;

	return CurrentCallResult;
}

void UBTTaskCodeNode::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {

}