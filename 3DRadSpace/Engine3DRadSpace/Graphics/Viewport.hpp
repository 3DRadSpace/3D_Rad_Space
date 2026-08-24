#pragma once

#include "../Math/Rectangle.hpp"
#include "../Math/Matrix4x4.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a screen viewport for rendering.
	/// </summary>
	struct E3DRSP_GRAPHICS_EXPORT Viewport
	{
		Viewport() = default;
		Viewport(Math::RectangleF r, float mind, float maxd) : ScreenRectangle(r), MinDepth(mind), MaxDepth(maxd) {};

		/// <summary>
		///	Screen coordinates of this viewport.
		/// </summary>
		Math::RectangleF ScreenRectangle;

		/// <summary>
		///	Minimal depth value of this viewport. Default is 0.0f.
		/// </summary>
		float MinDepth = 0.0f;
		/// <summary>
		///	Maximum depth value of this viewport. Default is 1.0f.
		/// </summary>
		float MaxDepth = 1.0f;

		/// <summary>
		/// Unprojects a screen space point to world space using the given projection, view and world matrices.
		/// </summary>
		/// <param name="source">The screen space point to unproject.</param>
		/// <param name="projection">The projection matrix.</param>
		/// <param name="view">The view matrix.</param>
		/// <param name="world">The world matrix.</param>
		/// <returns>The unprojected world space point.</returns>
		Math::Vector3 Unproject(const Math::Vector3& source, const Math::Matrix4x4& projection, const Math::Matrix4x4& view, const Math::Matrix4x4& world) const;
	};
}