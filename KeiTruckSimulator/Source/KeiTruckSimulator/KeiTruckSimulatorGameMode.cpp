// Copyright Epic Games, Inc. All Rights Reserved.

#include "KeiTruckSimulatorGameMode.h"
#include "KeiTruckSimulatorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKeiTruckSimulatorGameMode::AKeiTruckSimulatorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
