#pragma once
#include "../ShaderPipeline.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT Blank_NoMatrix : public ShaderPipeline
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