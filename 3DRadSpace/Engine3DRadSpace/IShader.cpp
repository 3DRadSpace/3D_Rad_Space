#include "IShader.hpp"
#include "Error.hpp"
#include "Warning.hpp"

void Engine3DRadSpace::Graphics::IShader::_determineTarget(char* target, size_t lenStr)
{
	switch (_type)
	{
		case ShaderType::VertexShader:
			strcat_s(target,lenStr, "vs_");
			break;
		case ShaderType::HullShader:
			strcat_s(target,lenStr, "hs_");
			break;
		case ShaderType::DomainShader:
			strcat_s(target, lenStr, "ds_");
			break;
		case ShaderType::GeometryShader:
			strcat_s(target, lenStr, "gs_");
			break;
		case ShaderType::PixelShader:
			strcat_s(target, lenStr, "ps_");
			break;
		default:
			Engine3DRadSpace::Logging::RaiseFatalError({ -1,"Unknown shader type!",&_type });
			break;
	}

	switch (_featureLevel)
	{
		case ShaderFeatureLevel::DX_V4:
			strcat_s(target, lenStr, "4_0");
			break;
		case ShaderFeatureLevel::DX_V4_1:
			strcat_s(target, lenStr, "4_1");
			break;
		case ShaderFeatureLevel::DX_V5:
			strcat_s(target, lenStr, "5_0");
			break;
		case ShaderFeatureLevel::DX_V6:
			strcat_s(target, lenStr, "6_0");
			break;
		default:
			Engine3DRadSpace::Logging::RaiseFatalError({ -1,"Unknown shader feature level!" });
			break;
	}
}

void Engine3DRadSpace::Graphics::IShader::_compileShader(const char *source)
{
#ifdef _WIN32
	char target[10] = "";
	_determineTarget(target, 10);

	HRESULT r = D3DCompile(
		source,
		strlen(source),
		nullptr,
		nullptr,
		nullptr,
		_entry.c_str(),
		target,
		0,
		0,
		&_shaderBlob,
		&_errorBlob
	);
	if(_errorBlob.Get() != nullptr)
	{
		Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(
			r,
			(std::string("Shader compilation failure! \r\n") + static_cast<char*>(_errorBlob->GetBufferPointer())).c_str(),
			source
		);
	}

	_createShader();
#endif
}

void Engine3DRadSpace::Graphics::IShader::_compileShaderFromFile(const char* path)
{
#ifdef _WIN32
	char target[10] = "";
	_determineTarget(target, 10);

	wchar_t wpath[_MAX_PATH]{ 0 };
	MultiByteToWideChar(CP_ACP, 0, path, (int)strlen(path), wpath, _MAX_PATH);

	HRESULT r = D3DCompileFromFile(
		wpath,
		nullptr,
		nullptr,
		_entry.c_str(),
		target,
		0,
		0,
		&_shaderBlob,
		&_errorBlob
	);
	if(_errorBlob.Get() == nullptr) Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Shader file not found!", path);
	else
	{
		Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(
			r,
			(std::string("Shader compilation failure! \r\n") + static_cast<char*>(_errorBlob->GetBufferPointer())).c_str(),
			path
		);
	}

	_createShader();
#endif
}

void Engine3DRadSpace::Graphics::IShader::_createShader()
{
	switch (_type)
	{
		case ShaderType::VertexShader:
			_device->_device->CreateVertexShader(
				_shaderBlob->GetBufferPointer(),
				_shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11VertexShader**>(this->_shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::HullShader:
			_device->_device->CreateHullShader(
				_shaderBlob->GetBufferPointer(),
				_shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11HullShader**>(this->_shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::DomainShader:
			_device->_device->CreateDomainShader(
				_shaderBlob->GetBufferPointer(),
				_shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11DomainShader**>(this->_shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::GeometryShader:
			_device->_device->CreateGeometryShader(
				_shaderBlob->GetBufferPointer(),
				_shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11GeometryShader**>(this->_shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::PixelShader:
			_device->_device->CreatePixelShader(
				_shaderBlob->GetBufferPointer(),
				_shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11PixelShader**>(this->_shader.ReleaseAndGetAddressOf())
			);
			break;
		default:
			break;
	}
}

D3D11_INPUT_ELEMENT_DESC *Engine3DRadSpace::Graphics::IShader::generateInputElementDesc(std::span<InputLayoutElement> inputLayout)
{
	size_t numLayoutEntries = inputLayout.size();

	D3D11_INPUT_ELEMENT_DESC *elem = new D3D11_INPUT_ELEMENT_DESC[numLayoutEntries]{};
	if (elem == nullptr)
	{
		Logging::RaiseFatalError(Logging::Error(-1, "Failed to allocate heap memory for a D3D11_INPUT_ELEMENT_DESC array!"));
		return nullptr;
	}

	unsigned posIndex = 0;
	//unsigned posTIndex = 0;
	unsigned colorIndex = 0;
	unsigned normalIndex = 0;
	unsigned tangentIndex = 0;
	unsigned bitangentIndex = 0;
	unsigned texCoordIndex = 0;
	unsigned blendIndicesIndex = 0;
	unsigned blendWeightIndex = 0;
	unsigned pointSizeIndex = 0;

	for (int i = 0; i < numLayoutEntries; i++)
	{
		switch (inputLayout[i])
		{
			case InputLayoutElement::Position_Vec3:
			{
				elem[i] = 
				{
					"POSITION", //SemanticName
					posIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				posIndex++;
				break;
			}
			case InputLayoutElement::Position_Vec4:
			{
				elem[i] =
				{
					"POSITION", //SemanticName
					posIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				posIndex++;
				break;
			}
			case InputLayoutElement::PositionTransformed_Vec3:
			{
				elem[i] =
				{
					"POSITIONT", //SemanticName
					0, //posTIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				//posTIndex++;
				break;
			}
			case InputLayoutElement::PositionTransformed_Vec4:
			{
				elem[i] =
				{
					"POSITIONT", //SemanticName
					0, //posTIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				//posTIndex++;
				break;
			}
			case InputLayoutElement::Color:
			{
				elem[i] =
				{
					"COLOR", //SemanticName
					colorIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				colorIndex++;
				break;
			}
			case InputLayoutElement::Normal_Vec3:
			{
				elem[i] =
				{
					"NORMAL", //SemanticName
					normalIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				normalIndex++;
				break;
			}
			case InputLayoutElement::Normal_Vec4:
			{
				elem[i] =
				{
					"NORMAL", //SemanticName
					normalIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				normalIndex++;
				break;
			}
			case InputLayoutElement::Tangent_Vec3:
			{
				elem[i] =
				{
					"TANGENT", //SemanticName
					tangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				tangentIndex++;
				break;
			}
			case InputLayoutElement::Tangent_Vec4:
			{
				elem[i] =
				{
					"TANGENT", //SemanticName
					tangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				tangentIndex++;
				break;
			}
			case InputLayoutElement::Bitangent_Vec3:
			{
				elem[i] =
				{
					"BINORMAL", //SemanticName
					bitangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				bitangentIndex++;
				break;
			}
			case InputLayoutElement::Bitangent_Vec4:
			{
				elem[i] =
				{
					"BINORMAL", //SemanticName
					bitangentIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				bitangentIndex++;
				break;
			}
			case InputLayoutElement::TextureCoordinate2D:
			{
				elem[i] =
				{
					"TEXCOORD", //SemanticName
					texCoordIndex, //SemanticIndex
					DXGI_FORMAT_R32G32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				texCoordIndex++;
				break;
			}
			case InputLayoutElement::TextureCoordinate3D:
			{
				elem[i] =
				{
					"TEXCOORD", //SemanticName
					texCoordIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				texCoordIndex++;
				break;
			}
			case InputLayoutElement::TextureCoordinate4D:
			{
				elem[i] =
				{
					"TEXCOORD", //SemanticName
					texCoordIndex, //SemanticIndex
					DXGI_FORMAT_R32G32B32A32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				texCoordIndex++;
				break;
			}
			case InputLayoutElement::BlendIndices:
			{
				elem[i] =
				{
					"BLENDINDICES", //SemanticName
					blendIndicesIndex, //SemanticIndex
					DXGI_FORMAT_R32_UINT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				blendIndicesIndex++;
				break;
			}
			case InputLayoutElement::BlendWeights:
			{
				elem[i] =
				{
					"BLENDWEIGHT", //SemanticName
					blendWeightIndex, //SemanticIndex
					DXGI_FORMAT_R32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				blendWeightIndex++;
				break;
			}
			case InputLayoutElement::PointSize:
			{
				elem[i] =
				{
					"PSIZE", //SemanticName
					blendWeightIndex, //SemanticIndex
					DXGI_FORMAT_R32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				blendWeightIndex++;
				break;
			}
			default:
				break;
		}
	}
	return elem;
}

void Engine3DRadSpace::Graphics::IShader::_generateInputLayout(std::span<InputLayoutElement> inputLayout)
{
	D3D11_INPUT_ELEMENT_DESC *elements = generateInputElementDesc(inputLayout);

	HRESULT r = _device->_device->CreateInputLayout(
		elements,
		static_cast<UINT>(inputLayout.size()),
		_shaderBlob->GetBufferPointer(),
		_shaderBlob->GetBufferSize(),
		&_inputLayout
	);
	delete[] elements;

	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create the input layout!");
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice *device, ShaderType type, const char *shaderSourceCode,const char* entry, ShaderFeatureLevel featureLevel):
	_device(device),
	_type(type),
	_entry(entry),
	_featureLevel(featureLevel),
	_constantBuffers({ nullptr })
{
	_compileShader(shaderSourceCode);
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice *device, std::span<InputLayoutElement> inputLayout, const char *shaderSourceCode, const char *vsEntry, ShaderFeatureLevel featureLevel):
	_device(device),
	_type(ShaderType::VertexShader),
	_entry(vsEntry),
	_featureLevel(featureLevel),
	_constantBuffers({ nullptr })
{
	_compileShader(shaderSourceCode);
	_generateInputLayout(inputLayout);
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice* device, ShaderType type, const char* path, const char* entry, int dummy, ShaderFeatureLevel featureLevel):
	_device(device),
	_type(type),
	_entry(entry),
	_featureLevel(featureLevel),
	_constantBuffers({ nullptr }),
	_shader(),
	_errorBlob(),
	_shaderBlob()
{
	UNREFERENCED_PARAMETER(dummy);
	_compileShaderFromFile(path);
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice* device, std::span<InputLayoutElement> inputLayout, const char* path, const char* vsEntry, int dummy, ShaderFeatureLevel featureLevel):
	_device(device),
	_type(ShaderType::VertexShader),
	_entry(vsEntry),
	_featureLevel(featureLevel),
	_constantBuffers({ nullptr }),
	_shader(nullptr),
	_errorBlob(nullptr),
	_shaderBlob(nullptr)
{
	UNREFERENCED_PARAMETER(dummy);
	_compileShaderFromFile(path);
	_generateInputLayout(inputLayout);
}

void Engine3DRadSpace::Graphics::IShader::SetData(unsigned index, void *data, unsigned dataSize)
{
	if (_constantBuffers[index].Get() == nullptr)
	{
		D3D11_BUFFER_DESC constantBufferDesc{};
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.ByteWidth = dataSize;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA res{};
		res.pSysMem = data;

		HRESULT r = _device->_device->CreateBuffer(&constantBufferDesc, &res, _constantBuffers[index].GetAddressOf());
		Logging::RaiseFatalErrorIfFailed(r, "Failed to create a constant buffer for a shader!");
	}
	else
	{
		D3D11_MAPPED_SUBRESOURCE res{};
		res.pData = data;
		res.DepthPitch = dataSize;

		HRESULT r = _device->_context->Map(_constantBuffers[index].Get(), 0, D3D11_MAP_WRITE, 0, &res);
		Logging::RaiseFatalErrorIfFailed(r, "Failed to write the shader data!");
	}
}

void Engine3DRadSpace::Graphics::IShader::SetTexture(unsigned index, Texture2D *texture)
{
	switch (_type)
	{
		case ShaderType::VertexShader:
		{
			_device->_context->VSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::HullShader:
		{
			_device->_context->HSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::DomainShader:
		{
			_device->_context->DSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::GeometryShader:
		{
			_device->_context->GSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::PixelShader:
		{
			_device->_context->PSSetShaderResources(index, 1, nullptr);
			break;
		}
		default:
			break;
	}
}

Engine3DRadSpace::Graphics::ShaderFeatureLevel Engine3DRadSpace::Graphics::IShader::GetFeatureLevel()
{
	return _featureLevel;
}

Engine3DRadSpace::Graphics::ShaderType Engine3DRadSpace::Graphics::IShader::GetType()
{
	return _type;
}

std::string Engine3DRadSpace::Graphics::IShader::GetEntryName()
{
	return std::string(_entry);
}

Engine3DRadSpace::Graphics::IShader::~IShader()
{

}
