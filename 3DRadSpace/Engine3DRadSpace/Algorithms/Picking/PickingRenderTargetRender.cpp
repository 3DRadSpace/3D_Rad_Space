#include "PickingRenderTargetRender.hpp"

Engine3DRadSpace::Algorithms::Picking::PickingRenderTargetRender::PickingRenderTargetRender(GraphicsDevice* device) :
	_device(device),
	_renderTarget(std::make_unique<Graphics::RenderTarget>(device, Graphics::PixelFormat::R32_SignedInt)),
	_shader(Content::ShaderManager::LoadShader<PickingShader>(device)),
	_depthBuffer(std::make_unique<Graphics::DepthStencilBuffer>(device))
{
}