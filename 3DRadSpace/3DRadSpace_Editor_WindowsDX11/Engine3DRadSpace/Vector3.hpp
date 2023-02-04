#pragma once
#include "Libs.hpp"

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

	float Length();
};

