#pragma once

struct Quaternion
{
	float X, Y, Z, W;

	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {};

	Quaternion Identity();
};

