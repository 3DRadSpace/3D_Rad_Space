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

std::span<InputLayoutElement> BlankShader::VertexShader::InputLayout()
{
	return std::span<InputLayoutElement>(elements);
}

BlankShader::BlankShader(GraphicsDevice* device):
	Effect(device, new VertexShader(device), new PixelShader(device))
{
}

void BlankShader::SetTransformation(const Matrix4x4&matrix)
{
	_vertex->SetData(0, static_cast<const void*>(&matrix), sizeof(Matrix4x4));
	_pixel->SetData(0, static_cast<const void*>(&matrix), sizeof(Matrix4x4));
}
