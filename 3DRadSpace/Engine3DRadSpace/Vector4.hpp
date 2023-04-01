#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector4
	{
		float X, Y, Z, W;

		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : X(x), Y(y), Z(z), W(w) {};
		Vector4(Vector3 v) : X(v.X), Y(v.Y), Z(v.Z), W(1) {};

		auto operator <=>(const Vector4& v) const = default;
	};
}
