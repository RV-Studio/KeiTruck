// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KEITRUCKSIMULATOR_API IInventoryInterface
{
	GENERATED_BODY()

	struct CCOA {
		class AMoveableObject* object;
		float x, y, theta;

		CCOA(AMoveableObject* _i, float _x, float _y, float _theta) {
			object = _i;
			x = _x;
			y = _y;
			theta = _theta;
		}
	};

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	bool AddItemToInventory(AMoveableObject* itemToAdd);

	bool RemoveItemFromIventory(AMoveableObject* itemToRemove);

protected:
		TArray<CCOA> GenerateCCOAs(TArray<FVector> corners, TArray<AMoveableObject*> remainingItems, TArray<CCOA> sortedItems);
		bool ValidateCCOA(CCOA _CCOA, TArray<CCOA> sortedItems);

		float CalculateCCOADegree(CCOA _CCOA, TArray<CCOA> sortedItems);
		float CalculateMinDistance(CCOA obj_a, CCOA obj_b);

		bool SortItems(TArray<AMoveableObject*> itemsToSort, TArray<CCOA>& successfulCCOAs);

		
		TArray<AMoveableObject*> ItemsInInventory; 

		// These varialbes will be initialized in the constructor of the implementing class
		TArray<FVector> InventoryCorners;
		FVector4 Bounds; // Ordered: Top, Bottom, Left, Right

};
