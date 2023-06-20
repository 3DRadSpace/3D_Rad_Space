#include "BlendState.hpp"
#include "../Logging/Error.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

BlendState::BlendState(GraphicsDevice *device):
	_device(device)
{
#ifdef _DX11
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = false;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

	for(int i = 1; i < 8; i++)
		blendDesc.RenderTarget[i] = blendDesc.RenderTarget[0];

	HRESULT r = device->_device->CreateBlendState(&blendDesc, _blendState.GetAddressOf());
	RaiseFatalErrorIfFailed(r, "Failed to create a default blend state!", "");
#endif
}

D3D11_BLEND Engine3DRadSpace::Graphics::BlendState::convert3DRSPBlend_toDX11(Blend b)
{
	switch(b)
	{
		case Blend::Zero:
			return D3D11_BLEND_ZERO;

		case Blend::One:
			return D3D11_BLEND_ONE;

		case Blend::SourceColor:
			return D3D11_BLEND_SRC_COLOR;

		case Blend::InverseSourceColor:
			return D3D11_BLEND_INV_SRC_COLOR;

		case Blend::SourceAlpha:
			return D3D11_BLEND_SRC_ALPHA;

		case Blend::InverseSourceAlpha:
			return D3D11_BLEND_INV_SRC_ALPHA;

		case Blend::DestinationAlpha:
			return D3D11_BLEND_DEST_ALPHA;

		case Blend::InverseDestinationAlpha:
			return D3D11_BLEND_INV_DEST_ALPHA;

		case Blend::DestinationColor:
			return D3D11_BLEND_DEST_COLOR;

		case Blend::InverseDestinationColor:
			return D3D11_BLEND_INV_DEST_COLOR;

		case Blend::SourceAlphaSat:
			return D3D11_BLEND_SRC_ALPHA_SAT;

		case Blend::BlendFactor:
			return D3D11_BLEND_BLEND_FACTOR;

		case Blend::Source1Color:
			return D3D11_BLEND_SRC1_COLOR;

		case Blend::InverseBlendFactor:
			return D3D11_BLEND_INV_BLEND_FACTOR;

		case Blend::Source1InverseColor:
			return D3D11_BLEND_INV_SRC1_COLOR;

		case Blend::Source1Alpha:
			return D3D11_BLEND_SRC1_ALPHA;

		case Blend::InverseSource1Alpha:
			return D3D11_BLEND_INV_SRC1_ALPHA;

		default:
			return D3D11_BLEND_ZERO;
	}
}

D3D11_BLEND_OP Engine3DRadSpace::Graphics::BlendState::convert3DRSPBlendOp_toDX11(BlendOperation op)
{
	switch(op)
	{
		case BlendOperation::Add:
			return D3D11_BLEND_OP_ADD;

		case BlendOperation::Substract:
			return D3D11_BLEND_OP_SUBTRACT;

		case BlendOperation::ReverseSubstract:
			return D3D11_BLEND_OP_REV_SUBTRACT;

		case BlendOperation::Minimum:
			return D3D11_BLEND_OP_MIN;

		case BlendOperation::Maximum:
			return D3D11_BLEND_OP_MAX;

		default:
			return D3D11_BLEND_OP_ADD;
	}
}

BlendState::BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend,const RenderTargetBlendState &renderTargetBlendState):
	_device(device)
{
#ifdef _DX11
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = alphaCoverage;
	blendDesc.IndependentBlendEnable = indepedentBlend;

	blendDesc.RenderTarget[0].BlendEnable = renderTargetBlendState.EnableBlending;
	blendDesc.RenderTarget[0].BlendOp = convert3DRSPBlendOp_toDX11(renderTargetBlendState.BlendOp);
	blendDesc.RenderTarget[0].BlendOpAlpha = convert3DRSPBlendOp_toDX11(renderTargetBlendState.BlendOpAlpha);
	blendDesc.RenderTarget[0].DestBlend = convert3DRSPBlend_toDX11(renderTargetBlendState.DestinationBlend);
	blendDesc.RenderTarget[0].DestBlendAlpha = convert3DRSPBlend_toDX11(renderTargetBlendState.DestinationBlendAlpha);
	blendDesc.RenderTarget[0].RenderTargetWriteMask = convert3DRSPColorWrite_toDX11(renderTargetBlendState.WriteMask);
	blendDesc.RenderTarget[0].SrcBlend = convert3DRSPBlend_toDX11(renderTargetBlendState.SourceBlend);
	blendDesc.RenderTarget[0].SrcBlendAlpha = convert3DRSPBlend_toDX11(renderTargetBlendState.SourceBlendAlpha);

	for(int i = 1; i < 8; i++)
		blendDesc.RenderTarget[i] = blendDesc.RenderTarget[0];

	HRESULT r = device->_device->CreateBlendState(&blendDesc, _blendState.GetAddressOf());
	RaiseFatalErrorIfFailed(r, "Failed to create a default blend state!", "");
#endif
}

BlendState::BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates):
	_device(device)
{
#ifdef _DX11
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = alphaCoverage;
	blendDesc.IndependentBlendEnable = indepedentBlend;

	for(int i = 1; i < 8; i++)
	{
		blendDesc.RenderTarget[i].BlendEnable = renderTargetBlendStates[i].EnableBlending;
		blendDesc.RenderTarget[i].BlendOp = convert3DRSPBlendOp_toDX11(renderTargetBlendStates[i].BlendOp);
		blendDesc.RenderTarget[i].BlendOpAlpha = convert3DRSPBlendOp_toDX11(renderTargetBlendStates[i].BlendOpAlpha);
		blendDesc.RenderTarget[i].DestBlend = convert3DRSPBlend_toDX11(renderTargetBlendStates[i].DestinationBlend);
		blendDesc.RenderTarget[i].DestBlendAlpha = convert3DRSPBlend_toDX11(renderTargetBlendStates[i].DestinationBlendAlpha);
		blendDesc.RenderTarget[i].RenderTargetWriteMask = convert3DRSPColorWrite_toDX11(renderTargetBlendStates[i].WriteMask);
		blendDesc.RenderTarget[i].SrcBlend = convert3DRSPBlend_toDX11(renderTargetBlendStates[i].SourceBlend);
		blendDesc.RenderTarget[i].SrcBlendAlpha = convert3DRSPBlend_toDX11(renderTargetBlendStates[i].SourceBlendAlpha);
	}

	HRESULT r = device->_device->CreateBlendState(&blendDesc, _blendState.GetAddressOf());
	RaiseFatalErrorIfFailed(r, "Failed to create a default blend state!", "");
#endif
}

D3D11_COLOR_WRITE_ENABLE BlendState::convert3DRSPColorWrite_toDX11(ColorWriteEnable flag)
{
#ifdef _DX11
	switch(flag)
	{
		case ColorWriteEnable::Red:
			return D3D11_COLOR_WRITE_ENABLE_RED;
		case ColorWriteEnable::Greed:
			return D3D11_COLOR_WRITE_ENABLE_GREEN;
		case ColorWriteEnable::Blue:
			return D3D11_COLOR_WRITE_ENABLE_BLUE;
		case ColorWriteEnable::Alpha:
			return D3D11_COLOR_WRITE_ENABLE_ALPHA;
		default:
			return D3D11_COLOR_WRITE_ENABLE_ALL;
	}
#endif
}

BlendState BlendState::Opaque(GraphicsDevice *device)
{
	// https://github.com/microsoft/DirectXTK/wiki/CommonStates
	return BlendState(device); //just return the default descriptor.
}

BlendState BlendState::AlphaBlend(GraphicsDevice *device)
{
	return BlendState(device, false, false, RenderTargetBlendState{
			.EnableBlending = true,
			.SourceBlend = Blend::One,
			.DestinationBlend = Blend::InverseSourceAlpha,
			.BlendOp = BlendOperation::Add,
			.SourceBlendAlpha = Blend::One,
			.DestinationBlendAlpha = Blend::InverseSourceAlpha,
			.BlendOpAlpha = BlendOperation::Add,
			.WriteMask = ColorWriteEnable::All
		}
	);
}

BlendState BlendState::Additive(GraphicsDevice *device)
{
	return BlendState(device, false, false, RenderTargetBlendState{
			.EnableBlending = true,
			.SourceBlend = Blend::SourceAlpha,
			.DestinationBlend = Blend::One,
			.BlendOp = BlendOperation::Add,
			.SourceBlendAlpha = Blend::SourceAlpha,
			.DestinationBlendAlpha = Blend::One,
			.BlendOpAlpha = BlendOperation::Add,
			.WriteMask = ColorWriteEnable::All
		}
	);
}

BlendState BlendState::NonPremultiplied(GraphicsDevice *device)
{
	return BlendState(device, false, false, RenderTargetBlendState{
		.EnableBlending = true,
		.SourceBlend = Blend::SourceAlpha,
		.DestinationBlend = Blend::InverseSourceAlpha,
		.BlendOp = BlendOperation::Add,
		.SourceBlendAlpha = Blend::SourceAlpha,
		.DestinationBlendAlpha = Blend::InverseSourceAlpha,
		.BlendOpAlpha = BlendOperation::Add,
		.WriteMask = ColorWriteEnable::All
		}
	);
}
