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
		NullRenderer(IGraphicsDevice* device, RenderingManager* owner);
		void Begin() override;
		void End() override;

		~NullRenderer() override = default;
	};
}