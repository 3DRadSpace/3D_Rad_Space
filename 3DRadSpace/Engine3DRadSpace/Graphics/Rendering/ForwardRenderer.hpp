#pragma once
#include "IRenderPass.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// A trivial forward renderer.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ForwardRenderer : public IRenderPass
	{
		bool _beginCalled = false;
	public:
		/// <summary>
		/// Constructs a forward renderer pipeline.
		/// </summary>
		/// <param name="device"></param>
		ForwardRenderer(IGraphicsDevice* device);

		/// <summary>
		/// Begins drawing.
		/// </summary>
		void Begin() override;
		/// <summary>
		/// Ends drawing.
		/// </summary>
		void End() override;

		~ForwardRenderer() override = default;
	};
}