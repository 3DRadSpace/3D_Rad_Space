#pragma once
#include "Matrix4x4.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents the World-View-Projection matrices.
	/// </summary>
	struct MVP
	{
		Matrix4x4 World;
		Matrix4x4 View;
		Matrix4x4 Projection;

		/// <summary>
		/// Multiplies the World, View, and Projection matrices in the order: Projection * View * World.
		/// </summary>
		/// <returns>MVP transform</returns>
		Matrix4x4 Multiply() const noexcept;
	};
}