#pragma once
#include "ShaderPipeline.hpp"
#include "Matrix.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class BasicTextured_NBT : public ShaderPipeline
	{
		class PixelShader : public IShader
		{
		public:
			explicit PixelShader(GraphicsDevice* Device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		class VertexShader : public IShader
		{
		public:
			explicit VertexShader(GraphicsDevice* Device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		static inline InputLayoutElement elements[] = {
			InputLayoutElement::Position_Vec3,
			InputLayoutElement::Normal_Vec3,
			InputLayoutElement::Tangent_Vec3,
			InputLayoutElement::Bitangent_Vec3,
			InputLayoutElement::TextureCoordinate2D
		};
	public:
		explicit BasicTextured_NBT(GraphicsDevice* device);

		void SetTransformation(Engine3DRadSpace::Math::Matrix& m);
		void SetTexture(Engine3DRadSpace::Graphics::Texture2D* texture);
		void SetSampler(Engine3DRadSpace::SamplerState* state);
	};
}

