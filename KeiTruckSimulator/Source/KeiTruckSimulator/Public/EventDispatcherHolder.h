// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventDispatcherHolder.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcherInteractable, UObject*, InteractableObject);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEventDispatcherDisplayDialogue, FText, DialogueToDisplay, class ABaseNPC*, NPCTalking);

UCLASS()
class KEITRUCKSIMULATOR_API AEventDispatcherHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventDispatcherHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
