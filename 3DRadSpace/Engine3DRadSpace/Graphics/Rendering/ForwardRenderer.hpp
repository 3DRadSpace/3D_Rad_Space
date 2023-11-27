#pragma once
#include "IRenderer.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class ForwardRenderer final : public IRenderer
	{
		bool _beginCalled = false;
	public:
		ForwardRenderer(GraphicsDevice* device, const std::shared_ptr<Shaders::Effect>& pipeline);

		void Begin() override;
		void End() override;
	};
}