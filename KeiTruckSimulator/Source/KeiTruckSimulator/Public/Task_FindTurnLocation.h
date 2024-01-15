// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTaskCodeNode.h"
#include "Task_FindTurnLocation.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UTask_FindTurnLocation : public UBTTaskCodeNode
{
	GENERATED_BODY()

	UTask_FindTurnLocation();

protected:
	virtual void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DegreesToTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FBlackboardKeySelector DestinationKey;
};
