#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the shader feature level.
	/// </summary>
	enum class ShaderFeatureLevel : char
	{
		/// <summary>
		/// DirectX feature level 4.0
		/// </summary>
		DX_V4,
		/// <summary>
		/// DirectX feature level 4.1
		/// </summary>
		DX_V4_1,
		/// <summary>
		/// DirectX feature level 5.0
		/// </summary>
		DX_V5,
		/// <summary>
		/// DirectX feature level 6.0
		/// </summary>
		DX_V6,
	};
}