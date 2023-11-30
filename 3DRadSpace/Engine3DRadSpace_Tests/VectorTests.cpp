#include "pch.h"
#include <Engine3DRadSpace/Math/Vector3.hpp>

using namespace Engine3DRadSpace::Math;

TEST(LinearAlgebraTests,Vector)
{
	//Basic cross product test:
	Vector3 a = Vector3::UnitX(), b = Vector3::UnitY();
	Vector3 unitZ = Vector3::UnitZ();

	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).X, unitZ.X);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Y, unitZ.Y);
	EXPECT_FLOAT_EQ(Vector3::Cross(a, b).Z, unitZ.Z);
}