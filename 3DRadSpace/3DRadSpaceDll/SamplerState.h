#pragma once
#include "Globals.h"
#include "Color.h"

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
    enum class SamplerStateFilter
    {
        MinMagMipPoint = 0,
        MinMagPoint_MipLinear = 0x1,
        MinPoint_MagLinear_MipPoint = 0x4,
        MinPoint_MagMipLinear = 0x5,
        MinLinear_MagMipPoint = 0x10,
        MinLinear_MagPoint_MipLinear = 0x11,
        MinMagLinear_MipPoint = 0x14,
        MinMagMipLinear = 0x15,
        Anisotropic = 0x55,
        Comparison_MinMagMipPoint = 0x80,
        Comparison_MinMagPoint_MipLinear = 0x81,
        Comparison_MinPoint_MagLinear_MipPoint = 0x84,
        Comparison_MinPoint_MagMipLinear = 0x85,
        Comparison_MinLinear_MagMipPoint = 0x90,
        Comparison_MinLinear_MagPoint_MipLinear = 0x91,
        Comparison_MinMagLinear_MipPoint = 0x94,
        Comparison_MinMagMipLinear = 0x95,
        Comparison_Anisotropic = 0xd5,
        Minimum_MinMagMipPoint = 0x100,
        Minimum_MinMagPoint_MipLinear = 0x101,
        Minimum_MinPoint_MagLinear_MipPoint = 0x104,
        Minimum_MinPoint_MagMipLinear = 0x105,
        Minimum_MinLinear_MagMipPoint = 0x110,
        Minimum_MinLinear_MagPoint_MipLinear = 0x111,
        Minimum_MinMagLinear_MipPoint = 0x114,
        Minimum_MinMagMipLinear = 0x115,
        Minimum_Anisotropic = 0x155,
        Maximum_MinMagMipPoint = 0x180,
        Maximum_MinMagPoint_MipLinear = 0x181,
        Maximum_MinPoint_MagLinear_MipPoint = 0x184,
        Maximum_MinPoint_MagMipLinear = 0x185,
        Maximum_MinLinear_MagMipPoint = 0x190,
        Maximum_MinLinear_MagPoint_MipLinear = 0x191,
        Maximum_MinMagLinear_MipPoint = 0x194,
        Maximum_MinMagMipLinear = 0x195,
        Maximum_Anisotropic = 0x1d5
    };
    enum class TextureAdressMode
    {
        Wrap = 1,
        Mirror = 2,
        Clamp = 3,
        Border = 4,
        Once = 5
    };

    enum class ComparisonFunction
    {
        Never = 1,
        Less = 2,
        Equal = 3,
        LessEqual = 4,
        Greater = 5,
        NotEqual = 6,
        GreaterEqual = 7,
        Always = 8
    };

    struct SamplerStateDescription
    {
        SamplerStateFilter Filter;
        TextureAdressMode AddressU;
        TextureAdressMode AddressV;
        TextureAdressMode AddressW;
        FLOAT MipLODBias;
        unsigned MaxAnisotropy;
        ComparisonFunction ComparisonFunc;
        ColorShader BorderColor;
        float MinLOD;
        float MaxLOD;
    };

    class DLLEXPORT SamplerState
    {
        ID3D11SamplerState* _samplerstate;
    public:
        SamplerState(ID3D11Device* device);
        SamplerState(ID3D11Device* device, const SamplerStateDescription& desc);

        ID3D11SamplerState* GetCreatedSamplerState() const noexcept;

        void SetSamplerVertexShader(ID3D11DeviceContext* context);
        void SetSamplerHullShader(ID3D11DeviceContext* context);

        void SetSamplerGeometryShader(ID3D11DeviceContext* context);
        void SetSamplerDomainShader(ID3D11DeviceContext* context);

        void SetSamplerPixelShader(ID3D11DeviceContext* context);

        ~SamplerState();

    };
}
#endif
