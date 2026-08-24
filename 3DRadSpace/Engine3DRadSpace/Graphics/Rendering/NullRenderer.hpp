#pragma once
#include "IRenderer.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// A renderer that does nothing. Useful for testing.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT NullRenderer : public IRenderer
	{
	public:
		/// <summary>
		/// Constructs a null renderer pipeline.
		/// </summary>
		explicit NullRenderer(RenderingManager* owner);
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Begin() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="part">unused</param>
		/// <param name="materialDescriptor">unused</param>
		void Draw(ModelMeshPart* part, const MaterialDescriptor* materialDescriptor = 0) override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void End() override;

		/// <summary>
		/// Returns false for all possible types.
		/// </summary>
		/// <param name="passType">The render pass type to check.</param>
		/// <returns>False for all possible types.</returns>
		bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept override;

		~NullRenderer() override = default;
	};
}