#include "TrivialPixelShader.hpp"

using namespace Engine3DRadSpace::Graphics;

InputLayoutElement elements[] = { InputLayoutElement::Position_Vec3 };

Engine3DRadSpace::Graphics::Shaders::TrivialPixelShader::TrivialPixelShader(GraphicsDevice* device) :
	IShader(device, { elements }, "Data\\Shaders\\PositionColor_NoMat.hlsl", "PS_Main", 0)
{
}

std::span<Engine3DRadSpace::Graphics::InputLayoutElement> Engine3DRadSpace::Graphics::Shaders::TrivialPixelShader::InputLayout()
{
	return std::span<InputLayoutElement>();
}
