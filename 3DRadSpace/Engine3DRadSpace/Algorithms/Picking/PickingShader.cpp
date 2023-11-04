#include "PickingShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Algorithms::Picking;

PickingShader::VertexShader::VertexShader(GraphicsDevice* device) : 
	IVertexShader(device, _elements, std::filesystem::path("Data\\Shaders\\PickInfo.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> PickingShader::VertexShader::InputLayout()
{
	return _elements;
}

PickingShader::PixelShader::PixelShader(GraphicsDevice* device) :
	IPixelShader(device, std::filesystem::path("Data\\Shaders\\PickInfo.hlsl"), "PS_Main")
{
}

PickingShader::PickingShader(GraphicsDevice* device) : 
	ShaderPipeline(device, new VertexShader(device), new PixelShader(device))
{
}

void PickingShader::SetData(const Data& d)
{
	_vertex->SetData(0, &d, sizeof(Data));
	_pixel->SetData(0, &d, sizeof(Data));
}
