// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseAIController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAIPerceptionComponent* AIPerception;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TargetKey;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* BTAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAISenseConfig_Sight* Config;

	void OnPossess(APawn* InPawn);

	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
