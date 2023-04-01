#include "pch.h"
#include <Engine3DRadSpace/Vector3.hpp>

using namespace Engine3DRadSpace::Math;

TEST(LinearAlgebraTests,Vector)
{
	//Basic cross product test:
	Vector3 a = Vector3::UnitX(), b = Vector3::UnitY();
	EXPECT_EQ(Vector3::Cross(a, b),Vector3::UnitZ());
	
}