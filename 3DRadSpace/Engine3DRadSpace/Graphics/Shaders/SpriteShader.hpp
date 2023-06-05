#pragma once
#include "../ShaderPipeline.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class SpriteShader : public Engine3DRadSpace::Graphics::Shaders::ShaderPipeline
	{
		class VertexShader : public Engine3DRadSpace::Graphics::IVertexShader
		{
		public:
			VertexShader(Engine3DRadSpace::GraphicsDevice *device);
			std::span<Engine3DRadSpace::Graphics::InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public Engine3DRadSpace::Graphics::IPixelShader
		{
		public:
			PixelShader(Engine3DRadSpace::GraphicsDevice *device);
		};

		static inline std::array<Engine3DRadSpace::Graphics::InputLayoutElement, 2> sprite_elements =
		{
			Engine3DRadSpace::Graphics::InputLayoutElement::Position_Vec2,
			Engine3DRadSpace::Graphics::InputLayoutElement::TextureCoordinate2D
		};
	public:
		explicit SpriteShader(Engine3DRadSpace::GraphicsDevice *device);

		struct alignas(16) Data
		{
			Engine3DRadSpace::Color tintColor;
			int flipU = false;
			int flipV = false;
		};

		void SetData(Data &d);
		void SetTexture(Engine3DRadSpace::Graphics::Texture2D *texture);
		void SetSamplerState(Engine3DRadSpace::Graphics::SamplerState *sampler);
	};
}