#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Identify the portion of a depth-stencil buffer for writing depth data.
	/// </summary>
	enum class DepthWriteMask : uint8_t
	{
		/// <summary>
		/// Turn off writes to the depth-stencil buffer.
		/// </summary>
		Zero = 0,
		/// <summary>
		/// Turn on writes to the depth-stencil buffer.
		/// </summary>
		All = 1
	};
}