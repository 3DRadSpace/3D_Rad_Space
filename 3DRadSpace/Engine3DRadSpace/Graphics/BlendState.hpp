#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	enum class Blend
	{
        Zero = 0,
        One,
        SourceColor,
        InverseSourceColor,
        SourceAlpha,
        InverseSourceAlpga,
        DestinationAlpha,
        InverseDestinationAlpha,
        DestinationColor,
        InverseDestinationColor,
        SourceAlphaSat,
        BlendFactor,
        InverseBlendFactor,
        Source1Color,
        Source1InverseColor,
        Source1Alpha,
        InverseSource1Alpha
	};

    enum class BlendOperation
    {
        Add,
        Substract,
        ReverseSubstract,
        Minimum,
        Maximum,
    };

    struct RenderTargetBlendState
    {
        bool EnableBlending;
        Blend SourceBlend;
        Blend DestinationBlend;
        BlendOperation BlendOp;
        Blend SourceBlendAlpha;
        Blend DestinationBlendAlpha;
        BlendOperation BlendOpAlpha;
        uint8_t WriteMask;
    };

	class BlendState
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11BlendState> _blendState;
        GraphicsDevice *_device;

        D3D11_BLEND convert3DRSPBlend_toDX11(Blend b);
        D3D11_BLEND_OP convert3DRSPBlendOp_toDX11(BlendOperation op);
#endif
	public:
		/// <summary>
		/// Craetes a default blend state.
		/// </summary>
		/// <param name="device">Graphics device required to create the blend state.</param>
		explicit BlendState(GraphicsDevice *device);

        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, RenderTargetBlendState &renderTargetBlendState);
        BlendState(GraphicsDevice *device, bool alphaCoverage, bool indepedentBlend, std::array<RenderTargetBlendState, 8> renderTargetBlendStates);

        BlendState(BlendState &) = delete;
        BlendState(BlendState &&blend) noexcept;

        BlendState &operator=(BlendState &) = delete;
        BlendState &operator=(BlendState &&blend) noexcept;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
