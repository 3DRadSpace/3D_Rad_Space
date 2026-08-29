#pragma once
#include "IRenderer.hpp"
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// A trivial forward renderer. (currently doesn't support instanced rendering).
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ForwardRenderer : public IRenderer
	{
		bool _beginCalled = false;

		Effect* _trivialEffect = nullptr;
		Effect* _shadowEffect = nullptr;

		void _loadBasicShader();
		void _loadShadowShader();
	public:
		/// <summary>
		/// Constructs a forward renderer pipeline.
		/// </summary>
		/// <param name="owner">The rendering manager that owns this renderer.</param>
		explicit ForwardRenderer(RenderingManager* owner);

		/// <summary>
		/// Begins drawing.
		/// </summary>
		void Begin() override;

		void Draw(const MeshPartDrawInfo& part) override;

		/// <summary>
		/// Ends drawing.
		/// </summary>
		void End() override;
		
		/// <summary>
		/// Determines whether the specified render pass type is supported by this renderer.
		/// </summary>
		/// <param name="passType">The render pass type to check.</param>
		/// <returns>True if the render pass type is supported; otherwise, false.</returns>
		bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept override;

		~ForwardRenderer() override = default;
	};
}