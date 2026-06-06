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

		BoundingPlane Top();
		BoundingPlane Bottom();
		BoundingPlane Left();
		BoundingPlane Right();
		BoundingPlane Near();
		BoundingPlane Far();

		std::array<Vector3, 8> Corners();

		bool Contains(const Vector3& point);
		bool Contains(const BoundingSphere& sphere);
		bool Contains(const BoundingBox& box);
		bool Contains(const BoundingPlane& plane);
		bool Contains(const ViewingFrustum& frustum);

		float Intersects(const Ray& ray);

	private:
		BoundingPlane _planes[6];
		std::array<Vector3, 8> _corners;
	};
}