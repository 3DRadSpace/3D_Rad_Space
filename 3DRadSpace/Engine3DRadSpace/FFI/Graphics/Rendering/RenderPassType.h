#pragma once

typedef enum E3DRSP_RenderPassType
{
	/// <summary>
	/// Mesh is not rendered at all.
	/// </summary>
	E3DRSP_RenderPassType_Hidden,
	/// <summary>
	/// Mesh is rendered with opaque materials and shadows.
	/// </summary>
	E3DRSP_RenderPassType_Opaque,
	/// <summary>
	///	Mesh is opaque but does not cast shadows.
	/// </summary>
	E3DRSP_RenderPassType_OpaqueNoShadow,
	/// <summary>
	/// Mesh is transparent and it casts shadows.
	/// </summary>
	E3DRSP_RenderPassType_Transparent,
	/// <summary>
	///	Mesh is transparent but it doesn't cast shadows.
	/// </summary>
	E3DRSP_RenderPassType_TransparentNoShadow,
	/// <summary>
	/// Mesh only emits a shadow, but it is invisible in the color passes.
	/// </summary>
	E3DRSP_RenderPassType_ShadowMap,
	/// <summary>
	/// Mesh is rendered in a depth pre-pass, which is used for optimizing rendering of complex scenes.
	/// </summary>
	E3DRSP_RenderPassType_DepthPrePass,
	/// <summary>
	/// Unspecified render pass type.
	/// </summary>
	E3DRSP_RenderPassType_Custom
} E3DRSP_RenderPassType;