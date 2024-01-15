// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskCodeNode.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UBTTaskCodeNode : public UBTTaskNode
{
	GENERATED_BODY()

	virtual void SetOwner(AActor* ActorOwner) override;


protected:
	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	AAIController* AIOwner;

	/** Cached actor owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	AActor* ActorOwner;

	/** temporary variable for ReceiveExecute(Abort)-FinishExecute(Abort) chain */
	mutable TEnumAsByte<EBTNodeResult::Type> CurrentCallResult;

	/** if set, execution is inside blueprint's ReceiveExecute(Abort) event
	  * FinishExecute(Abort) function should store their result in CurrentCallResult variable */
	mutable uint32 bStoreFinishResult : 1;

	void FinishExecute(bool bSuccess);

	void SetFinishOnMessage(FName MessageName);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	virtual void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
};
