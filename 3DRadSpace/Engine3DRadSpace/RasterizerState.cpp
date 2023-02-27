#include "RasterizerState.hpp"
#include "Error.hpp"
#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;

Engine3DRadSpace::RasterizerState::RasterizerState(
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
	:
	FillMode(filling),
	CullMode(culling),
	FrontCounterClockwise(switchFrontBack),
	DepthBias(depthBias),
	DepthBiasClamp(depthBiasClamp),
	SlopeScaledDepthBias(slopeScaleDepthBias),
	DepthClip(depthClip),
	Scissors(scissor),
	Multisample(multisample),
	AntialiasedLines(aaLine)
{
	D3D11_RASTERIZER_DESC desc{};
	desc.FillMode = static_cast<D3D11_FILL_MODE>(this->FillMode);
	desc.CullMode = static_cast<D3D11_CULL_MODE>(this->CullMode);
	desc.FrontCounterClockwise = this->FrontCounterClockwise;
	desc.DepthBias = this->DepthBias;
	desc.DepthBiasClamp = this->DepthBiasClamp;
	desc.SlopeScaledDepthBias = this->SlopeScaledDepthBias;
	desc.DepthClipEnable = this->DepthClip;
	desc.ScissorEnable = this->Scissors;
	desc.MultisampleEnable = this->Multisample;
	desc.AntialiasedLineEnable = this->AntialiasedLines;

	HRESULT r = device->device->CreateRasterizerState(&desc, this->rasterizerState.ReleaseAndGetAddressOf());
	if (FAILED(r)) Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create a rasterizer state object");
}