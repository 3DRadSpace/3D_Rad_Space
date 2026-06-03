#include "ShadowMapRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

ShadowMapRenderer::ShadowMapRenderer(IGraphicsDevice* device) : IRenderer(device)
{
	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	_shadowMap = _device->CreateDepthStencilBuffer(shadowMapWidth, shadowMapHeight);
}

void ShadowMapRenderer::Begin()
{
	auto context = _device->ImmediateContext();
	
	context->UnbindRenderTargetAndDepth();
	context->SetDepthStencilBuffer(_shadowMap.get());
}

void ShadowMapRenderer::End()
{
	// End rendering to shadow map
}