#include "Shader_PosColor_NoMat.hpp"
#include "Shader_PosColor_NoMat.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

InputLayoutElement elements[] = { InputLayoutElement::Position_Vec3, InputLayoutElement::Color };

Shader_PosColor_NoMatrix::TrivialPixelShader::TrivialPixelShader(GraphicsDevice* device) :
	IShader(device, ShaderType::PixelShader, "Data\\Shaders\\PositionColor_NoMat.hlsl", "PS_Main", 0)
{
}

std::span<InputLayoutElement> Shader_PosColor_NoMatrix::TrivialPixelShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

Shader_PosColor_NoMatrix::TrivialVertexShader::TrivialVertexShader(GraphicsDevice* device) :
	IShader(device, std::span<InputLayoutElement>(elements), "Data\\Shaders\\PositionColor_NoMat.hlsl", "VS_Main", 0)
{
}

std::span<InputLayoutElement> Engine3DRadSpace::Graphics::Shaders::Shader_PosColor_NoMatrix::TrivialVertexShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

Engine3DRadSpace::Graphics::Shaders::Shader_PosColor_NoMatrix::Shader_PosColor_NoMatrix(GraphicsDevice* device):
	ShaderPipeline(device, new TrivialVertexShader(device), new TrivialPixelShader(device))
{
}

IShader* Engine3DRadSpace::Graphics::Shaders::Shader_PosColor_NoMatrix::GetPixelShaderRef() const
{
	return this->pixel;
}

IShader* Engine3DRadSpace::Graphics::Shaders::Shader_PosColor_NoMatrix::GetVertexShaderRef() const
{
	return this->vertex;
}
