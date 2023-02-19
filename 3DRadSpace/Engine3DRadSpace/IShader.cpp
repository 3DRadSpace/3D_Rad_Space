#include "IShader.hpp"
#include "Error.hpp"
#include "Warning.hpp"

void Engine3DRadSpace::Graphics::IShader::_determineTarget(char* target, size_t lenStr)
{
	switch (type)
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
			Engine3DRadSpace::Logging::RaiseFatalError({ -1,"Unknown shader type!",&type });
			break;
	}

	switch (featureLevel)
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

#ifdef _DEBUG
	const UINT shaderFlags = D3DCOMPILE_DEBUG;
#else
	const UINT shaderFlags = 0;
#endif

	HRESULT r = D3DCompile(
		source,
		strlen(source),
		nullptr,
		nullptr,
		nullptr,
		entry.c_str(),
		target,
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);
	if(errorBlob.Get() != nullptr)
	{
		Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(
			r,
			(std::string("Shader compilation failure! \r\n") + static_cast<char*>(errorBlob->GetBufferPointer())).c_str(),
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

#ifdef _DEBUG
	const UINT shaderFlags = D3DCOMPILE_DEBUG;
#else
	const UINT shaderFlags = 0;
#endif

	HRESULT r = D3DCompileFromFile(
		wpath,
		nullptr,
		nullptr,
		entry.c_str(),
		target,
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);
	if(errorBlob.Get() == nullptr) Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Shader file not found!", path);
	else
	{
		Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(
			r,
			(std::string("Shader compilation failure! \r\n") + static_cast<char*>(errorBlob->GetBufferPointer())).c_str(),
			path
		);
	}

	_createShader();
#endif
}

void Engine3DRadSpace::Graphics::IShader::_createShader()
{
	switch (type)
	{
		case ShaderType::VertexShader:
			device->device->CreateVertexShader(
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11VertexShader**>(this->shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::HullShader:
			device->device->CreateHullShader(
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11HullShader**>(this->shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::DomainShader:
			device->device->CreateDomainShader(
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11DomainShader**>(this->shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::GeometryShader:
			device->device->CreateGeometryShader(
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11GeometryShader**>(this->shader.ReleaseAndGetAddressOf())
			);
			break;
		case ShaderType::PixelShader:
			device->device->CreatePixelShader(
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(),
				nullptr,
				reinterpret_cast<ID3D11PixelShader**>(this->shader.ReleaseAndGetAddressOf())
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

	HRESULT r = device->device->CreateInputLayout(
		elements,
		static_cast<UINT>(inputLayout.size()),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&this->inputLayout
	);
	delete[] elements;

	Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(r, "Failed to create the input layout!");
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice *device, ShaderType type, const char *shaderSourceCode,const char* entry, ShaderFeatureLevel featureLevel):
	device(device),
	type(type),
	entry(entry),
	featureLevel(featureLevel),
	constantBuffers({ nullptr })
{
	_compileShader(shaderSourceCode);
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice *device, std::span<InputLayoutElement> inputLayout, const char *shaderSourceCode, const char *vsEntry, ShaderFeatureLevel featureLevel):
	device(device),
	type(ShaderType::VertexShader),
	entry(vsEntry),
	featureLevel(featureLevel),
	constantBuffers({ nullptr })
{
	_compileShader(shaderSourceCode);
	_generateInputLayout(inputLayout);
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice* device, ShaderType type, const char* path, const char* entry, int dummy, ShaderFeatureLevel featureLevel):
	device(device),
	type(type),
	entry(entry),
	featureLevel(featureLevel),
	constantBuffers({ nullptr }),
	shader(),
	errorBlob(),
	shaderBlob()
{
	UNREFERENCED_PARAMETER(dummy);
	_compileShaderFromFile(path);
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice* device, std::span<InputLayoutElement> inputLayout, const char* path, const char* vsEntry, int dummy, ShaderFeatureLevel featureLevel):
	device(device),
	type(ShaderType::VertexShader),
	entry(vsEntry),
	featureLevel(featureLevel),
	constantBuffers({ nullptr }),
	shader(nullptr),
	errorBlob(nullptr),
	shaderBlob(nullptr)
{
	UNREFERENCED_PARAMETER(dummy);
	_compileShaderFromFile(path);
	_generateInputLayout(inputLayout);
}

void Engine3DRadSpace::Graphics::IShader::SetData(unsigned index, void *data, unsigned dataSize)
{
	if (constantBuffers[index].Get() == nullptr)
	{
		D3D11_BUFFER_DESC constantBufferDesc{};
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.ByteWidth = dataSize;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA res{};
		res.pSysMem = data;

		HRESULT r = device->device->CreateBuffer(&constantBufferDesc, &res, constantBuffers[index].GetAddressOf());
		Logging::RaiseFatalErrorIfFailed(r, "Failed to create a constant buffer for a shader!");
	}
	else
	{
		D3D11_MAPPED_SUBRESOURCE res{};
		res.pData = data;
		res.DepthPitch = dataSize;

		HRESULT r = device->context->Map(constantBuffers[index].Get(), 0, D3D11_MAP_WRITE, 0, &res);
		Logging::RaiseFatalErrorIfFailed(r, "Failed to write the shader data!");
	}
}

void Engine3DRadSpace::Graphics::IShader::SetTexture(unsigned index, Texture2D *texture)
{
	switch (type)
	{
		case ShaderType::VertexShader:
		{
			device->context->VSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::HullShader:
		{
			device->context->HSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::DomainShader:
		{
			device->context->DSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::GeometryShader:
		{
			device->context->GSSetShaderResources(index, 1, nullptr);
			break;
		}
		case ShaderType::PixelShader:
		{
			device->context->PSSetShaderResources(index, 1, nullptr);
			break;
		}
		default:
			break;
	}
}

Engine3DRadSpace::Graphics::ShaderFeatureLevel Engine3DRadSpace::Graphics::IShader::GetFeatureLevel()
{
	return featureLevel;
}

Engine3DRadSpace::Graphics::ShaderType Engine3DRadSpace::Graphics::IShader::GetType()
{
	return type;
}

std::string Engine3DRadSpace::Graphics::IShader::GetEntryName()
{
	return std::string(entry);
}

Engine3DRadSpace::Graphics::IShader::~IShader()
{

}
