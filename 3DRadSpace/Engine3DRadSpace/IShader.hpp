#pragma once
#include "Texture2D.hpp"

#ifdef _DX11
#pragma comment(lib,"d3dcompiler.lib")
#endif

namespace Engine3DRadSpace::Graphics
{
	enum class InputLayoutElement
	{
		Position_Vec3 = 0,
		Position_Vec4,

		PositionTransformed_Vec3,
		PositionTransformed_Vec4,

		Color,

		Normal_Vec3,
		Normal_Vec4,

		Tangent_Vec3,
		Tangent_Vec4,

		Bitangent_Vec3,
		Bitangent_Vec4,

		TextureCoordinate2D,
		TextureCoordinate3D,
		TextureCoordinate4D,

		BlendIndices,
		BlendWeights,
		PointSize,
	};

	enum class ShaderFeatureLevel : char
	{
		DX_V4,
		DX_V4_1,
		DX_V5,
		DX_V6,
	};

	enum class ShaderType : char
	{
		VertexShader,
		HullShader,
		DomainShader,
		GeometryShader,
		PixelShader,
	};

	class IShader
	{
		Engine3DRadSpace::GraphicsDevice *device;
		ShaderType type;
		ShaderFeatureLevel featureLevel;
		std::string entry;
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

		Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;
		Microsoft::WRL::ComPtr<ID3D11DeviceChild> shader;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
		std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>,14> constantBuffers;
#endif
		void determineTarget(char* target, size_t lenStr);
		void compileShader( const char* source);
		void compileShaderFromFile(  const char* path);
		void createShader();
		[[nodiscard]] D3D11_INPUT_ELEMENT_DESC *generateInputElementDesc(std::span<InputLayoutElement> inputLayout);
		void generateInputLayout(std::span<InputLayoutElement> inputLayout);
	public:
		IShader(GraphicsDevice *device, ShaderType type, const char *shaderSourceCode,const char* entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
		IShader(GraphicsDevice *device, std::span<InputLayoutElement> inputLayout, const char *shaderSourceCode, const char *vsEntry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);

		IShader(GraphicsDevice* device, ShaderType type, const char* path, const char* entry,int dummy, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
		IShader(GraphicsDevice* device, std::span<InputLayoutElement> inputLayout, const char* path, const char* vsEntry,int dummy, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);

		IShader(IShader&) = delete;
		IShader(IShader&&) = delete;
		IShader& operator=(IShader&) = delete;

		virtual std::span<InputLayoutElement> InputLayout() = 0;

		void SetData(unsigned index,void *data, unsigned dataSize);
		void SetTexture(unsigned index, Texture2D *texture);

		ShaderFeatureLevel GetFeatureLevel();
		ShaderType GetType();
		std::string GetEntryName();

		const char* GetCompilationErrorsAndWarnings();

		virtual ~IShader();

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}