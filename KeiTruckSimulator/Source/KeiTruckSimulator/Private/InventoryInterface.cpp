// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryInterface.h"
#include "MoveableObject.h"

// Add default functionality here for any IInventoryInterface functions that are not pure virtual.

bool IInventoryInterface::AddItemToInventory(AMoveableObject* itemToAdd) {
	TArray<AMoveableObject*> hypotheticalInventory = TArray<AMoveableObject*>(ItemsInInventory);
	hypotheticalInventory.Add(itemToAdd);

	TArray<CCOA> successfulCCOAs;
	if (SortItems(hypotheticalInventory, successfulCCOAs)) {
		ItemsInInventory = hypotheticalInventory;
		for (int i = 0; i < successfulCCOAs.Num(); ++i) {
			CCOA currCCOA = successfulCCOAs[i];
			currCCOA.object->PlaceObject(FVector(currCCOA.x, currCCOA.y, 0), currCCOA.theta, this);
		}
		return true;
	}
	return false;
}

bool IInventoryInterface::RemoveItemFromIventory(AMoveableObject* itemToRemove) {
	ItemsInInventory.Remove(itemToRemove);
	TArray<CCOA> successfulCCOAs;
	SortItems(ItemsInInventory, successfulCCOAs);
	for (int i = 0; i < successfulCCOAs.Num(); ++i) {
		CCOA currCCOA = successfulCCOAs[i];
		currCCOA.object->PlaceObject(FVector(currCCOA.x, currCCOA.y, 0), currCCOA.theta, this);
	}
	return true;
}

TArray<IInventoryInterface::CCOA> IInventoryInterface::GenerateCCOAs(TArray<FVector> corners, TArray<AMoveableObject*> remainingItems, TArray<CCOA> sortedItems) {
	TArray<CCOA> CCOAs = TArray<CCOA>();
	for (int i = 0; i < corners.Num(); ++i) {
		for (int j = 0; j < remainingItems.Num(); ++j) {
			float theta = 0;
			//top right
			float newX = corners[i].X + (remainingItems[j]->GetDimensions().X / 2);
			float newY = corners[i].X + (remainingItems[j]->GetDimensions().Y / 2);
			CCOA newCCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
			//bottom right
			newX = corners[i].X + (remainingItems[j]->GetDimensions().X / 2);
			newY = corners[i].X - (remainingItems[j]->GetDimensions().Y / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
			//top left
			newX = corners[i].X - (remainingItems[j]->GetDimensions().X / 2);
			newY = corners[i].X + (remainingItems[j]->GetDimensions().Y / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
			//bottom left
			newX = corners[i].X - (remainingItems[j]->GetDimensions().X / 2);
			newY = corners[i].X - (remainingItems[j]->GetDimensions().Y / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }

			//rotate 90 degrees
			theta = 90;
			//top right
			newX = corners[i].X + (remainingItems[j]->GetDimensions().Y / 2);
			newY = corners[i].X + (remainingItems[j]->GetDimensions().X / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
			//bottom right
			newX = corners[i].X + (remainingItems[j]->GetDimensions().Y / 2);
			newY = corners[i].X - (remainingItems[j]->GetDimensions().X / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
			//top left
			newX = corners[i].X - (remainingItems[j]->GetDimensions().Y / 2);
			newY = corners[i].X + (remainingItems[j]->GetDimensions().X / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
			//bottom left
			newX = corners[i].X - (remainingItems[j]->GetDimensions().Y / 2);
			newY = corners[i].X - (remainingItems[j]->GetDimensions().X / 2);
			newCCOA = CCOA(remainingItems[j], newX, newY, theta);
			if (ValidateCCOA(newCCOA, sortedItems)) { CCOAs.Add(newCCOA); }
		}
	}
	return CCOAs;
}

bool IInventoryInterface::ValidateCCOA(CCOA _CCOA, TArray<CCOA> sortedItems) {
	FVector2f aTopLeft;
	FVector2f aBottomRight;
	if (_CCOA.theta == 0) {
		aTopLeft = FVector2f(_CCOA.object->GetMaxBounds().Z + _CCOA.x, _CCOA.object->GetMaxBounds().X + _CCOA.y);
		aBottomRight = FVector2f(_CCOA.object->GetMaxBounds().W + _CCOA.x, _CCOA.object->GetMaxBounds().Y + _CCOA.y);
	}
	else {
		aTopLeft = FVector2f(_CCOA.object->GetMaxBounds().Y + _CCOA.x, _CCOA.object->GetMaxBounds().Z + _CCOA.y);
		aBottomRight = FVector2f(_CCOA.object->GetMaxBounds().X + _CCOA.x, _CCOA.object->GetMaxBounds().W + _CCOA.y);
	}
	

	FVector2f bTopLeft;
	FVector2f bBottomRight;

	CCOA currentCCOA = sortedItems[0];
	for (int i = 0; i < sortedItems.Num(); ++i) {
		currentCCOA = sortedItems[i];
		if (currentCCOA.theta == 0) {
			bTopLeft = FVector2f(currentCCOA.object->GetMaxBounds().Z + currentCCOA.x, currentCCOA.object->GetMaxBounds().X + currentCCOA.y);
			bBottomRight = FVector2f(currentCCOA.object->GetMaxBounds().W + currentCCOA.x, currentCCOA.object->GetMaxBounds().Y + currentCCOA.y);
		}
		else {
			bTopLeft = FVector2f(currentCCOA.object->GetMaxBounds().Y + currentCCOA.x, currentCCOA.object->GetMaxBounds().Z + currentCCOA.y);
			bBottomRight = FVector2f(currentCCOA.object->GetMaxBounds().X + currentCCOA.x, currentCCOA.object->GetMaxBounds().W + currentCCOA.y);
		}

		if (aTopLeft.X > bBottomRight.X || bTopLeft.X > aBottomRight.X) { continue; }
		if (aBottomRight.Y > bTopLeft.Y || bBottomRight.Y > aTopLeft.Y) { continue; }

		return false;
	}

	//Check overlap on walls
	if (aTopLeft.X < Bounds.Z || aTopLeft.Y > Bounds.X || aBottomRight.X > Bounds.W || aBottomRight.Y < Bounds.Y) { return false; }

	return true;
}

float IInventoryInterface::CalculateCCOADegree(CCOA _CCOA, TArray<CCOA> sortedItems) {
	int zeroCounter = 2;
	float dMin = std::numeric_limits<float>::max();
	float currentMin;
	for (int i = 0; i < sortedItems.Num(); ++i) {
		currentMin = CalculateMinDistance(_CCOA, sortedItems[i]);
		if (currentMin == 0 && zeroCounter != 0) { continue; }
		else if (currentMin < dMin) { dMin = currentMin; }
	}

	FVector objectDimensions = _CCOA.object->GetDimensions();
	return 1 - (dMin / ((objectDimensions.X + objectDimensions.Y) / 2));
}

float IInventoryInterface::CalculateMinDistance(CCOA obj_a, CCOA obj_b) {
	FVector4 obj_a_bounds = obj_a.object->GetMaxBounds();
	obj_a_bounds.X += obj_a.y;
	obj_a_bounds.Y += obj_a.y;
	obj_a_bounds.Z += obj_a.x;
	obj_a_bounds.W += obj_a.x;
	if (obj_a.theta == 90) {
		float temp = obj_a_bounds.W;
		obj_a_bounds.W = obj_a_bounds.X;
		obj_a_bounds.X = obj_a_bounds.Z;
		obj_a_bounds.Z = obj_a_bounds.Y;
		obj_a_bounds.Z = temp;
	}
	FVector4 obj_b_bounds = obj_b.object->GetMaxBounds();
	obj_b_bounds.X += obj_b.y;
	obj_b_bounds.Y += obj_b.y;
	obj_b_bounds.Z += obj_b.x;
	obj_b_bounds.W += obj_b.x;
	if (obj_b.theta == 90) {
		float temp = obj_b_bounds.W;
		obj_b_bounds.W = obj_b_bounds.X;
		obj_b_bounds.X = obj_b_bounds.Z;
		obj_b_bounds.Z = obj_b_bounds.Y;
		obj_b_bounds.Z = temp;
	}

	float outerHeight = fmaxf(obj_a_bounds.X, obj_a_bounds.X) - fminf(obj_a_bounds.Y, obj_a_bounds.Y);
	float outerWidth = fmaxf(obj_a_bounds.W, obj_a_bounds.W) - fminf(obj_a_bounds.Z, obj_a_bounds.Z);

	float innerWidth = fmaxf(0, outerWidth - (obj_a_bounds.W - obj_a_bounds.Z) - (obj_b_bounds.W - obj_b_bounds.Z));
	float innerHeight = fmaxf(0, outerHeight - (obj_a_bounds.X - obj_a_bounds.Y) - (obj_b_bounds.X - obj_b_bounds.Y));

	return sqrtf((innerWidth * innerWidth) + (innerHeight * innerHeight));
}

bool IInventoryInterface::SortItems(TArray<AMoveableObject*> itemsToSort, TArray<CCOA>& successfulCCOAs) {
	TArray<AMoveableObject*> remainingItems = TArray<AMoveableObject*>(itemsToSort);

	TArray<CCOA> CCOAs = TArray<CCOA>();
	TArray<CCOA> PlacedCCOAs = TArray<CCOA>();
	TArray<FVector> corners = TArray<FVector>();
	float highestDegree = 0;
	CCOA bestCCOA = CCOA(nullptr, 0, 0, 0);
	float returnedDegree;

	corners.Append(InventoryCorners);
	while (!remainingItems.IsEmpty()) {
		CCOAs = GenerateCCOAs(corners, remainingItems, PlacedCCOAs);
		if (CCOAs.IsEmpty()) { return false; }

		for (int i = 0; i < CCOAs.Num(); ++i) {
			returnedDegree = CalculateCCOADegree(CCOAs[i], PlacedCCOAs);
			if (returnedDegree > highestDegree) { 
				highestDegree = returnedDegree; 
				bestCCOA = CCOAs[i];
			}
		}
		// Log the CCOA with the highest degree
		PlacedCCOAs.Add(bestCCOA);
		TArray<FVector> cornersToAdd = bestCCOA.object->GetCorners();
		for (int i = 0; i < cornersToAdd.Num(); ++i) {
			cornersToAdd[i].X += bestCCOA.x;
			cornersToAdd[i].Y += bestCCOA.y;
		}
		corners.Append(cornersToAdd);

		// Remove the corresponding item from remaining
		remainingItems.Remove(bestCCOA.object);

	}
	successfulCCOAs = PlacedCCOAs; 
	return true;
}