#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;

	struct Quaternion
	{
		float X, Y, Z, W;

		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : X(x), Y(y), Z(z), W(w) {};

		constexpr static Quaternion FromYawPitchRoll(float yaw, float pitch, float roll);
		constexpr static Quaternion FromAxisAngle(const Vector3& axis, float angle);

		float Length() const;
		Quaternion Normalize();

		Vector3 Im() const;
		
		Vector3 ToYawPitchRoll();

		Quaternion operator /(float s);
	};
}

