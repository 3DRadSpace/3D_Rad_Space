#include "IPixelShader.hpp"
#include "ShaderCompilationError.hpp"
#include "../Logging/ResourceLoadingError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void IPixelShader::_createShader()
{
#ifdef USING_DX11
	HRESULT r = _device->_device->CreatePixelShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf());

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a pixel shader!");

#ifdef _DEBUG
	const char shaderName[] = "IPixelShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName), shaderName);
#endif
#endif
}

const char * IPixelShader::_determineTarget()
{
	switch(_featureLevel)
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

IPixelShader::IPixelShader(GraphicsDevice *device, const char *shaderSource, const char *entryFunction, ShaderFeatureLevel fl):
	IShader(device, shaderSource, entryFunction, fl)
{
	_compileShader(shaderSource, _determineTarget());
	_createShader();
}

IPixelShader::IPixelShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entryFunction, ShaderFeatureLevel fl):
	IShader(device, path, entryFunction, fl)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void IPixelShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef USING_DX11
	_device->_context->PSSetShaderResources(index, 1, texture->_resourceView.GetAddressOf());
#endif // USING_DX11
}

void IPixelShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef USING_DX11
	_device->_context->PSSetSamplers(0, 1, samplerState->_samplerState.GetAddressOf());
#endif
}

void IPixelShader::SetShader()
{
#ifdef USING_DX11
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->PSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->PSSetShader(_shader.Get(), nullptr, 0);
#endif
}
