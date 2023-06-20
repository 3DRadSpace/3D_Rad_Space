#include "SamplerState.hpp"
#include "../Logging/Error.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

SamplerState::SamplerState(GraphicsDevice* device)
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

	HRESULT r = device->_device->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a sampler state with default values!");
#endif
}

SamplerState::SamplerState(GraphicsDevice *device, TextureFilter Filter, TextureAddressMode AddressU, TextureAddressMode AddressV, TextureAddressMode AddressW, float MipLODBias, unsigned MaxAnisotropy, ComparisonFunction ComparisionFunction, Color BorderColor, float MinLOD, float MaxLOD)
{
#ifdef _DX11
	D3D11_SAMPLER_DESC desc{};
	
	switch(Filter)
	{
		case TextureFilter::Anisotropic:
			desc.Filter = D3D11_FILTER_ANISOTROPIC;
			break;
		case TextureFilter::Linear:
			desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case TextureFilter::LinearMipPoint:
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			break;
		case TextureFilter::MinLinearMagPointMipLinear:
			desc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			break;
		case TextureFilter::MinPointMagLinearMipLinear:
			desc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
			break;
		case TextureFilter::MinPointMagLinearMipPoint:
			desc.Filter = D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
			break;
		case TextureFilter::Point:
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
			break;
		case TextureFilter::PointMipLinear:
			desc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
			break;
		default:
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			break;
	}
	
	auto convert_3drsp_addressmode_dx_address_mode = [](TextureAddressMode address)
	{
		switch(address)
		{
			case TextureAddressMode::Wrap:
				return D3D11_TEXTURE_ADDRESS_WRAP;
			case TextureAddressMode::Mirror:
				return D3D11_TEXTURE_ADDRESS_MIRROR;
			case TextureAddressMode::Clamp:
				return D3D11_TEXTURE_ADDRESS_CLAMP;
			case TextureAddressMode::Border:
				return D3D11_TEXTURE_ADDRESS_BORDER;
			case TextureAddressMode::MirrorOnce:
				return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
			default:
				throw std::invalid_argument("TextureAddressMode is invalid/unknown!");
		}
	};

	desc.AddressU = convert_3drsp_addressmode_dx_address_mode(AddressU);
	desc.AddressV = convert_3drsp_addressmode_dx_address_mode(AddressV);
	desc.AddressW = convert_3drsp_addressmode_dx_address_mode(AddressW);
	desc.MipLODBias = MipLODBias;
	desc.MaxAnisotropy = MaxAnisotropy;

	switch(ComparisionFunction)
	{
		case ComparisonFunction::Never:
			desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			break;
		case ComparisonFunction::Less:
			desc.ComparisonFunc = D3D11_COMPARISON_LESS;
			break;
		case ComparisonFunction::Equal:
			desc.ComparisonFunc = D3D11_COMPARISON_EQUAL;
			break;
		case ComparisonFunction::LessEqual:
			desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
			break;
		case ComparisonFunction::Greater:
			desc.ComparisonFunc = D3D11_COMPARISON_GREATER;
			break;
		case ComparisonFunction::NotEqual:
			desc.ComparisonFunc = D3D11_COMPARISON_NOT_EQUAL;
			break;
		case ComparisonFunction::GreaterEqual:
			desc.ComparisonFunc = D3D11_COMPARISON_GREATER_EQUAL;
			break;
		case ComparisonFunction::Always:
			desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			break;
		default:
			throw std::invalid_argument("Unknown/invalid comparison function!");
	}

	desc.BorderColor[0] = BorderColor.R;
	desc.BorderColor[1] = BorderColor.G;
	desc.BorderColor[2] = BorderColor.B;
	desc.BorderColor[3] = BorderColor.A;

	desc.MinLOD = MinLOD;
	desc.MaxLOD = MaxLOD;

	HRESULT r = device->_device->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a sampler state with default values!");
#endif
}

SamplerState SamplerState::LinearClamp(GraphicsDevice* device)
{
	return SamplerState(
		device, 
		TextureFilter::Linear, 
		TextureAddressMode::Clamp,
		TextureAddressMode::Clamp,
		TextureAddressMode::Clamp,
		0.0f,
		0u,
		ComparisonFunction::Never,
		Color(0,0,0,0),
		0.0f,
		std::numeric_limits<float>::max()
	);
}

SamplerState SamplerState::LinearWrap(GraphicsDevice *device)
{
	return SamplerState(
		device,
		TextureFilter::Linear,
		TextureAddressMode::Wrap,
		TextureAddressMode::Wrap,
		TextureAddressMode::Wrap,
		0.0f,
		0u,
		ComparisonFunction::Never,
		Color(0,0,0,0),
		0.0f,
		std::numeric_limits<float>::max()
	);
}

SamplerState Engine3DRadSpace::Graphics::SamplerState::PointClamp(GraphicsDevice *device)
{
	return SamplerState(
		device,
		TextureFilter::Point,
		TextureAddressMode::Clamp, 
		TextureAddressMode::Clamp, 
		TextureAddressMode::Clamp, 
		0.0f,
		0u,
		ComparisonFunction::Never,
		Color(0,0,0,0),
		0.0f,
		std::numeric_limits<float>::max()
	);
}

SamplerState Engine3DRadSpace::Graphics::SamplerState::PointWrap(GraphicsDevice *device)
{
	return SamplerState(
		device,
		TextureFilter::Point,
		TextureAddressMode::Wrap,
		TextureAddressMode::Wrap,
		TextureAddressMode::Wrap,
		0.0f,
		0u,
		ComparisonFunction::Never,
		Color(0, 0, 0, 0),
		0.0f,
		std::numeric_limits<float>::max()
	);
}

SamplerState Engine3DRadSpace::Graphics::SamplerState::AnisotropicClamp(GraphicsDevice *device)
{
	return SamplerState(
		device,
		TextureFilter::Anisotropic,
		TextureAddressMode::Clamp,
		TextureAddressMode::Clamp,
		TextureAddressMode::Clamp,
		0.0f,
		16u,
		ComparisonFunction::Never,
		Color(0,0,0,0),
		0.0f,
		std::numeric_limits<float>::max()
	);
}

SamplerState Engine3DRadSpace::Graphics::SamplerState::AnisotropicWrap(GraphicsDevice *device)
{
	return SamplerState(
		device,
		TextureFilter::Anisotropic,
		TextureAddressMode::Wrap,
		TextureAddressMode::Wrap,
		TextureAddressMode::Wrap,
		0.0f,
		16u,
		ComparisonFunction::Never,
		Color(0, 0, 0, 0),
		0.0f,
		std::numeric_limits<float>::max()
	);
}
