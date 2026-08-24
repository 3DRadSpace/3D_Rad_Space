#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Texture filter used in a sampler state
	/// </summary>
	enum class TextureFilter : unsigned char
	{
		/// <summary>
		///	Anisotropic filtering. The maximum anisotropy is determined by the graphics device.
		/// </summary>
		Anisotropic,
		/// <summary>
		/// Linear filtering. The texture is sampled using linear interpolation between the nearest texels.
		/// </summary>
		Linear,
		/// <summary>
		/// Point filtering. The texture is sampled using the nearest texel.
		/// </summary>
		LinearMipPoint,
		/// <summary>
		/// Linear filtering with mipmaps. The texture is sampled using linear interpolation between the nearest texels and mipmaps.
		/// </summary>
		MinLinearMagPointMipLinear,
		/// <summary>
		/// Linear filtering with mipmaps. The texture is sampled using linear interpolation between the nearest texels and mipmaps.
		/// </summary>
		MinLinearMagPointMipPoint,
		/// <summary>
		/// Linear filtering with mipmaps. The texture is sampled using linear interpolation between the nearest texels and mipmaps.
		/// </summary>
		MinPointMagLinearMipLinear,
		/// <summary>
		/// Linear filtering with mipmaps. The texture is sampled using linear interpolation between the nearest texels and mipmaps.
		/// </summary>
		MinPointMagLinearMipPoint,
		/// <summary>
		/// Point filtering. The texture is sampled using the nearest texel.
		/// </summary>
		Point,
		/// <summary>
		/// Linear filtering with mipmaps. The texture is sampled using linear interpolation between the nearest texels and mipmaps.
		/// </summary>
		PointMipLinear
	};
}