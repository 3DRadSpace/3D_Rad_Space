#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingBox;
	struct Plane;
	struct Ray;
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

		bool Intersects(const BoundingBox& box) const;
		bool Intersects(const BoundingSphere& sphere) const;
		bool Intersects(const Plane& plane) const;
		bool Intersects(const Ray& ray) const;

		bool Contains(const Vector3& p) const;
	};
}