#include "BasicTextured_NBT.hpp"
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

BasicTextured_NBT::VertexShader::VertexShader(GraphicsDevice* device) :
	IShader(device, elements, "Data\\Shaders\\PositionNormalTangentUV.hlsl", "VS_Main",0)
{
}

std::span<InputLayoutElement> BasicTextured_NBT::VertexShader::InputLayout()
{
	return elements;
}

BasicTextured_NBT::PixelShader::PixelShader(GraphicsDevice* device) :
	IShader(device, ShaderType::PixelShader, "Data\\Shaders\\PositionNormalTangentUV.hlsl", "PS_Main", 0)
{
}

std::span<InputLayoutElement> BasicTextured_NBT::PixelShader::InputLayout()
{
	return elements;
}

BasicTextured_NBT::BasicTextured_NBT(GraphicsDevice* device) : 
	ShaderPipeline(device, new BasicTextured_NBT::VertexShader(device), new BasicTextured_NBT::PixelShader(device))
{
}

void Engine3DRadSpace::Graphics::Shaders::BasicTextured_NBT::SetTransformation(Matrix& m)
{
	vertex->SetData(0, &m, sizeof(Matrix));
}

void Engine3DRadSpace::Graphics::Shaders::BasicTextured_NBT::SetTexture(Engine3DRadSpace::Graphics::Texture2D* texture)
{
	vertex->SetTexture(0, texture);
}

void Engine3DRadSpace::Graphics::Shaders::BasicTextured_NBT::SetSampler(Engine3DRadSpace::SamplerState* state)
{
	pixel->SetSampler(0, state);
}
