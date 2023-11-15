#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Ray;
	/// Represents a plane with the equation p(x,y,z) = Normal.X * x + Normal.Y * y + Normal.Z * z + D
	struct Plane
	{
		Vector3 Normal;
		float D;

		bool Intersects(const BoundingBox& box) const;
		bool Intersects(const BoundingSphere& sphere) const;
		bool Intersects(const Ray& ray) const;

		bool Contains(const Vector3& p) const;
	};
}