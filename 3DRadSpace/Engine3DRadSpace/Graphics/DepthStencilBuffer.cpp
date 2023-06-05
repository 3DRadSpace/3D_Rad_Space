#include "DepthStencilBuffer.hpp"
#include "../Logging/Error.hpp"
using namespace Engine3DRadSpace::Logging;

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice *device):
	_device(device)
{
#ifdef WIN32
	D3D11_TEXTURE2D_DESC desc{};
	desc.Format = DXGI_FORMAT_R32_TYPELESS;
	desc.ArraySize = 1;
	desc.Width = device->_resolution.X;
	desc.Height = device->_resolution.Y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _depthTexture.GetAddressOf());
	RaiseFatalErrorIfFailed(r, "Failed to create the depth texture!");
	
	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	r = device->_device->CreateDepthStencilView(_depthTexture.Get(), &viewDesc, &_depthView); //the & operator release the previous stencil view object
	RaiseFatalErrorIfFailed(r, "Failed to create the depth stencil view!");

	D3D11_DEPTH_STENCIL_DESC dsDesc;

	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	r = device->_device->CreateDepthStencilState(&dsDesc, _stencilState.GetAddressOf());
	RaiseFatalErrorIfFailed(r, "Failed to create a depth stencil state with default settings");
#endif
}

Engine3DRadSpace::Graphics::DepthStencilBuffer::DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept:
	_device(buff._device),
	_depthTexture(buff._depthTexture),
	_depthView(buff._depthView),
	_stencilState(buff._stencilState)
{
	buff._depthTexture.Reset();
	buff._depthView.Reset();
	buff._stencilState.Reset();
}

DepthStencilBuffer &Engine3DRadSpace::Graphics::DepthStencilBuffer::operator=(DepthStencilBuffer &&buff) noexcept
{
	_depthTexture.Reset();
	_depthView.Reset();
	_stencilState.Reset();

	_depthTexture = buff._depthTexture;
	_depthView = buff._depthView;
	_stencilState = buff._stencilState;

	return *this;
}
