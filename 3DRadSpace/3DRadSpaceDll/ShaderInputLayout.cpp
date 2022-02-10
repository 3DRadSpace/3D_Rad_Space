#include "ShaderInputLayout.hpp"

#ifdef __DIRECTXVER
Engine3DRadSpace::ShaderInputLayout::ShaderInputLayout(const std::vector<InputLayoutElement>& list)
{
	this->_layout = nullptr;
	this->_num_elements = list.size();

	size_t l = list.size();
	this->_inputelements = new D3D11_INPUT_ELEMENT_DESC[l];;
	unsigned aglinement = 0;
	unsigned semantic_index_counter[11] = { 0 };

	for (size_t i = 0; i < l; i++)
	{
		InputLayoutElement elem = list[i];
		switch (elem)
		{
			case InputLayoutElement::Position:
			{
				this->_inputelements[i] = { "POSITION",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 3;
				break;
			}
			case InputLayoutElement::Color:
			{
				this->_inputelements[i] = { "COLOR",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
				break;
			}
			case InputLayoutElement::TexureCoordinate:
			{
				this->_inputelements[i] = { "TEXCOORD",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
				break;
			}
			case InputLayoutElement::Normal:
			{
				this->_inputelements[i] = { "NORMAL",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
				break;
			}
			case InputLayoutElement::Tangent:
			{
				this->_inputelements[i] = { "TANGENT",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
				break;
			}
			case InputLayoutElement::Binormal:
			{
				this->_inputelements[i] = { "BINORMAL",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
				break;
			}
			case InputLayoutElement::PointSize:
			{
				this->_inputelements[i] = { "PSIZE",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float);
				break;
			}
			case InputLayoutElement::BlendIndicies:
			{
				this->_inputelements[i] = { "BLENDINDICES",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32_UINT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float);
				break;
			}
			case InputLayoutElement::BlendWeight:
			{
				this->_inputelements[i] = { "BLENDWEIGHT",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float);
				break;
			}
			default:break;
		}
	}
}

void Engine3DRadSpace::ShaderInputLayout::CreateInputLayout(ID3D11Device* device,const void * shader,size_t shadersize)
{
	HRESULT r = device->CreateInputLayout(this->_inputelements, this->_num_elements, shader, shadersize, &this->_layout);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create the input layout!");
	}
}

void Engine3DRadSpace::ShaderInputLayout::CreateInputLayout(ID3D11Device* device, const Shader* shader)
{
	ID3DBlob* sh_by = shader->GetShaderBlob();
	HRESULT r = device->CreateInputLayout(this->_inputelements, this->_num_elements, sh_by->GetBufferPointer(), sh_by->GetBufferSize(), &this->_layout);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create the input layout!");
	}
}

void Engine3DRadSpace::ShaderInputLayout::SetInputLayout(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(this->_layout);
}

Engine3DRadSpace::ShaderInputLayout::~ShaderInputLayout()
{
	if (this->_layout != nullptr) this->_layout->Release();
	delete this->_inputelements;

	this->_layout = nullptr;
	this->_inputelements = nullptr;
}
#endif