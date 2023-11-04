#include "RenderTarget.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

RenderTarget::RenderTarget(GraphicsDevice *device, PixelFormat format) :
	Texture2D(device, true, format)
{
#ifdef USING_DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}

RenderTarget::RenderTarget(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format):
	Texture2D(device, x, y, true, format)
{
#ifdef USING_DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}

void* RenderTarget::RenderTargetHandle()
{
	return _renderTarget.Get();
}
