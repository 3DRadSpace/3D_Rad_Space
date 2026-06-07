#include "FragmentShader.hpp"
#include "ShaderCompilationError.hpp"
#include "GraphicsDevice.hpp"
#include "SamplerState.hpp"
#include "Texture1D.hpp"
#include "TextureCube.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

void FragmentShader::_createShader()
{
	HRESULT r = _device->_device->CreatePixelShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.GetAddressOf());

	if(FAILED(r)) throw ShaderCompilationError("Failed to create a pixel shader!");

#ifdef _DEBUG
	const char shaderName[] = "FragmentShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName), shaderName);
#endif
}

const char * FragmentShader::_determineTarget(ShaderFeatureLevel f)
{
	switch(f)
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

FragmentShader::FragmentShader(GraphicsDevice *device, const char *shaderSource, const char *entryFunction, ShaderFeatureLevel fl):
	ShaderBase(device, shaderSource, entryFunction, _determineTarget(fl))
{
	_compileShader(shaderSource, _determineTarget(fl));
	_createShader();
}

FragmentShader::FragmentShader(GraphicsDevice *device, const std::filesystem::path &path, const char *entryFunction, ShaderFeatureLevel fl):
	ShaderBase(device, path, entryFunction, _determineTarget(fl))
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget(fl));
	_createShader();
}

void FragmentShader::SetTexture(unsigned index, ITexture1D* texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<Texture1D*>(texture);
	_device->_context->PSSetShaderResources(index, 1, dxTexture->_shaderResourceView.GetAddressOf());
}

void FragmentShader::SetTextures(std::span<ITexture1D*> textures)
{
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView * []>(textures.size());
	auto len = textures.size();

	for(decltype(len) i = 0; i < len; i++)
	{
		srvs[i] = static_cast<Texture1D*>(textures[i])->_shaderResourceView.Get();
	}

	_device->_context->PSSetShaderResources(0, len, srvs.get());
}

void FragmentShader::SetTexture(unsigned index, ITexture2D *texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<Texture2D*>(texture);
	_device->_context->PSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void FragmentShader::SetTextures(std::span<ITexture2D*> textures)
{
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView* []>(textures.size());
	auto len = textures.size();

	for(decltype(len) i = 0; i < len; i++)
	{
		srvs[i] = static_cast<Texture2D*>(textures[i])->_resourceView.Get();
	}

	_device->_context->PSSetShaderResources(0, len, srvs.get());
}

void FragmentShader::SetTexture(unsigned index, ITextureCube* texture)
{
	if(texture == nullptr)
		return;

	auto dxTexture = static_cast<TextureCube*>(texture);
	_device->_context->PSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void FragmentShader::SetTextures(std::span<ITextureCube*> textures)
{
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView * []>(textures.size());
	auto len = textures.size();

	for(decltype(len) i = 0; i < len; i++)
	{
		srvs[i] = static_cast<TextureCube*>(textures[i])->_resourceView.Get();
	}

	_device->_context->PSSetShaderResources(0, len, srvs.get());
}

void FragmentShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	auto dxSamplerState = static_cast<SamplerState*>(samplerState);
	_device->_context->PSSetSamplers(0, 1, dxSamplerState->_samplerState.GetAddressOf());
}

void FragmentShader::SetShader()
{
	ShaderBase::SetShader();

	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->PSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->PSSetShader(_shader.Get(), nullptr, 0);
}

void* FragmentShader::GetHandle() const noexcept
{
	return static_cast<void*>(_shader.Get());
}
