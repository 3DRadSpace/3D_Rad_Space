#pragma once
#include "Vector3.hpp"
#include "Triangle.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents the result of a ray-object intersection
	/// </summary>
	struct RayResult
	{
		/// <summary>
		/// Checks if the ray has intersected a object
		/// </summary>
		bool Hit;
		/// <summary>
		/// Represents the distance from the ray to the hit point.
		/// </summary>
		float Distance;
	};

	struct Ray
	{
		/// <summary>
		/// Represents the ray origin
		/// </summary>
		Vector3 Origin;
		/// <summary>
		/// Represents the ray direction by using a unit vector
		/// </summary>
		Vector3 Direction;

		/// <summary>
		/// Constructs a ray at the center of the world heading forward
		/// </summary>
		Ray() : Origin({ 0,0,0 }), Direction({ 0,0,1 }) {}; // I assume +Z is forward
		/// <summary>
		/// Constructs a ray with the given location and direction vectors
		/// </summary>
		/// <param name="center">Ray center</param>
		/// <param name="dir">Ray direction</param>
		Ray(const Vector3& center, const Vector3& dir) : Origin(center), Direction(dir) {};

		/// <summary>
		/// Checks if an ray intersects with a triangle using Moller-Trumbore
		/// </summary>
		/// <param name="triangle">Given triangle</param>
		/// <returns></returns>
		RayResult Intersects(const Triangle& triangle);
	};
}
