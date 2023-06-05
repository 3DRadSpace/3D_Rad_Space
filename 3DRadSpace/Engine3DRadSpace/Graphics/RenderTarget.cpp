#include "RenderTarget.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace::Logging;

Engine3DRadSpace::Graphics::RenderTarget::RenderTarget(GraphicsDevice *device) :
	Texture2D(device, true)
{
#ifdef _DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}

Engine3DRadSpace::Graphics::RenderTarget::RenderTarget(GraphicsDevice *device, unsigned x, unsigned y):
	Texture2D(device, x, y, true)
{
#ifdef _DX11
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
#endif
}
