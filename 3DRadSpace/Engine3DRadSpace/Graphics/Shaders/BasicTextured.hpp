#pragma once
#include "../Effect.hpp"
#include "..\..\Math\Matrix4x4.hpp"
#include "../Texture2D.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT BasicTextured : public Effect
	{
		class VertexShader : public IVertexShader
		{
		public:
			explicit VertexShader(GraphicsDevice *Device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IPixelShader
		{
		public:
			explicit PixelShader(GraphicsDevice* Device);
		};

		static inline InputLayoutElement elements[] = {
			InputLayoutElement::Position_Vec3,
			InputLayoutElement::Normal_Vec3,
			InputLayoutElement::Tangent_Vec3,
			InputLayoutElement::Bitangent_Vec3,
			InputLayoutElement::TextureCoordinate2D
		};
	public:
		explicit BasicTextured(GraphicsDevice* device);

		void SetTransform(const Math::Matrix4x4& m);
		void SetTexture(Texture2D* texture);
		void SetSampler(SamplerState* state);
	};
}

