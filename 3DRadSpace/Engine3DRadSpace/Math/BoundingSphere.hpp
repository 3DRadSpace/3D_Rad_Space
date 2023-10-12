#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingBox;
	struct DLLEXPORT BoundingSphere
	{
		Vector3 Center;
		float Radius;

		BoundingSphere();
		BoundingSphere(Vector3 center, float radius);
		BoundingSphere(const BoundingBox& box);
		BoundingSphere(const BoundingSphere& sph1, const BoundingSphere& sph2);
		BoundingSphere(const BoundingSphere& sph, const BoundingBox& box);
		BoundingSphere(const BoundingBox& box1, const BoundingBox& box2);
	};
}