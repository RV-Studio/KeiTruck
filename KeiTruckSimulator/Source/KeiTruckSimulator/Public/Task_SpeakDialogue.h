// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTaskCodeNode.h"
#include "Task_SpeakDialogue.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UTask_SpeakDialogue : public UBTTaskCodeNode
{
	GENERATED_BODY()
	
	UTask_SpeakDialogue();

protected:
	virtual void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Dialogue;
};
