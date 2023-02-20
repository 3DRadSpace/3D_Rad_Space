#pragma once
#include "ShaderPipeline.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class Blank_NoMatrix : public ShaderPipeline
	{
		class TrivialPixelShader : public IShader
		{
		public:
			TrivialPixelShader(GraphicsDevice* device);

			virtual std::span<InputLayoutElement> InputLayout();
		};

		class TrivialVertexShader : public IShader
		{
		public:
			TrivialVertexShader(GraphicsDevice* device);

			virtual std::span<InputLayoutElement> InputLayout();
		};

	public:
		Blank_NoMatrix(GraphicsDevice* device);
	};
}