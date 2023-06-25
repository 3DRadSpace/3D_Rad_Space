#pragma once
#include "Sphere.hpp"
#include "Triangle.hpp"

namespace Engine3DRadSpace::Math
{
	struct Ray
	{
		Vector3 Origin;
		Vector3 Direction;

		std::optional<float> Intersects(const Sphere &sph);
		std::optional<float> Intersects(const Triangle &tri);
	};
}