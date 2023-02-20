#pragma once
#include "ShaderPipeline.hpp"
#include "Matrix.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class BlankShader : public ShaderPipeline
	{
		class VertexShader : public IShader
		{
		public:
			VertexShader(GraphicsDevice* device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IShader
		{
		public:
			PixelShader(GraphicsDevice* device);

			std::span<InputLayoutElement> InputLayout() override;
		};

	public:
		BlankShader(GraphicsDevice* device);

		void SetTransformation(Math::Matrix matrix);
	};
}