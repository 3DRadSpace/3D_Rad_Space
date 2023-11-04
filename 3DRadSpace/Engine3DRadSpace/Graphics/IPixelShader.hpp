#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT IPixelShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;

		void _createShader();
#endif
		const char *_determineTarget();
	protected:
		IPixelShader(GraphicsDevice* device, const char* shaderSource, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
		IPixelShader(GraphicsDevice* device, const std::filesystem::path& path, const char* entryFunction, ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4);
	public:
		IPixelShader(IPixelShader &) = delete;
		IPixelShader(IPixelShader &&) noexcept = delete;

		IPixelShader &operator = (IPixelShader &) = delete;
		IPixelShader &operator = (IPixelShader &&) noexcept = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;

		virtual ~IPixelShader() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}
