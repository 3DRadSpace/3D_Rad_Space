#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

		static Vector3 Zero();
		static Vector3 UnitX();
		static Vector3 UnitY();
		static Vector3 UnitZ();

		float Length();
	};
}
