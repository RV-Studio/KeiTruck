// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
static class KEITRUCKSIMULATOR_API MathLibrary
{
public:
	static FVector Cross(FVector v1, FVector v2);

	static float Dot(FVector v1, FVector v2);

	static FVector Normalize(FVector v);

	static float Square(float _val);

	static float Clamp(float _val, float _min, float _max);

	static FMatrix XRotMatrix(float rotAmount);

	static FMatrix YRotMatrix(float rotAmount);

	static FMatrix ZRotMatrix(float rotAmount);

	static FMatrix LookAt(FVector eye, FVector center);

	static FMatrix TurnTo(FMatrix matrix, FVector target, float turnSpeed);

	static FMatrix Orthonormalize(FMatrix matrix, FVector up);

	static float FInpterpTo(float _current, float _target, float _deltaTime, float _interpSpeed);

protected:
};
