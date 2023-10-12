#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingSphere;
	struct DLLEXPORT BoundingBox
	{
		Vector3 Position;
		Vector3 Scale;

		BoundingBox() = default;
		BoundingBox(const Vector3& pos, const Vector3& scale);
		BoundingBox(const BoundingSphere& sphere);
		BoundingBox(const BoundingBox& box1, const BoundingBox& box2);
		BoundingBox(const BoundingBox& box, const BoundingSphere& sphere);
		BoundingBox(const BoundingSphere& sph1, BoundingSphere& sph2);

		Vector3 Center() const;
	};
}