#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Ray;
	/// <summary>
	/// Represents a plane with the equation p(x,y,z) = Normal.X * x + Normal.Y * y + Normal.Z * z + D
	/// </summary>
	struct E3DRSP_MATH_EXPORT BoundingPlane
	{
		/// <summary>
		/// Normal vector of the plane. Should be normalized.
		/// </summary>
		Vector3 Normal;
		/// <summary>
		/// Distance from the origin.
		/// </summary>
		float D = 0;

		/// <summary>
		///	Does this plane intersect with the given bounding box?
		/// </summary>
		/// <param name="box">The bounding box to test for intersection</param>
		/// <returns>True if this plane intersects with the given bounding box, false otherwise.</returns>
		bool Intersects(const BoundingBox& box) const;
		/// <summary>
		/// Does this plane intersect with the given bounding sphere?
		/// </summary>
		/// <param name="sphere">The bounding sphere to test for intersection</param>
		bool Intersects(const BoundingSphere& sphere) const;
		/// <summary>
		/// Does this plane intersect with the given ray?
		/// </summary>
		/// <param name="ray">The ray to test for intersection</param>
		/// <returns>True if this plane intersects with the given ray, false otherwise.</returns>
		bool Intersects(const Ray& ray) const;
		
		/// <summary>
		/// Is p on this plane?
		/// </summary>
		/// <param name="p">Point p</param>
		/// <returns>True if p is on this plane, false otherwise.</returns>
		bool Contains(const Vector3& p) const;
	};
}