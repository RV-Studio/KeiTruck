// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "GameManager.h"

UGameManager* UMyGameInstance::GameManager()
{
	return
		IsValid(GameManagerInstance) ?
		GameManagerInstance :
		GameManagerInstance = NewObject<UGameManager>(
			this,
			FName("GameManager"));
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	if (IsValid(GameManagerInstance))
	{

	}
}