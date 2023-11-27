#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT Blank_NoMatrix : public Effect
	{
		class TrivialVertexShader : public IVertexShader
		{
		public:
			explicit TrivialVertexShader(GraphicsDevice* device);

			virtual std::span<InputLayoutElement> InputLayout();
		};

		class TrivialPixelShader : public IPixelShader
		{
		public:
			explicit TrivialPixelShader(GraphicsDevice *device);
		};
	public:
		explicit Blank_NoMatrix(GraphicsDevice* device);
	};
}