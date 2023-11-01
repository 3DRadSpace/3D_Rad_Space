#include "BasicTextured.hpp"
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

BasicTextured::VertexShader::VertexShader(GraphicsDevice* device) :
	IVertexShader(device, elements, std::filesystem::path("Data\\Shaders\\PositionNormalTangentUV.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> BasicTextured::VertexShader::InputLayout()
{
	return elements;
}

BasicTextured::PixelShader::PixelShader(GraphicsDevice* device) :
	IPixelShader(device, std::filesystem::path("Data\\Shaders\\PositionNormalTangentUV.hlsl"), "PS_Main")
{
}


BasicTextured::BasicTextured(GraphicsDevice* device) : 
	ShaderPipeline(device, new BasicTextured::VertexShader(device), new BasicTextured::PixelShader(device))
{
}

void BasicTextured::SetTransform(const Matrix& m)
{
	_vertex->SetData(0, &m, sizeof(Matrix));
}

void BasicTextured::SetTexture(Texture2D* texture)
{
	_vertex->SetTexture(0, texture);
}

void BasicTextured::SetSampler(SamplerState* state)
{
	_pixel->SetSampler(0, state);
}
