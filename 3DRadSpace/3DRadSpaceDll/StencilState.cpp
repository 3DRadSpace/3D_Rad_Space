#include "StencilState.h"

#ifdef __DIRECTXVER
StencilState::StencilState(Game* g)
{
	_stencilview = nullptr;

	ID3D11Device* device = g->GetDevice();

	D3D11_TEXTURE2D_DESC stencilTextureDesc;
	memset(&stencilTextureDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	stencilTextureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	stencilTextureDesc.ArraySize = 1;
	stencilTextureDesc.MipLevels = 1;
	stencilTextureDesc.SampleDesc.Count = 1;
	stencilTextureDesc.SampleDesc.Quality = 0;
	stencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	stencilTextureDesc.Width = g->GetResolution().X;
	stencilTextureDesc.Height = g->GetResolution().Y;

	HRESULT r = device->CreateTexture2D(&stencilTextureDesc, nullptr, &this->_stenciltexture);
	if (FAILED(r)) throw std::exception("Failed to create the Stencil State texture");

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	memset(&depthStencilDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	r = device->CreateDepthStencilState(&depthStencilDesc, &this->_stencilstate);
	if (FAILED(r)) throw std::runtime_error("Failed to create the Depth Stencil State");

	D3D11_DEPTH_STENCIL_VIEW_DESC stencilViewDesc;
	memset(&stencilViewDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	stencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMS;
	stencilViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	stencilViewDesc.Texture2D.MipSlice = 0;

	r = device->CreateDepthStencilView(_stenciltexture, &stencilViewDesc, &this->_stencilview);
	if (FAILED(r)) throw std::runtime_error("Failed to create the Depth Stencil View");
}

ID3D11DepthStencilView* StencilState::GetStencilView()
{
	return this->_stencilview;
}

ID3D11DepthStencilState* StencilState::GetStencilState()
{
	return this->_stencilstate;
}

StencilState::~StencilState()
{
	if(this->_stenciltexture != nullptr) this->_stenciltexture->Release();
	if(this->_stencilstate != nullptr) this->_stencilstate->Release();
	if(this->_stencilview != nullptr) this->_stencilview->Release();

	this->_stenciltexture = nullptr;
	this->_stencilstate = nullptr;
	this->_stencilview = nullptr;
}
#endif