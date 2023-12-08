// Fill out your copyright notice in the Description page of Project Settings.


#include "MathLibrary.h"

FVector MathLibrary::Cross(FVector v1, FVector v2) {
	float x = (v1.Y * v2.Z) - (v1.Z * v2.Y);
	float y = (v1.Z * v2.X) - (v1.X * v2.Z);
	float z = (v1.X * v2.Y) - (v1.Y * v2.X);
	return FVector(x, y, z);
}

FVector MathLibrary::Normalize(FVector v) {
	float length = sqrtf((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z));
	float x = v.X / length;
	float y = v.Y / length;
	float z = v.Z / length;
	return FVector(x, y, z);
}

float MathLibrary::Square(float _val) {
	return _val * _val;
}

float MathLibrary::Clamp(float _val, float _min, float _max) {
	if (_val <= _min) return _min;
	else if (_val >= _max) return _max;
	else return _val;
}

FRotator MathLibrary::LookAt(FVector eye, FVector center) {
	FVector X = Normalize(center - eye);
	FVector Y = Normalize(Cross(FVector(0, 0, 1), X));
	FVector Z = Normalize(Cross(X, Y));

	FMatrix RotMatrix(X, Y, Z, FVector::ZeroVector);

	return RotMatrix.Rotator();
}

float MathLibrary::FInpterpTo(float _current, float _target, float _deltaTime, float _interpSpeed) {
	// If no interp speed, jump to target value
	if (_interpSpeed <= 0.f)
	{
		return _target;
	}

	// Distance to reach
	float dist = _target - _current;

	// If distance is too small, just set the desired location
	if (Square(dist) < UE_SMALL_NUMBER)
	{
		return _target;
	}

	// Delta Move, Clamp so we do not over shoot.
	float deltaMove = dist * Clamp(_deltaTime * _interpSpeed, 0.f, 1.f);

	return _current + deltaMove;
}
