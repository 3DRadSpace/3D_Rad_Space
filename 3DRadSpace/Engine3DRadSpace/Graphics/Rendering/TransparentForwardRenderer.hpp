#pragma once
#include "ForwardRenderer.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// A forward renderer that supports transparency.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT TransparentForwardRenderer : public ForwardRenderer
	{
	public:
		/// <summary>
		/// Constructs a transparent forward renderer pipeline.
		/// </summary>
		/// <param name="owner">The rendering manager that owns this renderer.</param>
		TransparentForwardRenderer(RenderingManager* owner);

		bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept override;

		~TransparentForwardRenderer() override = default;
	};
}