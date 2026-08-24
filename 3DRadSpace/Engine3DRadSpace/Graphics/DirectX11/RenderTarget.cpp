#include "RenderTarget.hpp"
#include "../Logging/Exception.hpp"
#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Internal;

RenderTarget::RenderTarget(
	GraphicsDevice* device,
	Microsoft::WRL::ComPtr<ID3D11Texture2D>&& backbuffer,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& srv,
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>&& rtv
) : Texture2D(device, std::move(backbuffer), std::move(srv)),
	_renderTarget(std::move(rtv))
{
}

RenderTarget::RenderTarget(GraphicsDevice *device, PixelFormat format) :
	Texture2D(device, std::monostate{}, true, format)
{
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
}

RenderTarget::RenderTarget(GraphicsDevice *device, size_t x, size_t y, PixelFormat format):
	Texture2D(device, x, y, true, format)
{
	HRESULT r = device->_device->CreateRenderTargetView(_texture.Get(), nullptr, _renderTarget.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create a render target!");
}

RenderTarget::RenderTarget(GraphicsDevice* device, std::monostate cpy) :
	Texture2D(device) //create a invalid texture
{
	(void)cpy;

	device->_context->OMGetRenderTargets(1, &_renderTarget, nullptr);

	ID3D11Resource* res;
	_renderTarget->GetResource(&res);

	HRESULT r = res->QueryInterface<ID3D11Texture2D>(&_texture);
	if(FAILED(r)) throw Exception("Failed to get the texture from the render target!");
}

void* RenderTarget::RenderTargetHandle() const noexcept
{
	return _renderTarget.Get();
}
