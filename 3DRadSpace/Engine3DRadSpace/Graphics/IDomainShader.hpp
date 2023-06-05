#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IDomainShader : public IShader
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11DomainShader> shader;
		const char *determineTarget();
#endif
		void createShader();
	public:
		IDomainShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		IDomainShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);

		IDomainShader(IDomainShader &) = delete;
		IDomainShader(IDomainShader &&) = delete;
		IDomainShader &operator = (IDomainShader &) = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}

