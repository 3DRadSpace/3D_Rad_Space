#include "IDomainShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

const char *IDomainShader::determineTarget()
{
	switch(featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "ds_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "ds_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "ds_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "ds_6_0";
		default:
			return nullptr;
			break;
	}
}

void IDomainShader::createShader()
{
#ifdef _DX11
	HRESULT r = device->device->CreateDomainShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		nullptr
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a domain shader!");
#endif
}

IDomainShader::IDomainShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs) :
	IShader(device, source, fnEntry, fs)
{
	compileShader(source, determineTarget());
	createShader();
}

IDomainShader::IDomainShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs):
	IShader(device, path, fnEntry, fs)
{
	compileShaderFromFile(path.string().c_str(), determineTarget());
	createShader();
}

void IDomainShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	device->context->DSSetShaderResources(index, 1, texture->resourceView.GetAddressOf());
#endif
}

void IDomainShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	device->context->DSSetSamplers(index, 1, samplerState->samplerState.GetAddressOf());
#endif // _DX11
}

void Engine3DRadSpace::Graphics::IDomainShader::SetShader()
{
#ifdef _DX11
	unsigned i;
	auto validConstantBuffers = this->validConstantBuffers(i);
	device->context->DSSetConstantBuffers(0, i, validConstantBuffers.data());

	device->context->DSSetShader(shader.Get(), nullptr, 0);
#endif // _DX11
}

