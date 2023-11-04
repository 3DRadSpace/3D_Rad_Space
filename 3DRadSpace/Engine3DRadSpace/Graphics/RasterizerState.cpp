#include "RasterizerState.hpp"
#include "../Logging/Exception.hpp"
#include "../GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

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
#ifdef USING_DX11
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
	if (FAILED(r)) throw Exception("Failed to create a rasterizer state object");

#ifdef _DEBUG
	const char rasterizerStateName[] = "RasterizerState::_rasterizerState";
	_rasterizerState->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(rasterizerStateName) - 1, rasterizerStateName);
#endif
#endif
}

RasterizerState Engine3DRadSpace::Graphics::RasterizerState::CullNone(GraphicsDevice *device)
{
	// https://github.com/microsoft/DirectXTK/wiki/CommonStates
	return RasterizerState(device, 
		RasterizerFillMode::Solid, 
		RasterizerCullMode::None,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState Engine3DRadSpace::Graphics::RasterizerState::CullClockwise(GraphicsDevice *device)
{
	return RasterizerState(device,
		RasterizerFillMode::Solid,
		RasterizerCullMode::CullFront,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState Engine3DRadSpace::Graphics::RasterizerState::CullCounterClockwise(GraphicsDevice *device)
{
	return RasterizerState(device,
		RasterizerFillMode::Solid,
		RasterizerCullMode::CullBack,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState Engine3DRadSpace::Graphics::RasterizerState::Wireframe(GraphicsDevice *device)
{
	return RasterizerState(device,
		RasterizerFillMode::Wireframe,
		RasterizerCullMode::None,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}
