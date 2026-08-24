#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingBox;
	struct BoundingPlane;
	struct Ray;
	/// <summary>
	///	Represents an bounding sphere defined by a center point and a radius.
	/// </summary>
	struct E3DRSP_MATH_EXPORT BoundingSphere
	{
		/// <summary>
		/// Center of the sphere.
		/// </summary>
		Vector3 Center;
		/// <summary>
		///	Radius of the sphere.
		/// </summary>
		float Radius;

		/// <summary>
		/// Default constructor. Creates a null bounding sphere with center at (0,0,0) and radius 0.
		/// </summary>
		BoundingSphere();
		/// <summary>
		/// Creates a bounding sphere with the given center and radius.
		/// </summary>
		/// <param name="center">Center of the sphere</param>
		/// <param name="radius">Radius of the sphere</param>
		BoundingSphere(const Vector3& center, float radius);
		/// <summary>
		/// Creates a bounding sphere that contains the given bounding box.
		/// </summary>
		/// <param name="box">The bounding box to contain</param>
		explicit BoundingSphere(const BoundingBox& box);
		/// <summary>
		///	Creates a bounding sphere that contains both given bounding spheres.
		/// </summary>
		/// <param name="sph1">The first bounding sphere</param>
		/// <param name="sph2">The second bounding sphere</param>
		BoundingSphere(const BoundingSphere& sph1, const BoundingSphere& sph2);
		/// <summary>
		///	Creates a bounding sphere that contains the given bounding sphere and bounding box.
		/// </summary>
		/// <param name="sph">The bounding sphere to contain</param>
		/// <param name="box">The bounding box to contain</param>
		BoundingSphere(const BoundingSphere& sph, const BoundingBox& box);
		/// <summary>
		///	Creates a bounding sphere that contains both given bounding boxes.
		/// </summary>
		/// <param name="box1">The first bounding box</param>
		/// <param name="box2">The second bounding box</param>
		BoundingSphere(const BoundingBox& box1, const BoundingBox& box2);
		/// <summary>
		///	Determines whether this bounding sphere intersects with the given bounding box.
		/// </summary>
		/// <param name="box">The bounding box to test for intersection</param>
		/// <returns>True if the bounding sphere intersects with the bounding box, false otherwise</returns>
		bool Intersects(const BoundingBox& box) const;
		/// <summary>
		/// Determines whether this bounding sphere intersects with the given bounding sphere.
		/// </summary>
		/// <param name="sphere">The bounding sphere to test for intersection</param>
		/// <returns>True if the bounding sphere intersects with the bounding sphere, false otherwise</returns>
		bool Intersects(const BoundingSphere& sphere) const;
		/// <summary>
		/// Determines whether this bounding sphere intersects with the given bounding plane.
		/// </summary>
		/// <param name="plane">The bounding plane to test for intersection</param>
		/// <returns>True if the bounding sphere intersects with the bounding plane, false otherwise</returns>
		bool Intersects(const BoundingPlane& plane) const;
		/// <summary>
		/// Determines whether this bounding sphere intersects with the given ray.
		/// </summary>
		/// <param name="ray">The ray to test for intersection</param>
		/// <returns>True if the bounding sphere intersects with the ray, false otherwise</returns>
		bool Intersects(const Ray& ray) const;

		/// <summary>
		/// Determines whether this bounding sphere contains the given point.
		/// </summary>
		/// <param name="p">The point to test for containment</param>
		/// <returns>True if the bounding sphere contains the point, false otherwise</returns>
		bool Contains(const Vector3& p) const;
	};
}