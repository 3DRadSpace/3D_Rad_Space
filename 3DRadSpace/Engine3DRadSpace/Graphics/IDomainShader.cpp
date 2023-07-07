#include "IDomainShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

const char *IDomainShader::_determineTarget()
{
	switch(_featureLevel)
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

void IDomainShader::_createShader()
{
#ifdef _DX11
	HRESULT r = _device->_device->CreateDomainShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf()
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a domain shader!");

#ifdef  _DEBUG
	const char shaderName[] = "IDomainShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif //  _DEBUG
#endif
}

IDomainShader::IDomainShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs) :
	IShader(device, source, fnEntry, fs)
{
	_compileShader(source, _determineTarget());
	_createShader();
}

IDomainShader::IDomainShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs):
	IShader(device, path, fnEntry, fs)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void IDomainShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	_device->_context->DSSetShaderResources(index, 1, texture->_resourceView.GetAddressOf());
#endif
}

void IDomainShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	_device->_context->DSSetSamplers(index, 1, samplerState->_samplerState.GetAddressOf());
#endif // _DX11
}

void Engine3DRadSpace::Graphics::IDomainShader::SetShader()
{
#ifdef _DX11
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->DSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->DSSetShader(_shader.Get(), nullptr, 0);
#endif // _DX11
}

