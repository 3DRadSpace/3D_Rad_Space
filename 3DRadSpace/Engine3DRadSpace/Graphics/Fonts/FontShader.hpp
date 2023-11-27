#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Fonts
{
	class FontShader : public Shaders::Effect
	{
		class VertexShader : public IVertexShader
		{
		public:
			VertexShader(GraphicsDevice* device);
			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IPixelShader
		{
		public:
			PixelShader(GraphicsDevice* device);
		};
	public:
		FontShader(GraphicsDevice* device);

		void SetTexture(Texture2D* texture);
		void SetSampler(SamplerState* sampler);
		void SetTintColor(const Color& color);
	};
}