#include "PickingRenderTargetRender.hpp"

using namespace Engine3DRadSpace::Algorithms::Picking;

PickingRenderTargetRender::PickingRenderTargetRender(GraphicsDevice* device) :
	IRenderer(device),
	_renderTarget(std::make_unique<Graphics::RenderTarget>(device, Graphics::PixelFormat::R32_SignedInt)),
	_shader(Content::ShaderManager::LoadShader<PickingShader>(device)),
	_depthBuffer(std::make_unique<Graphics::DepthStencilBuffer>(device))
{
}

void PickingRenderTargetRender::Begin()
{
	if (_isDrawing)
	{
		_device->SetRenderTargetAndDepth(_renderTarget.get(), _depthBuffer.get());
		_device->Clear();
		_isDrawing = false;
	}
	else throw std::exception("Begin() already called.");
}

void PickingRenderTargetRender::End()
{
	_isDrawing = false;
	_device->SetRenderTargetAndDepth(nullptr, nullptr);
}

std::optional<unsigned> Engine3DRadSpace::Algorithms::Picking::PickingRenderTargetRender::Pick(const Math::Point& mouseCoords)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;

	auto renderTarget = static_cast<ID3D11Texture2D*>(_renderTarget->RenderTargetHandle());

	HRESULT r = _device->_context->Map(renderTarget, 0, D3D11_MAP_READ, 0, &mappedSubresource);
	if (FAILED(r)) throw Logging::Exception("Failed to map the ID texture!");

	unsigned ID = *static_cast<int*>(mappedSubresource.pData) + (mouseCoords.Y * _renderTarget->Width()) + mouseCoords.X;

	_device->_context->Unmap(renderTarget, 0);

	if (ID != 0) return ID + 1;
	return std::nullopt;
#endif
}