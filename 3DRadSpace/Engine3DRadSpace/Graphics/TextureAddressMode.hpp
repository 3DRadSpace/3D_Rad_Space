#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Texuture address mode in a sampler state.
	/// </summary>
	enum class TextureAddressMode : unsigned char
	{
		/// <summary>
		/// Wrap the texture coordinates.
		/// </summary>
		Wrap = 1,
		/// <summary>
		/// Mirror the texture coordinates.
		/// </summary>
		Mirror = 2,
		/// <summary>
		/// Clamp the texture coordinates.
		/// </summary>
		Clamp = 3,
		/// <summary>
		/// Use the border color for texture coordinates outside the [0, 1] range.
		/// </summary>
		Border = 4,
		/// <summary>
		/// Mirror the texture coordinates once and then clamp.
		/// </summary>
		MirrorOnce = 5
	};
}