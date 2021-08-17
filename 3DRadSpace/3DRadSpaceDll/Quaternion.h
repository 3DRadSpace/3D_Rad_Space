#pragma once
#include "Globals.h"

struct DLLEXPORT Quaternion
{
	float X, Y, Z, W;

	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {};

	static Quaternion Identity();
};

