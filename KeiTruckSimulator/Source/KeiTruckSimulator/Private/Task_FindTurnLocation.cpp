// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindTurnLocation.h"
#include <NavigationSystem.h>
#include <BehaviorTree/BTFunctionLibrary.h>
#include "AIController.h"

UTask_FindTurnLocation::UTask_FindTurnLocation() {
	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

void UTask_FindTurnLocation::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	currentTurnAmout += DegreesToTurn;
	FRotator MakeRotation(0, currentTurnAmout, 0);

	FVector Direction = FRotationMatrix(MakeRotation).GetScaledAxis(EAxis::Y);
	FNavLocation NewDestination(ControlledPawn->GetActorLocation() + (Direction * Distance));

	UBTFunctionLibrary::SetBlackboardValueAsVector(this, DestinationKey, NewDestination.Location);


	FinishExecute(true);

}
