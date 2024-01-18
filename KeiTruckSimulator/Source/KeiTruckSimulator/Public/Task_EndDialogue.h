// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTaskCodeNode.h"
#include "Task_EndDialogue.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UTask_EndDialogue : public UBTTaskCodeNode
{
	GENERATED_BODY()

	UTask_EndDialogue();
	
protected:
	virtual void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) override;

public:
};
