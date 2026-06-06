#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingBox;
	struct BoundingPlane;
	struct Ray;
	struct E3DRSP_MATH_EXPORT BoundingSphere
	{
		Vector3 Center;
		float Radius;

		BoundingSphere();
		BoundingSphere(const Vector3& center, float radius);
		BoundingSphere(const BoundingBox& box);
		BoundingSphere(const BoundingSphere& sph1, const BoundingSphere& sph2);
		BoundingSphere(const BoundingSphere& sph, const BoundingBox& box);
		BoundingSphere(const BoundingBox& box1, const BoundingBox& box2);

		bool Intersects(const BoundingBox& box) const;
		bool Intersects(const BoundingSphere& sphere) const;
		bool Intersects(const BoundingPlane& plane) const;
		bool Intersects(const Ray& ray) const;

		bool Contains(const Vector3& p) const;
	};
}