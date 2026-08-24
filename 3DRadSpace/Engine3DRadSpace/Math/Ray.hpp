#pragma once
#include "BoundingSphere.hpp"
#include "Triangle.hpp"
#include "BoundingBox.hpp"
#include "BoundingPlane.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents an ray in 3D space, defined by an origin and direction vector.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Ray
	{
		/// <summary>
		/// Origin in world space.
		/// </summary>
		Vector3 Origin;
		/// <summary>
		///	Direction vector. Must be normalized.
		/// </summary>
		Vector3 Direction;

		/// <summary>
		/// Checks if this ray intersects with the given bounding sphere.
		/// </summary>
		/// <param name="sph">Bounding sphere.</param>
		/// <returns>Closest intersection point.</returns>
		/// <remarks>
		/// this.Direction but must be normalized.
		/// </remarks>
		float Intersects(const BoundingSphere &sph) const;
		/// <summary>
		/// Checks if this ray intersects the given triangle using the Möller–Trumbore intersection algorithm.
		/// </summary>
		/// <param name="tri">Triangle to test for intersection.</param>
		/// <returns>Closest intersection point.</returns>
		float Intersects(const Triangle &tri) const;
		/// <summary>
		///	Checks if this ray intersects with the given bounding box.
		/// </summary>
		/// <param name="box">Bounding box to test for intersection.</param>
		/// <returns>Closest intersection point.</returns>
		float Intersects(const BoundingBox &box) const;
		/// <summary>
		///	Checks if this ray intersects with the given bounding plane.
		/// </summary>
		/// <param name="plane">Bounding plane to test for intersection.</param>
		/// <returns>Closest intersection point.</returns>
		float Intersects(const BoundingPlane& plane) const;
	};
}