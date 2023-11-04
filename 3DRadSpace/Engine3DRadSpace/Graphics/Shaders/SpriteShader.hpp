#pragma once
#include "../ShaderPipeline.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT SpriteShader : public ShaderPipeline
	{
		class VertexShader : public IVertexShader
		{
		public:
			VertexShader(GraphicsDevice *device);
			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IPixelShader
		{
		public:
			PixelShader(GraphicsDevice *device);
		};

		static inline std::array<InputLayoutElement, 2> sprite_elements =
		{
			InputLayoutElement::Position_Vec2,
			InputLayoutElement::TextureCoordinate2D
		};
	public:
		explicit SpriteShader(GraphicsDevice*device);

		struct alignas(16) Data
		{
			Color TintColor;
			int FlipU = false;
			int FlipV = false;
		};

		void SetData(const Data &d);
		void SetTexture(Texture2D *texture);
		void SetSamplerState(SamplerState *sampler);
	};
}