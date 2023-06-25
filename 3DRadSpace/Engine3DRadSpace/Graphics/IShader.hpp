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
		Engine3DRadSpace::GraphicsDevice *_device;
		ShaderFeatureLevel _featureLevel;
		const char* _entry;
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3DBlob> _shaderBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob;

		std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> _constantBuffers;

		Array_ValidConstantBuffers _validConstantBuffers(unsigned &numConstantBuffers);
#endif
		void _compileShader( const char* source, const char* target);
		void _compileShaderFromFile( const char* path, const char* target);
	public:
		IShader(GraphicsDevice *device, const char *shaderSourceCode, const char *entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
		IShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);

		IShader(IShader&) = delete;
		IShader(IShader&&) = delete;
		IShader& operator=(IShader&) = delete;

		void SetData(unsigned index,const void *data, unsigned dataSize);
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