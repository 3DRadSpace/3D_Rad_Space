#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents a triangle made up of three points in 3D space.
	/// </summary>
	struct Triangle
	{
		/// <summary>
		/// The first point of the triangle.
		/// </summary>
		Vector3 PointA;
		/// <summary>
		/// The second point of the triangle.
		/// </summary>
		Vector3 PointB;
		/// <summary>
		/// The third point of the triangle.
		/// </summary>
		Vector3 PointC;
	};
}