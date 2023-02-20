#include "Blank_NoMatrix.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

inline InputLayoutElement elements[] = { InputLayoutElement::Position_Vec3, InputLayoutElement::Color };

Blank_NoMatrix::TrivialPixelShader::TrivialPixelShader(GraphicsDevice* device) :
	IShader(device, ShaderType::PixelShader, "Data\\Shaders\\PositionColor_NoMat.hlsl", "PS_Main", 0)
{
}

std::span<InputLayoutElement> Blank_NoMatrix::TrivialPixelShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

Blank_NoMatrix::TrivialVertexShader::TrivialVertexShader(GraphicsDevice* device) :
	IShader(device, std::span<InputLayoutElement>(elements), "Data\\Shaders\\PositionColor_NoMat.hlsl", "VS_Main", 0)
{
}

std::span<InputLayoutElement> Engine3DRadSpace::Graphics::Shaders::Blank_NoMatrix::TrivialVertexShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

Blank_NoMatrix::Blank_NoMatrix(GraphicsDevice* device):
	ShaderPipeline(device, new TrivialVertexShader(device), new TrivialPixelShader(device))
{
}