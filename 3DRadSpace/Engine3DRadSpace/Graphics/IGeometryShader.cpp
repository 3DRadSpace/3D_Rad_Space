#include "IGeometryShader.hpp"
#include "ShaderCompilationError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

const char *IGeometryShader::_determineTarget()
{
	switch(_featureLevel)
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

void IGeometryShader::_createShader()
{
#ifdef USING_DX11
	HRESULT r = _device->_device->CreateGeometryShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf()
	);

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a domain shader!");

#ifdef _DEBUG
	const char shaderName[] = "IGeometryShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif
#endif
}

IGeometryShader::IGeometryShader(GraphicsDevice *device, const char *source, const char *fnEntry, ShaderFeatureLevel fs) :
	IShader(device, source, fnEntry, fs)
{
	_compileShader(source, _determineTarget());
	_createShader();
}

IGeometryShader::IGeometryShader(GraphicsDevice *device, const std::filesystem::path &path, const char *fnEntry, ShaderFeatureLevel fs) :
	IShader(device, path, fnEntry, fs)
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget());
	_createShader();
}

void IGeometryShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef USING_DX11
	_device->_context->GSSetShaderResources(index, 1, texture->_resourceView.GetAddressOf());
#endif
}

void IGeometryShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef USING_DX11
	_device->_context->GSSetSamplers(index, 1, samplerState->_samplerState.GetAddressOf());
#endif
}

void Engine3DRadSpace::Graphics::IGeometryShader::SetShader()
{
#ifdef USING_DX11
	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->GSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->GSSetShader(_shader.Get(), nullptr, 0);
#endif // USING_DX11
}

