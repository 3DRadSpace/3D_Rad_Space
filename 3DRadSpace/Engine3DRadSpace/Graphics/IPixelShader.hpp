#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IPixelShader : public IShader
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;

		void createShader();
#endif
		const char *determineTarget();
	public:
		
		IPixelShader(GraphicsDevice *device, const char *shaderSource, const char *entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		IPixelShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);

		IPixelShader(IPixelShader &) = delete;
		IPixelShader(IPixelShader &&) = delete;
		IPixelShader &operator =(IPixelShader &) = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
