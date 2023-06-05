#include "RasterizerState.hpp"
#include "../Logging/Error.hpp"
#include "../GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

RasterizerState::RasterizerState(
	GraphicsDevice* device,
	RasterizerFillMode filling, 
	RasterizerCullMode culling, 
	bool switchFrontBack, 
	int depthBias, 
	float depthBiasClamp, 
	float slopeScaleDepthBias, 
	bool depthClip,
	bool scissor,
	bool multisample,
	bool aaLine) 
{
#ifdef _DX11
	D3D11_RASTERIZER_DESC desc{};
	desc.FillMode = static_cast<D3D11_FILL_MODE>(filling); //TODO: prefer using a switch case
	desc.CullMode = static_cast<D3D11_CULL_MODE>(culling);
	desc.FrontCounterClockwise = switchFrontBack;
	desc.DepthBias = depthBias;
	desc.DepthBiasClamp = depthBiasClamp;
	desc.SlopeScaledDepthBias = slopeScaleDepthBias;
	desc.DepthClipEnable = depthClip;
	desc.ScissorEnable = scissor;
	desc.MultisampleEnable = multisample;
	desc.AntialiasedLineEnable = aaLine;

	HRESULT r = device->_device->CreateRasterizerState(&desc, _rasterizerState.ReleaseAndGetAddressOf());
	if (FAILED(r)) Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a rasterizer state object");
#endif
}