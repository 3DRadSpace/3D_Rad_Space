#include "SamplerState.hpp"
#include "Error.hpp"

Engine3DRadSpace::SamplerState::SamplerState(GraphicsDevice* device)
{
#ifdef _DX11
	//Default values, as described here: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-pssetsamplers
	D3D11_SAMPLER_DESC desc{}; 
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.MipLODBias = 0;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;

	desc.MinLOD = std::numeric_limits<float>::min();
	desc.MaxLOD = std::numeric_limits<float>::max();

	HRESULT r = device->device->CreateSamplerState(&desc, samplerState.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a sampler state with default values!");
#endif
}
