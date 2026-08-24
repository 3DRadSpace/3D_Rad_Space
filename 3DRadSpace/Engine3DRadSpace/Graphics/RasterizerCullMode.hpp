#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the cull mode used by a rasterizer state.
	/// </summary>
	enum class RasterizerCullMode : unsigned char
	{
		/// <summary>
		/// Always draw all triangles.
		/// </summary>
		None = 1,
		/// <summary>
		/// Do not draw front-facing triangles.
		/// </summary>
		CullFront = 2,
		/// <summary>
		/// Do not draw back-facing triangles.
		/// </summary>
		CullBack = 3,
	};
}