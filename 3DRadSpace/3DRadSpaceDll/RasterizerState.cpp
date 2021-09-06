#include "RasterizerState.h"

#ifdef __DIRECTXVER

RasterizerState::RasterizerState(ID3D11Device *device)
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

	//provide default values
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;

	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = true;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	HRESULT r = device->CreateRasterizerState(&rasterizerDesc, &this->_rasterizerState);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create a RasterizerState");
	}
}

RasterizerState::RasterizerState(ID3D11Device* device,const RasterizerStateDesc& desc)
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.AntialiasedLineEnable = desc.AntialiasedLineEnable;
	rasterizerDesc.CullMode = (D3D11_CULL_MODE)desc.CullMode;
	rasterizerDesc.DepthBias = desc.DepthBias;
	rasterizerDesc.DepthBiasClamp = desc.DepthBiasClamp;
	rasterizerDesc.DepthClipEnable = desc.DepthClipEnable;
	rasterizerDesc.FillMode = (D3D11_FILL_MODE)desc.FillMode;
	rasterizerDesc.FrontCounterClockwise = desc.FrontCounterClockwise;
	rasterizerDesc.MultisampleEnable = desc.MultisampleEnable;
	rasterizerDesc.ScissorEnable = desc.ScissorEnable;
	rasterizerDesc.SlopeScaledDepthBias = desc.SlopeScaledDepthBias;

	HRESULT r = device->CreateRasterizerState(&rasterizerDesc, &this->_rasterizerState);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create a RasterizerState");
	}
}

void RasterizerState::SetRasterizerState(ID3D11DeviceContext* context)
{
	context->RSSetState(this->_rasterizerState);
}
RasterizerState::~RasterizerState()
{
	if (this->_rasterizerState != nullptr) this->_rasterizerState->Release();
}
#endif