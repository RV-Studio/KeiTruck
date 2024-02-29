// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Persistence", meta = (DisplayName = "Get Savegame Manager", Keywords = "SavegameManager"))
	UGameManager* GameManager();


protected:
	virtual void Shutdown() override;

private:
	UPROPERTY(Transient)
	UGameManager* GameManagerInstance;
};
