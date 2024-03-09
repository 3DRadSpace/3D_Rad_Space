#include "FontShader.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Fonts;

static std::array<InputLayoutElement, 2> font_input_layout =
{
	InputLayoutElement::Position_Vec2,
	InputLayoutElement::TextureCoordinate2D
};

FontShader::VertexShader::VertexShader(GraphicsDevice* device) :
    IVertexShader(device, font_input_layout, std::filesystem::path("Data//Shaders//Font.hlsl"), "VS_Main")
{
}

FontShader::PixelShader::PixelShader(GraphicsDevice* device) :
	IPixelShader(device, std::filesystem::path("Data//Shaders//Font.hlsl"), "PS_Main")
{

}

std::span<InputLayoutElement> FontShader::VertexShader::InputLayout()
{
	return font_input_layout;
}

FontShader::FontShader(GraphicsDevice* device) :
	Effect(device, new VertexShader(device), new PixelShader(device))
{
}

void FontShader::SetTexture(Texture2D* texture)
{
	_pixel->SetTexture(0, texture);
}

void FontShader::SetSampler(SamplerState* sampler)
{
	_pixel->SetSampler(0, sampler);
}

void FontShader::SetTintColor(const Color& color)
{
	_pixel->SetData(0, &color, sizeof(Color));
}
