#include "IGeometryShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

const char *IGeometryShader::determineTarget()
{
	switch(featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			return "gs_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "gs_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "gs_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "gs_6_0";
		default:
			return nullptr;
			break;
	}
}

void IGeometryShader::createShader()
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

IGeometryShader::IGeometryShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs) :
	IShader(device, source, fnEntry, fs)
{
	compileShader(source, determineTarget());
	createShader();
}

IGeometryShader::IGeometryShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs) :
	IShader(device, path, fnEntry, fs)
{
	compileShaderFromFile(path.string().c_str(), determineTarget());
	createShader();
}

void IGeometryShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	device->context->GSSetShaderResources(index, 1, texture->resourceView.GetAddressOf());
#endif
}

void IGeometryShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	device->context->GSSetSamplers(index, 1, samplerState->samplerState.GetAddressOf());
#endif
}

void Engine3DRadSpace::Graphics::IGeometryShader::SetShader()
{
#ifdef _DX11
	unsigned i;
	auto validConstantBuffers = this->validConstantBuffers(i);
	device->context->GSSetConstantBuffers(0, i, validConstantBuffers.data());

	device->context->GSSetShader(shader.Get(), nullptr, 0);
#endif // _DX11
}

