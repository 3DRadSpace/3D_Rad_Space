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
		explicit NullRenderer(RenderingManager* owner);
		void Begin() override;
		void Draw(ModelMeshPart* part, const MaterialDescriptor* materialDescriptor = 0) override;
		void End() override;

		bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept override;

		~NullRenderer() override = default;
	};
}