#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingSphere;
	struct Plane;
	struct Ray;
	struct DLLEXPORT BoundingBox
	{
		Vector3 Position;
		Vector3 Scale;

		BoundingBox() = default;
		BoundingBox(const Vector3& pos, const Vector3& scale);
		BoundingBox(const BoundingSphere& sphere);
		BoundingBox(const BoundingBox& box1, const BoundingBox& box2);
		BoundingBox(const BoundingBox& box, const BoundingSphere& sphere);
		BoundingBox(const BoundingSphere& sph1,const BoundingSphere& sph2);

		Vector3 Min() const;
		Vector3 Center() const;
		Vector3 Max() const;

		bool Intersects(const BoundingBox& box) const;
		bool Intersects(const BoundingSphere& sphere) const;
		bool Intersects(const Plane& plane) const;
		bool Intersects(const Ray& ray) const;

		bool Contains(const Vector3& p) const;

		Vector3 operator[](int i) const;
	};
}