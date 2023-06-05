#include "BlankShader.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

BlankShader::VertexShader::VertexShader(GraphicsDevice* device):
	IVertexShader(device, elements, std::filesystem::path("Data\\Shaders\\PositionColor.hlsl"), "VS_Main")
{
}

BlankShader::PixelShader::PixelShader(GraphicsDevice* device) :
	IPixelShader(device, std::filesystem::path("Data\\Shaders\\PositionColor.hlsl"), "PS_Main")
{
}

std::span<InputLayoutElement> Engine3DRadSpace::Graphics::Shaders::BlankShader::VertexShader::InputLayout()
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
