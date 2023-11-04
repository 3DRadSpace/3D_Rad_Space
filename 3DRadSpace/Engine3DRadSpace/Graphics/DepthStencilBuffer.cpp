#include "DepthStencilBuffer.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void DepthStencilBuffer::_createDepthTexture()
{
#ifdef  USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Format = DXGI_FORMAT_R32_TYPELESS;
	desc.ArraySize = 1;
	desc.Width = _device->_resolution.X;
	desc.Height = _device->_resolution.Y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, _depthTexture.GetAddressOf());
	if(FAILED(r)) throw Exception("Failed to create the depth texture!");

	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	r = _device->_device->CreateDepthStencilView(_depthTexture.Get(), &viewDesc, &_depthView); //the & operator release the previous stencil view object
	if (FAILED(r)) throw Exception("Failed to create the depth stencil view!");

#ifdef _DEBUG
	const char depthTextureName[] = "DepthStencilBuffer::_depthTexture";
	_depthTexture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(depthTextureName) - 1, depthTextureName);

	const char depthViewName[] = "DepthStencilBuffer::_depthView";
	_depthView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(depthViewName) - 1, depthViewName);
#endif // _DEBUG

#endif //  USING_DX11
}

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice *device):
	_device(device)
{
	_createDepthTexture();
}