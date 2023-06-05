#include "IVertexShader.hpp"
#include "../Logging/Error.hpp"
#include "../Logging/Warning.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;

const char* IVertexShader::determineTarget()
{
	switch(featureLevel)
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

void IVertexShader::createShader()
{
#ifdef _DX11
	HRESULT r = device->device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		shader.ReleaseAndGetAddressOf()
	);

	if(FAILED(r)) throw std::exception("Failed to compile the shader!");
#endif // _DX11
}

D3D11_INPUT_ELEMENT_DESC *IVertexShader::generateInputElementDesc(std::span<InputLayoutElement> inputLayout)
{
#ifdef _DX11
	size_t numLayoutEntries = inputLayout.size();

	D3D11_INPUT_ELEMENT_DESC *elem = new D3D11_INPUT_ELEMENT_DESC[numLayoutEntries]{};
	if(elem == nullptr)
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

	for(int i = 0; i < numLayoutEntries; i++)
	{
		switch(inputLayout[i])
		{
			case InputLayoutElement::Position_Vec2:
			{
				elem[i] =
				{
					"POSITION", //SemanticName
					posIndex, //SemanticIndex
					DXGI_FORMAT_R32G32_FLOAT, //Format
					0, //InputSlot
					D3D11_APPEND_ALIGNED_ELEMENT, //AlignedByteOffset
					D3D11_INPUT_PER_VERTEX_DATA, //InputSlotClass
					0 //InstanceDataStepRate
				};
				posIndex++;
				break;
			}
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
					"BITANGENT", //SemanticName
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
					"BITANGENT", //SemanticName
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
#endif
}

void IVertexShader::generateInputLayout(std::span<InputLayoutElement> inputLayout)
{
#ifdef _DX11
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
#endif
}

IVertexShader::IVertexShader(Engine3DRadSpace::GraphicsDevice *Device, std::span<InputLayoutElement> inputLayout, const char *shaderSourceCode, const char *vsEntry, ShaderFeatureLevel fl):
	IShader(Device, shaderSourceCode, vsEntry, fl)
{
	compileShader(shaderSourceCode, determineTarget());
	createShader();
	generateInputLayout(inputLayout);
}

IVertexShader::IVertexShader(Engine3DRadSpace::GraphicsDevice *Device, std::span<InputLayoutElement> inputLayout, const std::filesystem::path &path, const char *vsEntry, ShaderFeatureLevel fl):
	IShader(Device, path, vsEntry, fl)
{
	compileShaderFromFile(path.string().c_str(), determineTarget());
	createShader();
	generateInputLayout(inputLayout);
}

void IVertexShader::SetTexture(unsigned index, Texture2D *texture)
{
#ifdef _DX11
	device->context->VSSetShaderResources(index, 1, texture->resourceView.GetAddressOf());
#endif
}

void IVertexShader::SetSampler(unsigned index, SamplerState *samplerState)
{
#ifdef _DX11
	device->context->VSSetSamplers(index, 1, samplerState->samplerState.GetAddressOf());
#endif
}

void IVertexShader::SetShader()
{
#ifdef  _DX11
	unsigned i;
	auto validConstantBuffers = this->validConstantBuffers(i);
	device->context->VSSetConstantBuffers(0, i, validConstantBuffers.data());

	device->context->IASetInputLayout(inputLayout.Get());
	device->context->VSSetShader(shader.Get(), nullptr, 0);
#endif //  _DX11

}
