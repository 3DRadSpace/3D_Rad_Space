#include "BlankShader.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

BlankShader::VertexShader::VertexShader(GraphicsDevice* device):
	IShader(device, elements, "Data\\Shaders\\PositionColor.hlsl", "VS_Main", 0)
{
}

BlankShader::PixelShader::PixelShader(GraphicsDevice* device) :
	IShader(device, ShaderType::PixelShader, "Data\\Shaders\\PositionColor.hlsl", "PS_Main", 0)
{
}

std::span<InputLayoutElement> Engine3DRadSpace::Graphics::Shaders::BlankShader::VertexShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

std::span<InputLayoutElement> Engine3DRadSpace::Graphics::Shaders::BlankShader::PixelShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

Engine3DRadSpace::Graphics::Shaders::BlankShader::BlankShader(GraphicsDevice* device):
	ShaderPipeline(device, new VertexShader(device), new PixelShader(device))
{
}

void Engine3DRadSpace::Graphics::Shaders::BlankShader::SetTransformation(Math::Matrix &matrix)
{
	this->vertex->SetData(0, static_cast<void*>(&matrix), sizeof(Matrix));
	this->pixel->SetData(0, static_cast<void*>(&matrix), sizeof(Matrix));
}
