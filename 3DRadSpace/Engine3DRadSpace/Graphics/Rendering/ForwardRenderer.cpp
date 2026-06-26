#include "ForwardRenderer.hpp"
#include "../IGraphicsDevice.hpp"
#include "../IGraphicsCommandList.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

ForwardRenderer::ForwardRenderer(IGraphicsDevice* device):
	IRenderPass(device)
{
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	_device->ImmediateContext()->SetRenderTargetAndDepth(nullptr, nullptr);
}

void ForwardRenderer::End()
{
	_beginCalled = false;
}
