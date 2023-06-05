#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	enum class TextureFilter
	{
		Anisotropic,
		Linear,
		LinearMipPoint,
		MinLinearMagPointMipLinear,
		MinLinearMagPointMipPoint,
		MinPointMagLinearMipLinear,
		MinPointMagLinearMipPoint,
		Point,
		PointMipLinear
	};

	enum class TextureAddressMode
	{
		Wrap = 1,
		Mirror = 2,
		Clamp = 3,
		Border = 4,
		MirrorOnce = 5
	};

	class SamplerState
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
#endif
	public:
		SamplerState(GraphicsDevice *device);
		SamplerState(GraphicsDevice* device, TextureFilter Filter, TextureAddressMode AddressU, TextureAddressMode AddressV, TextureAddressMode AddressW,
			float MipLODBias, unsigned MaxAnisotropy, ComparisonFunction ComparisionFunction, Color BorderColor, float MinLOD, float MaxLOD);

		static SamplerState LinearClamp(GraphicsDevice *device);
		static SamplerState LinearWrap(GraphicsDevice *device);

		static SamplerState PointClamp(GraphicsDevice *device);
		static SamplerState PointWrap(GraphicsDevice *device);

		static SamplerState AnisotropicClamp(GraphicsDevice *device);
		static SamplerState AnisotropicWrap(GraphicsDevice *device);

		friend class IVertexShader;
		friend class IPixelShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
	};
}

