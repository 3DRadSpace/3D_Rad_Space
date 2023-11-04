#include "Blank_NoMatrix.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

inline InputLayoutElement elements[] = { InputLayoutElement::Position_Vec3, InputLayoutElement::Color };

Blank_NoMatrix::TrivialVertexShader::TrivialVertexShader(GraphicsDevice *device) :
	IVertexShader(device, std::span<InputLayoutElement>(elements), std::filesystem::path("Data\\Shaders\\PositionColor_NoMat.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> Blank_NoMatrix::TrivialVertexShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

Blank_NoMatrix::TrivialPixelShader::TrivialPixelShader(GraphicsDevice* device) :
	IPixelShader(device, std::filesystem::path("Data\\Shaders\\PositionColor_NoMat.hlsl"), "PS_Main")
{
}

Blank_NoMatrix::Blank_NoMatrix(GraphicsDevice* device):
	ShaderPipeline(device, new TrivialVertexShader(device), new TrivialPixelShader(device))
{
}