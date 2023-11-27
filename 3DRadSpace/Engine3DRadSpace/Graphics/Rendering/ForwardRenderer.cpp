#include "ForwardRenderer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Graphics::Shaders;

ForwardRenderer::ForwardRenderer(GraphicsDevice* device, const std::shared_ptr<Effect>& pipeline):
	IRenderer(device)
{
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	_device->SetRenderTargetAndDepth(nullptr, nullptr);
	for(auto& effect : _effects)
	{
		effect->Apply();
	}
}

void ForwardRenderer::End()
{
	_beginCalled = false;
}
