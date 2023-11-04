#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	enum class InputLayoutElement
	{
		Position_Vec2 = 0,
		Position_Vec3,
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
	class DLLEXPORT IVertexShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11VertexShader> _shader;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
#endif
		void _createShader();
#ifdef USING_DX11
		const char *_determineTarget();
		[[nodiscard]] D3D11_INPUT_ELEMENT_DESC *_generateInputElementDesc(std::span<InputLayoutElement> inputLayout);
#endif
		void _generateInputLayout(std::span<InputLayoutElement> inputLayout);
	protected:
		IVertexShader(Engine3DRadSpace::GraphicsDevice* device, std::span<InputLayoutElement> inputLayout, const char* shaderSourceCode, const char* vsEntry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
		IVertexShader(Engine3DRadSpace::GraphicsDevice* device, std::span<InputLayoutElement> inputLayout, const std::filesystem::path& path, const char* vsEntry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
	public:
		IVertexShader(IVertexShader &) = delete;
		IVertexShader(IVertexShader &&) noexcept = delete;

		IVertexShader &operator=(IVertexShader &) = delete;
		IVertexShader &operator=(IVertexShader &&) noexcept = delete;

		virtual std::span<InputLayoutElement> InputLayout() = 0;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;

		virtual ~IVertexShader() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}