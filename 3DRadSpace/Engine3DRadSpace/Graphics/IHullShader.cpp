#include "IHullShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void IHullShader::createShader()
{
#ifdef _DX11
	HRESULT r = device->device->CreateHullShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		nullptr
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a hull shader!");
#endif
}

const char *IHullShader::determineTarget()
{
	switch(featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "hs_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "hs_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "hs_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "hs_6_0";
		default:
			return nullptr;
			break;
	}
}

IHullShader::IHullShader(GraphicsDevice *device, const char *shaderSource, const char *hsEntry, ShaderFeatureLevel fl):
	IShader(device, shaderSource, hsEntry, fl)
{
	compileShader(shaderSource, determineTarget());
	createShader();
}

IHullShader::IHullShader(GraphicsDevice *device, const std::filesystem::path &path, const char *hsEntry, ShaderFeatureLevel fl):
	IShader(device, path, hsEntry, fl)
{
	compileShaderFromFile(path.string().c_str(), determineTarget());
	createShader();
}

void IHullShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	device->context->HSSetShaderResources(index, 1, texture->resourceView.GetAddressOf());
#endif
}

void IHullShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	device->context->HSSetSamplers(index, 1, samplerState->samplerState.GetAddressOf());
#endif // _DX11
}

void Engine3DRadSpace::Graphics::IHullShader::SetShader()
{
#ifdef _DX11
	unsigned i;
	auto validConstantBuffers = this->validConstantBuffers(i);
	device->context->HSSetConstantBuffers(0, i, validConstantBuffers.data());

	device->context->HSSetShader(shader.Get(), nullptr, 0);
#endif // _DX11
}
