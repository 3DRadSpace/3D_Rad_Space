#include "IPixelShader.hpp"
#include "ShaderCompilationError.hpp"
#include "../Logging/ResourceLoadingError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void IPixelShader::createShader()
{
#ifdef _DX11
	HRESULT r = device->device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		shader.GetAddressOf());

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a pixel shader!");
#endif
}

const char *Engine3DRadSpace::Graphics::IPixelShader::determineTarget()
{
	switch(featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "ps_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "ps_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "ps_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "ps_6_0";
		default:
			return nullptr;
	}
}

Engine3DRadSpace::Graphics::IPixelShader::IPixelShader(GraphicsDevice *device, const char *shaderSource, const char *entryFunction, ShaderFeatureLevel fl):
	IShader(device, shaderSource, entryFunction, fl)
{
	compileShader(shaderSource, determineTarget());
	createShader();
}

Engine3DRadSpace::Graphics::IPixelShader::IPixelShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entryFunction, ShaderFeatureLevel fl):
	IShader(device, path, entryFunction, fl)
{
	compileShaderFromFile(path.string().c_str(), determineTarget());
	createShader();
}

void Engine3DRadSpace::Graphics::IPixelShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	device->context->PSSetShaderResources(index, 1, texture->resourceView.GetAddressOf());
#endif // _DX11
}

void Engine3DRadSpace::Graphics::IPixelShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	device->context->PSSetSamplers(0, 1, samplerState->samplerState.GetAddressOf());
#endif
}

void Engine3DRadSpace::Graphics::IPixelShader::SetShader()
{
#ifdef _DX11
	unsigned i;
	auto validConstantBuffers = this->validConstantBuffers(i);
	device->context->PSSetConstantBuffers(0, i, validConstantBuffers.data());

	device->context->PSSetShader(shader.Get(), nullptr, 0);
#endif
}
