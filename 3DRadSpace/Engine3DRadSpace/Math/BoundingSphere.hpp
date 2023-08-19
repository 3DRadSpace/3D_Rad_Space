#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingSphere
	{
		Vector3 Center;
		float Radius;

		BoundingSphere() = default;
		BoundingSphere(Vector3 center, float radius);
	};
}