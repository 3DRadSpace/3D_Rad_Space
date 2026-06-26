#pragma once
#include "IRenderPass.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// A renderer that does nothing. Useful for testing.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT NullRenderer : public IRenderPass
	{
	public:
		NullRenderer(IGraphicsDevice* device);
		void Begin() override;
		void End() override;

		~NullRenderer() override = default;
	};
}