#include "RenderTarget.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace::Logging;

Engine3DRadSpace::Graphics::RenderTarget::RenderTarget(GraphicsDevice *device, PixelFormat format) :
	Texture2D(device, true, format)
{
#ifdef _DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}

Engine3DRadSpace::Graphics::RenderTarget::RenderTarget(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format):
	Texture2D(device, x, y, true, format)
{
#ifdef _DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}
