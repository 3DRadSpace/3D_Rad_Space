#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct Quaternion
	{
		float X, Y, Z, W;

		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : X(x), Y(y), Z(z), W(w) {};
	};
}

