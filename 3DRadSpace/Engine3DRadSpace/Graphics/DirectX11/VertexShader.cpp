#include "VertexShader.hpp"
#include "../Logging/Logging.hpp"
#include "GraphicsDevice.hpp"
#include "SamplerState.hpp"
#include "../Reflection/ReflectedField.hpp"
#include "../Math/Point3.hpp"
#include "../Math/Point4.hpp"
#include "../Math/UPoint.hpp"
#include "../Math/UPoint3.hpp"
#include "../Math/UPoint4.hpp"
#include "Texture1D.hpp"
#include "TextureCube.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

const char* VertexShader::_determineTarget(ShaderFeatureLevel f)
{
	switch(f)
	{
		case ShaderFeatureLevel::DX_V4:
			return "vs_4_0";
		case ShaderFeatureLevel::DX_V4_1:
			return "vs_4_1";
		case ShaderFeatureLevel::DX_V5:
			return "vs_5_0";
		case ShaderFeatureLevel::DX_V6:
			return "vs_6_0";
		default:
			return nullptr;
			break;
	}
}

void VertexShader::_createShader()
{
	HRESULT r = _device->_device->CreateVertexShader(
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		nullptr,
		_shader.ReleaseAndGetAddressOf()
	);

	if(FAILED(r)) throw Logging::Exception("Failed to compile the shader!");
#ifdef _DEBUG
	const char shaderName[] = "IVertexShader::_shader";
	_shader->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(shaderName) - 1, shaderName);
#endif
}

template<typename E>
auto dx11vs_createInputLayoutDesc(const D3D11_INPUT_ELEMENT_DESC &elementDesc)
{
	return std::make_unique<Reflection::ReflectedField<E>>(
		elementDesc.AlignedByteOffset,
		std::format("{}{}", elementDesc.SemanticName, elementDesc.SemanticIndex),
		"",
		E{}
	);
}

void VertexShader::_generateInputLayout()
{
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflector;

	HRESULT r = D3DReflect(this->_shaderBlob->GetBufferPointer(),
		this->_shaderBlob->GetBufferSize(),
		IID_PPV_ARGS(&reflector)
	);
	if (FAILED(r)) throw Exception("Failed to create shader reflector!");

	//Reflect input parameters
	D3D11_SHADER_DESC shaderDesc{};
	r = reflector->GetDesc(&shaderDesc);
	if (FAILED(r)) throw Exception("Failed to get shader description from reflector!");

	for (int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc{};
		r = reflector->GetInputParameterDesc(i, &paramDesc);
		if (FAILED(r)) break;

		//https://takinginitiative.net/2011/12/11/directx-1011-basic-shader-reflection-automatic-input-layout-creation/

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		std::unique_ptr<Reflection::IReflectedField> e;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				e = dx11vs_createInputLayoutDesc<uint32_t>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				e = dx11vs_createInputLayoutDesc<int32_t>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				e = dx11vs_createInputLayoutDesc<float>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::UPoint>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::Point>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::Vector2>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::UPoint3>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::Point3>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::Vector3>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::UPoint4>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::Point4>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			}
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
			{
				e = dx11vs_createInputLayoutDesc<Math::Vector4>(elementDesc);
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
		}

		//save element desc
		_inputLayoutDesc.push_back(elementDesc);
	}

	r = _device->_device->CreateInputLayout(
		&_inputLayoutDesc[0],
		static_cast<UINT>(_inputLayoutDesc.size()),
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		&this->_inputLayout
	);

#ifdef _DEBUG
	const char inputLayoutName[] = "IVertexShader::InputLayout";
	_inputLayout->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(inputLayoutName) - 1, inputLayoutName);
#endif

	if (FAILED(r)) throw Exception("Failed to create the input layout!");
}

VertexShader::VertexShader(GraphicsDevice*Device, const char *shaderSourceCode, const char *vsEntry, ShaderFeatureLevel fl):
	ShaderBase(Device, shaderSourceCode, vsEntry, _determineTarget(fl))
{
	_compileShader(shaderSourceCode, _determineTarget(fl));
	_createShader();
	_generateInputLayout();
}

VertexShader::VertexShader(GraphicsDevice*Device, const std::filesystem::path &path, const char *vsEntry, ShaderFeatureLevel fl):
	ShaderBase(Device, path, vsEntry, _determineTarget(fl))
{
	_compileShaderFromFile(path.string().c_str(), _determineTarget(fl));
	_createShader();
	_generateInputLayout();
}

void VertexShader::SetTexture(unsigned index, ITexture1D* texture)
{
	if(texture == nullptr)
	{
		ID3D11ShaderResourceView* nullSRV = nullptr;
		_device->_context->VSSetShaderResources(index, 1, &nullSRV);
		return;
	}

	auto dxTexture = static_cast<Texture1D*>(texture);
	_device->_context->VSSetShaderResources(index, 1, dxTexture->_shaderResourceView.GetAddressOf());
}

void VertexShader::SetTextures(std::span<ITexture1D*> textures)
{
	std::unique_ptr<ID3D11ShaderResourceView* []> srvs = std::make_unique<ID3D11ShaderResourceView * []>(textures.size());
	auto len = textures.size();

	for(decltype(len) i = 0; i < len; i++)
	{
		auto texture = textures[i];
		if(texture != nullptr)
			srvs[i] = static_cast<Texture1D*>(textures[i])->_shaderResourceView.Get();
		else
			srvs[i] = nullptr;
	}

	_device->_context->VSSetShaderResources(0, len, srvs.get());
}

void VertexShader::SetTexture(unsigned index, ITexture2D *texture)
{
	if(texture == nullptr)
	{
		ID3D11ShaderResourceView* nullSRV = nullptr;
		_device->_context->VSSetShaderResources(index, 1, &nullSRV);
		return;
	}

	auto dxTexture = dynamic_cast<DirectX11::Texture2D*>(texture);
	_device->_context->VSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void VertexShader::SetTextures(std::span<ITexture2D*> textures)
{
	std::vector<ID3D11ShaderResourceView*> views(textures.size());

	for (size_t i = 0; i < textures.size() && i < D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT; i++)
	{
		views[i] = static_cast<Texture2D*>(textures[i])->_resourceView.Get();
	}

	_device->_context->VSSetShaderResources(0, textures.size(), &views[0]);
}

void VertexShader::SetTexture(unsigned index, ITextureCube* texture)
{
	if (texture == nullptr)
	{
		ID3D11ShaderResourceView* nullSRV = nullptr;
		_device->_context->VSSetShaderResources(index, 1, &nullSRV);
		return;
	}

	auto dxTexture = static_cast<TextureCube*>(texture);
	_device->_context->VSSetShaderResources(index, 1, dxTexture->_resourceView.GetAddressOf());
}

void VertexShader::SetTextures(std::span<ITextureCube*> textures)
{
	std::vector<ID3D11ShaderResourceView*> views(textures.size());

	for(size_t i = 0; i < textures.size() && i < D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT; i++)
	{
		views[i] = static_cast<TextureCube*>(textures[i])->_resourceView.Get();
	}

	_device->_context->VSSetShaderResources(0, textures.size(), &views[0]);
}

void VertexShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	if (samplerState == nullptr)
	{
		ID3D11SamplerState* nullSampler = nullptr;
		_device->_context->VSSetSamplers(index, 1, &nullSampler);
		return;
	}
	
	_device->_context->VSSetSamplers(index, 1, static_cast<SamplerState*>(samplerState)->_samplerState.GetAddressOf());
}

void VertexShader::SetShader()
{
	ShaderBase::SetShader();

	unsigned i;
	auto validConstantBuffers = this->_validConstantBuffers(i);
	_device->_context->VSSetConstantBuffers(0, i, validConstantBuffers.data());

	_device->_context->IASetInputLayout(_inputLayout.Get());
	_device->_context->VSSetShader(_shader.Get(), nullptr, 0);
}

void* VertexShader::GetHandle() const noexcept
{
	return static_cast<void*>(_shader.Get());
}

std::vector<Reflection::IReflectedField*> VertexShader::GetInputLayout() const noexcept
{
	std::vector<Reflection::IReflectedField*> layout;

	for (const auto &element : _reflectedInputLayout)
	{
		layout.emplace_back(element.get());
	}

	return layout;
}