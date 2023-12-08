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

	static FVector Normalize(FVector v);

	static float Square(float _val);

	static float Clamp(float _val, float _min, float _max);

	static FRotator LookAt(FVector eye, FVector center);

	static float FInpterpTo(float _current, float _target, float _deltaTime, float _interpSpeed);
};
