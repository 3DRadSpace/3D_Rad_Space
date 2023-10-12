#include "PickingShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

PickingShader::VertexShader::VertexShader(Engine3DRadSpace::GraphicsDevice* device) : 
	IVertexShader(device, elements, "Data\\Shaders\\PickInfo.hlsl", "VS_Main")
{
}

std::span<InputLayoutElement> PickingShader::VertexShader::InputLayout()
{
	return elements;
}

PickingShader::PixelShader::PixelShader(GraphicsDevice* device) :
	IPixelShader(device, "Data\\Shaders\\PickInfo.hlsl", "PS_Main")
{
}

PickingShader::PickingShader(Engine3DRadSpace::GraphicsDevice* device) : 
	ShaderPipeline(device, new VertexShader(device), new PixelShader(device))
{
}
