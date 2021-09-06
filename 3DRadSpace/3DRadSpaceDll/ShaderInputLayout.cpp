#include "ShaderInputLayout.h"

#ifdef __DIRECTXVER
ShaderInputLayout::ShaderInputLayout(const std::vector<InputLayoutElement>& list)
{
	this->_layout = nullptr;
	this->_num_elements = list.size();

	size_t l = list.size();
	this->_inputelements = new D3D11_INPUT_ELEMENT_DESC[l];;
	size_t aglinement = 0;
	unsigned semantic_index_counter[10] = { 0 };

	for (size_t i = 0; i < l; i++)
	{
		InputLayoutElement elem = list[i];
		switch (elem)
		{
			case InputLayoutElement::Position:
			{
				this->_inputelements[i] = { "POSITION",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
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
				this->_inputelements[i] = { "COLOR",semantic_index_counter[(uint8_t)elem],DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,0,aglinement,D3D11_INPUT_PER_VERTEX_DATA,0 };
				semantic_index_counter[(uint8_t)elem]++;
				aglinement += sizeof(float) * 4;
				break;
			}
			default:break;
		}
	}
}

void ShaderInputLayout::CreateInputLayout(ID3D11Device* device,const void * shader,size_t shadersize)
{
	HRESULT r = device->CreateInputLayout(this->_inputelements, this->_num_elements, shader, shadersize, &this->_layout);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create the input layout!");
	}
}

void ShaderInputLayout::CreateInputLayout(ID3D11Device* device, const Shader* shader)
{
	ID3DBlob* sh_by = shader->GetShaderBlob();
	HRESULT r = device->CreateInputLayout(this->_inputelements, this->_num_elements, sh_by->GetBufferPointer(), sh_by->GetBufferSize(), &this->_layout);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create the input layout!");
	}
}

void ShaderInputLayout::SetInputLayout(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(this->_layout);
}

ShaderInputLayout::~ShaderInputLayout()
{
	if (this->_layout != nullptr) this->_layout->Release();
	delete this->_inputelements;
}
#endif