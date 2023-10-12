#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT IGeometryShader : public IShader
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> _shader;
		const char *_determineTarget();
#endif
		void _createShader();
	protected:
		IGeometryShader(GraphicsDevice* device, const char* source, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		IGeometryShader(GraphicsDevice* device, const std::filesystem::path& path, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
	public:
		IGeometryShader(IGeometryShader &) = delete;
		IGeometryShader(IGeometryShader &&) noexcept = delete;
		IGeometryShader &operator = (IGeometryShader &) = delete;
		IGeometryShader &operator = (IGeometryShader &&) noexcept = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;

		~IGeometryShader() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}

