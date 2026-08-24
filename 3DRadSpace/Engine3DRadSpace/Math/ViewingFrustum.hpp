#pragma once
#include "Matrix4x4.hpp"
#include "BoundingPlane.hpp"

namespace Engine3DRadSpace::Math
{
	struct BoundingSphere;
	struct BoundingBox;
	struct BoundingPlane;
	struct Ray;

	/// <summary>
	/// Represents a viewing frustum
	/// </summary>
	class E3DRSP_MATH_EXPORT ViewingFrustum
	{
	public:
		/// <summary>
		/// Constructs an viewing frustum from the given view and projection matrices.
		/// </summary>
		/// <param name="view">View matrix.</param>
		/// <param name="projection">Projection matrix.</param>
		ViewingFrustum(const Matrix4x4& view, const Matrix4x4& projection);

		/// <summary>
		/// Returns the plane representing the top of the frustum.
		/// </summary>
		/// <returns>The top plane of the frustum.</returns>
		BoundingPlane Top();
		/// <summary>
		/// Returns the plane representing the bottom of the frustum.
		/// </summary>
		/// <returns>The bottom plane of the frustum.</returns>
		BoundingPlane Bottom();
		/// <summary>
		/// Returns the plane representing the left side of the frustum.
		/// </summary>
		/// <returns>The left plane of the frustum.</returns>
		BoundingPlane Left();
		/// <summary>
		/// Returns the plane representing the right side of the frustum.
		/// </summary>
		/// <returns>The right plane of the frustum.</returns>
		BoundingPlane Right();
		/// <summary>
		/// Returns the plane representing the near side of the frustum.
		/// </summary>
		/// <returns>The near plane of the frustum.</returns>
		BoundingPlane Near();
		/// <summary>
		/// Returns the plane representing the far side of the frustum.
		/// </summary>
		/// <returns>The far plane of the frustum.</returns>
		BoundingPlane Far();
		/// <summary>
		/// Returns the corners of the frustum in world space.
		/// </summary>
		/// <returns>An array containing the eight corners of the frustum.</returns>
		std::array<Vector3, 8> Corners();

		/// <summary>
		/// Does this frustum contain the given point?
		/// </summary>
		/// <param name="point">The point to test.</param>
		/// <returns>True if the frustum contains the point, false otherwise.</returns>
		bool Contains(const Vector3& point);
		/// <summary>
		/// Does this frustum contain the given bounding sphere?
		/// </summary>
		/// <param name="sphere">The bounding sphere to test.</param>
		/// <returns>True if the frustum contains the bounding sphere, false otherwise.</returns>
		bool Contains(const BoundingSphere& sphere);
		/// <summary>
		/// Does this frustum contain the given bounding box?
		/// </summary>
		/// <param name="box">The bounding box to test.</param>
		/// <returns>True if the frustum contains the bounding box, false otherwise.</returns>
		bool Contains(const BoundingBox& box);
		/// <summary>
		/// Does this frustum contain the given bounding plane?
		/// </summary>
		/// <param name="plane">The bounding plane to test.</param>
		/// <returns>True if the frustum contains the bounding plane, false otherwise.</returns>
		bool Contains(const BoundingPlane& plane);
		/// <summary>
		/// Does this frustum contain the given frustum?
		/// </summary>
		/// <param name="frustum">The frustum to test.</param>
		/// <returns>True if the frustum contains the other frustum, false otherwise.</returns>
		bool Contains(const ViewingFrustum& frustum);
		/// <summary>
		///	Does this frustum intersect with the given ray?
		/// </summary>
		/// <param name="ray">The ray to test.</param>
		/// <returns>The distance at which the ray intersects the frustum, or a negative value if there is no intersection.</returns>
		float Intersects(const Ray& ray);

	private:
		BoundingPlane _planes[6];
		std::array<Vector3, 8> _corners;
	};
}