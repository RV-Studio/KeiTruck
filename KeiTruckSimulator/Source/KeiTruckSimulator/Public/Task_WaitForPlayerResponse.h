// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTaskCodeNode.h"
#include "Task_WaitForPlayerResponse.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UTask_WaitForPlayerResponse : public UBTTaskCodeNode
{
	GENERATED_BODY()
	
	UTask_WaitForPlayerResponse();

protected:
	virtual void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> PlayerOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FBlackboardKeySelector PlayerResponse;
};
