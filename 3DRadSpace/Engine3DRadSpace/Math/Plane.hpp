#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	/// Represents a plane with the equation p(x,y,z) = Normal.X * x + Normal.Y * y + Normal.Z * z + D = 0
	struct Plane
	{
		Vector3 Normal;
		float D;
	};
}