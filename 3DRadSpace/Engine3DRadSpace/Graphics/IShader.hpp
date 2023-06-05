#pragma once
#include "Texture2D.hpp"
#include "SamplerState.hpp"
#include "ShaderFeatureLevel.hpp"

namespace Engine3DRadSpace::Graphics
{
#ifdef _DX11
	using Array_ValidConstantBuffers = std::array<ID3D11Buffer *, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT>;
#endif

	class IShader
	{
	protected:
		Engine3DRadSpace::GraphicsDevice *device;
		ShaderFeatureLevel featureLevel;
		const char* entry;
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

		Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;

		std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> constantBuffers;

		Array_ValidConstantBuffers validConstantBuffers(unsigned &numConstantBuffers);
#endif
		void compileShader( const char* source, const char* target);
		void compileShaderFromFile( const char* path, const char* target);
	public:
		IShader(GraphicsDevice *device, const char *shaderSourceCode, const char *entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
		IShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);

		IShader(IShader&) = delete;
		IShader(IShader&&) = delete;
		IShader& operator=(IShader&) = delete;

		void SetData(unsigned index,void *data, unsigned dataSize);
		virtual void SetTexture(unsigned index, Texture2D *texture) = 0;
		virtual void SetSampler(unsigned index, SamplerState *samplerState) = 0;
		virtual void SetShader() = 0;

		ShaderFeatureLevel GetFeatureLevel();
		std::string GetEntryName();

		const char* GetCompilationErrorsAndWarnings();

		virtual ~IShader() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}