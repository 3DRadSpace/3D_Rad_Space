#include "SpriteShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

SpriteShader::VertexShader::VertexShader(GraphicsDevice *device) : IVertexShader(device, sprite_elements, std::filesystem::path("Data\\Shaders\\Sprite.hlsl"), "VS_Main")
{
}

std::span<InputLayoutElement> SpriteShader::VertexShader::InputLayout()
{
	return SpriteShader::sprite_elements;
}

SpriteShader::PixelShader::PixelShader(GraphicsDevice *device) : IPixelShader(device, std::filesystem::path("Data\\Shaders\\Sprite.hlsl"), "PS_Main")
{
}

SpriteShader::SpriteShader(GraphicsDevice *device) :
	ShaderPipeline(device, new VertexShader(device), new PixelShader(device))
{
	Data default_data = {Engine3DRadSpace::Colors::White, false, false};
	SetData(default_data);
}

void Engine3DRadSpace::Graphics::Shaders::SpriteShader::SetData(const Data &d)
{
	_vertex->SetData(0, &d, sizeof(Data));
	_pixel->SetData(0, &d, sizeof(Data));
}

void Engine3DRadSpace::Graphics::Shaders::SpriteShader::SetTexture(Engine3DRadSpace::Graphics::Texture2D *texture)
{
	_vertex->SetTexture(0, texture);
	_pixel->SetTexture(0, texture);
}

void Engine3DRadSpace::Graphics::Shaders::SpriteShader::SetSamplerState(Engine3DRadSpace::Graphics::SamplerState *sampler)
{
	_vertex->SetSampler(0, sampler);
	_pixel->SetSampler(0, sampler);
}
