#pragma once
#include "ShaderPipeline.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class Shader_PosColor_NoMatrix : public ShaderPipeline
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
		Shader_PosColor_NoMatrix(GraphicsDevice* device);

		Shader_PosColor_NoMatrix(Shader_PosColor_NoMatrix&) = delete;
		Shader_PosColor_NoMatrix(Shader_PosColor_NoMatrix&&) = delete;
		Shader_PosColor_NoMatrix& operator=(Shader_PosColor_NoMatrix&) = delete;

		IShader* GetPixelShaderRef() const;
		IShader* GetVertexShaderRef() const;
	};
}