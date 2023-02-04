#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class TrivialPixelShader : public IShader
	{
	public:
		TrivialPixelShader(GraphicsDevice* device);

		virtual std::span<InputLayoutElement> InputLayout();

		virtual ~TrivialPixelShader()
		{
		}
	};
}