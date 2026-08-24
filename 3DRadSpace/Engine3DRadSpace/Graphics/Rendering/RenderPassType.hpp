#pragma once

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Render pass type.
	/// </summary>
	enum class RenderPassType : uint8_t
	{
		/// <summary>
		/// Mesh is not rendered at all.
		/// </summary>
		Hidden,
		/// <summary>
		/// Mesh is rendered with opaque materials and shadows.
		/// </summary>
		Opaque,
		/// <summary>
		///	Mesh is opaque but does not cast shadows.
		/// </summary>
		OpaqueNoShadow,
		/// <summary>
		/// Mesh is transparent and it casts shadows.
		/// </summary>
		Transparent,
		/// <summary>
		///	Mesh is transparent but it doesn't cast shadows.
		/// </summary>
		TransparentNoShadow,
		/// <summary>
		/// Mesh only emits a shadow, but it is invisible in the color passes.
		/// </summary>
		ShadowMap,
		/// <summary>
		/// Mesh is rendered in a depth pre-pass, which is used for optimizing rendering of complex scenes.
		/// </summary>
		DepthPrePass,
		/// <summary>
		/// Unspecified render pass type.
		/// </summary>
		Custom
	};
}