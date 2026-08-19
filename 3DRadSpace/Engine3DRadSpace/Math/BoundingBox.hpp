#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingSphere;
	struct BoundingPlane;
	struct Ray;
	struct Matrix4x4;
	struct E3DRSP_MATH_EXPORT BoundingBox
	{
		Vector3 Position;
		Vector3 Scale;

		/// <summary>
		/// Creates a null bounding box.
		/// </summary>
		BoundingBox() = default;
		/// <summary>
		/// Creates a bounding box from position and scale.
		/// </summary>
		/// <param name="pos">Position.</param>
		/// <param name="scale">Scale. Every coordinate should be positive.</param>
		BoundingBox(const Vector3& pos, const Vector3& scale);
		/// <summary>
		/// Create a bounding box that contains the given bounding sphere.
		/// </summary>
		/// <param name="sphere">Bounding sphere</param>
		BoundingBox(const BoundingSphere& sphere);
		/// <summary>
		/// Creates a bounding box that contains both given bounding boxes.
		/// </summary>
		/// <param name="box1">First</param>
		/// <param name="box2">Second</param>
		BoundingBox(const BoundingBox& box1, const BoundingBox& box2);
		/// <summary>
		/// Creates a bounding box that contains the given bounding box and bounding sphere.
		/// </summary>
		/// <param name="box">Box.</param>
		/// <param name="sphere">Sphere.</param>
		BoundingBox(const BoundingBox& box, const BoundingSphere& sphere);
		/// <summary>
		/// Creates a bounding box that contains both given bounding spheres.
		/// </summary>
		/// <param name="sph1">Sphere.</param>
		/// <param name="sph2">Sphere.</param>
		BoundingBox(const BoundingSphere& sph1,const BoundingSphere& sph2);

		/// <summary>
		/// Minimal point.
		/// </summary>
		/// <returns>Returns Position</returns>
		Vector3 Min() const noexcept;
		/// <summary>
		/// Returns the center of the bounding box.
		/// </summary>
		/// <returns>Position + (Scale / 2).</returns>
		Vector3 Center() const noexcept;
		/// <summary>
		/// Returns the maximal point.
		/// </summary>
		/// <returns> Position + Scale.</returns>
		Vector3 Max() const noexcept;

		bool Intersects(const BoundingBox& box) const noexcept;
		bool Intersects(const BoundingSphere& sphere) const noexcept;
		bool Intersects(const BoundingPlane& plane) const noexcept;
		bool Intersects(const Ray& ray) const noexcept;

		/// <summary>
		/// Is p inside this bounding box?
		/// </summary>
		/// <param name="p">Point p</param>
		/// <returns>True if p is inside this BoundingBox. false otherwise.</returns>
		bool Contains(const Vector3& p) const noexcept;

		/// <summary>
		/// Returns a corner of this BoundingBox.
		/// </summary>
		/// <param name="i">Ranged from 0 to 7.</param>
		/// <returns>A corner of this BoundingBox.</returns>
		/// <remarks>
		/// 0: Min
		/// 1: (Max.X, Min.Y, Min.Z)
		/// 2: (Min.X, Max.Y, Min.Z)
		/// 3: (Min.X, Min.Y, Max.Z)
		/// 4: (Max.X, Max.Y, Min.Z)
		/// 5: (Max.X, Min.Y, Max.Z)
		/// 6: (Min.X, Max.Y, Max.Z)
		/// 7: Max
		/// </remarks>
		Vector3 operator[](int i) const;

		/// <summary>
		/// Returns the smallest axis-aligned BoundingBox that contains this BoundingBox after being transformed by m.
		/// </summary>
		/// <param name="m">Transformation matrix (translation, rotation and/or scale).</param>
		/// <returns>A new, axis-aligned BoundingBox that fully contains the transformed box.</returns>
		/// <remarks>
		/// Unlike transforming Position and Scale directly, this correctly accounts for rotation
		/// by re-deriving the axis-aligned extents from the transformed center/half-extents,
		/// guaranteeing the result always contains every corner of the original box.
		/// </remarks>
		BoundingBox Transform(const Matrix4x4& m) const noexcept;
	};
}