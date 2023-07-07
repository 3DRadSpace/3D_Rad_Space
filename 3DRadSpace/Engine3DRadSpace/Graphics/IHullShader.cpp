#include "IHullShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void IHullShader::_createShader()
{
#ifdef _DX11
	HRESULT r = _device->_device->CreateHullShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf()
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a hull shader!");

#ifdef _DEBUG
	const char shaderName[] = "IHullShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif
#endif
}

const char *IHullShader::_determineTarget()
{
	switch(_featureLevel)
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
	_compileShader(shaderSource, _determineTarget());
	_createShader();
}

IHullShader::IHullShader(GraphicsDevice *device, const std::filesystem::path &path, const char *hsEntry, ShaderFeatureLevel fl):
	IShader(device, path, hsEntry, fl)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void IHullShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	_device->_context->HSSetShaderResources(index, 1, texture->_resourceView.GetAddressOf());
#endif
}

void IHullShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	_device->_context->HSSetSamplers(index, 1, samplerState->_samplerState.GetAddressOf());
#endif // _DX11
}

void Engine3DRadSpace::Graphics::IHullShader::SetShader()
{
#ifdef _DX11
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->HSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->HSSetShader(_shader.Get(), nullptr, 0);
#endif // _DX11
}
