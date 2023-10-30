// Fill out your copyright notice in the Description page of Project Settings.


#include "EventDispatcherHolder.h"

// Sets default values
AEventDispatcherHolder::AEventDispatcherHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventDispatcherHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEventDispatcherHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

