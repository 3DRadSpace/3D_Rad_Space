#pragma once
#include "Vector3.h"
#include "Triangle.h"

struct RayResult
{
	bool Hit;
	float Distance;
};

struct Ray
{
	Vector3 Origin;
	Vector3 Direction;

	Ray() : Origin({ 0,0,0 }), Direction({ 0,0,1 }) {}; // I assume +Z is forward
	Ray(const Vector3& center, const Vector3& dir) : Origin(center), Direction(dir) {};

	RayResult Intersects(const Triangle& triangle);
};

