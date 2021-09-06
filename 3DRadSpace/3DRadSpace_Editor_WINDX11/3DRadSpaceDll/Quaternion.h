#pragma once
#include "Globals.h"

struct DLLEXPORT Quaternion
{
	float X, Y, Z, W;

	Quaternion() : X(0), Y(0), Z(0), W(1) {};
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {};

};

