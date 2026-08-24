#include "DepthStencilBuffer.hpp"
#include "../Logging/Exception.hpp"
#include "Texture2D.hpp"
#include "../Core/AssetUUIDReader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

DepthStencilBuffer::DepthStencilBuffer(
	GraphicsDevice* device,
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>&& depthView,
	Microsoft::WRL::ComPtr<ID3D11Texture2D>&& depthTexture,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& depthShaderView
) :
	_device(device),
	_depthView(std::move(depthView)),
	_depthTexture(std::make_unique<Texture2D>(_device, std::move(depthTexture), std::move(depthShaderView)))
{

}	

D3D11_TEXTURE2D_DESC DepthStencilBuffer::_defaultDepthDesc(size_t x, size_t y)
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	desc.ArraySize = 1;
	desc.Width = x;
	desc.Height = y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	return desc;
}

D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilBuffer::_defaultDepthViewDesc()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT ;
	viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	return viewDesc;
}

D3D11_SHADER_RESOURCE_VIEW_DESC DepthStencilBuffer::_defaultShaderViewDesc()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc{};
	sr_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	sr_desc.Texture2D.MostDetailedMip = 0;
	sr_desc.Texture2D.MipLevels = 1;
	return sr_desc;
}

void DepthStencilBuffer::_createDepthTexture(size_t x, size_t y)
{
	D3D11_TEXTURE2D_DESC desc = _defaultDepthDesc(x, y);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> depthView;

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, depthTexture.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth texture!");

	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc = _defaultDepthViewDesc();

	r = _device->_device->CreateDepthStencilView(depthTexture.Get(), &viewDesc, &_depthView); //the & operator release the previous stencil view object
	if (FAILED(r)) throw Exception("Failed to create the depth stencil view!");

	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc = _defaultShaderViewDesc();

	r = _device->_device->CreateShaderResourceView(depthTexture.Get(), &sr_desc, depthView.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth stencil shader resource view!");

#ifdef _DEBUG
	const char depthTextureName[] = "DepthStencilBuffer::_depthTexture";
	depthTexture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(depthTextureName) - 1, depthTextureName);

	const char depthViewName[] = "DepthStencilBuffer::_depthView";
	_depthView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(depthViewName) - 1, depthViewName);
#endif // _DEBUG

	_depthTexture.reset(new Texture2D(_device, std::move(depthTexture), std::move(depthView)));
}

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice *device):
	_device(device)
{
	auto r = _device->Resolution();
	_createDepthTexture(r.X, r.Y);
}

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* device, size_t x, size_t y) :
	_device(device)
{
	_createDepthTexture(x,y);
}

void* DepthStencilBuffer::GetDepthTextureHandle() const noexcept
{
	return _depthTexture->GetHandle();
}

ITexture2D* DepthStencilBuffer::GetDepthTexture() const noexcept
{
	return this->_depthTexture.get();
}

std::unique_ptr<ITexture2D> DepthStencilBuffer::CloneDepthTexture()
{
	Texture2D texture(_device);

	auto res = _device->Resolution();
	auto desc = _defaultDepthDesc(res.X, res.Y);
	auto viewDesc = _defaultShaderViewDesc();
	Microsoft::WRL::ComPtr<ID3D11Texture2D> newDepthTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, newDepthTexture.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth texture!");

	r = _device->_device->CreateShaderResourceView(newDepthTexture.Get(), &viewDesc, srv.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth stencil shader resource view!");

	texture._texture = std::move(newDepthTexture);
	texture._resourceView = std::move(srv);

	texture._retrieveSize();

	return std::make_unique<Texture2D>(std::move(texture));
}

void* DepthStencilBuffer::GetHandle() const noexcept
{
	return this->_depthTexture.get();
}

IGraphicsDevice* DepthStencilBuffer::GetGraphicsDevice() const noexcept
{
	return this->_device;
}