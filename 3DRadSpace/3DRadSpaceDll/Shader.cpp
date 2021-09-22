#include "Shader.h"

#ifdef __DIRECTXVER
void Shader::LoadFromFile(const wchar_t* path, const char* entryfunction)
{
	switch (this->_shadertype)
	{
		case ShaderType::Vertex:
		{
			HRESULT res = D3DCompileFromFile(path, nullptr, nullptr, entryfunction, "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &_shadercode, &_errorblob);
			if (FAILED(res))
			{
				throw std::runtime_error("Possible compilation failure!");
			}
			break;
		}
		case ShaderType::Pixel:
		{
			HRESULT res = D3DCompileFromFile(path, nullptr, nullptr, entryfunction, "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &_shadercode, &_errorblob);
			if (FAILED(res))
			{
				throw std::runtime_error("Possible compilation failure!");
			}
			break;
		}
		default:
		{
			throw std::logic_error("Unknown shader type to be compiled." + std::to_string((uint8_t)this->_shadertype));
		}
	}
}

void Shader::LoadFromMemory(const char* memory, size_t lenght, const char* entryfunction)
{
	if (this->_shadercreated) return;
	switch (this->_shadertype)
	{
		case ShaderType::Vertex:
		{
			HRESULT r = D3DCompile(memory, lenght, "VertexShader", nullptr, nullptr, entryfunction, "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &this->_shadercode, &this->_errorblob);
			if (FAILED(r))
			{
				throw std::runtime_error("Possible compilation error!");
			}
			break;
		}
		case ShaderType::Pixel:
		{
			HRESULT r = D3DCompile(memory, lenght, "PixelShader", nullptr, nullptr, entryfunction, "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &this->_shadercode, &this->_errorblob);
			if (FAILED(r))
			{
				throw std::runtime_error("Possible compilation error!");
			}
			break;
		}
		default: break;
	}
	this->_shadercreated = true;
}

void Shader::CompileShader(ID3D11Device* device)
{
	if (this->_shadercompiled) return;
	switch (this->_shadertype)
	{
		case ShaderType::Vertex:
		{
			HRESULT r = device->CreateVertexShader(_shadercode->GetBufferPointer(), _shadercode->GetBufferSize(), nullptr, (ID3D11VertexShader**)&this->_shader);
			if (FAILED(r))
			{
				throw std::runtime_error("Failed to set the vertex shader!");
			}
			break;
		}
		case ShaderType::Pixel:
		{
			HRESULT r = device->CreatePixelShader(_shadercode->GetBufferPointer(), _shadercode->GetBufferSize(), nullptr, (ID3D11PixelShader**)&this->_shader);
			if (FAILED(r))
			{
				throw std::runtime_error("Failed to set the pixel shader!");
			}
			break;
		}
		default: break; //How did we even reach this part???
	}
	this->_shadercompiled = true;
}

void Shader::SetShader(ID3D11DeviceContext* context)
{
	switch (this->_shadertype)
	{
		case ShaderType::Vertex:
		{
			if(this->_constantbuffercreated) context->VSSetConstantBuffers(0, 1, &this->_constantbuffer);
			context->VSSetShader((ID3D11VertexShader*)this->_shader, nullptr, 0);
			break;
		}
		case ShaderType::Pixel:
		{
			if (this->_constantbuffercreated) context->PSGetConstantBuffers(0, 1, &this->_constantbuffer);
			context->PSSetShader((ID3D11PixelShader*)this->_shader, nullptr, 0);
			break;
		}
		default: break;
	}
}

void Shader::CreateInputLayout(ID3D11Device* device, ShaderInputLayout* input)
{
	input->CreateInputLayout(device, this->_shadercode->GetBufferPointer(), this->_shadercode->GetBufferSize());
}

void Shader::SetInputLayout(ID3D11DeviceContext* context, ShaderInputLayout* input)
{
	input->SetInputLayout(context);
}

void Shader::SetShaderParametersLayout(ID3D11Device* device, ID3D11DeviceContext* context, size_t size)
{
	if (this->_constantbuffercreated) return;
	D3D11_BUFFER_DESC constantBuffer;
	memset(&constantBuffer, 0, sizeof(D3D11_BUFFER_DESC));
	constantBuffer.ByteWidth = size;
	constantBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	constantBuffer.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	constantBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	this->_constantbufferstruct = malloc(size); //initialize unused memory

	D3D11_SUBRESOURCE_DATA constantBufferNullVals;
	memset(&constantBufferNullVals, 0, sizeof(D3D11_SUBRESOURCE_DATA));
	constantBufferNullVals.pSysMem = this->_constantbufferstruct;

	HRESULT r = device->CreateBuffer(&constantBuffer, &constantBufferNullVals, &this->_constantbuffer);
	if (FAILED(r))
		throw ResourceCreationException("Failed to create shader arguments", typeid(ID3D11Buffer));

	this->_constantbuffercreated = true;

	switch (this->_shadertype)
	{
		case ShaderType::Compute:
		{
			context->CSSetConstantBuffers(0, 1, &this->_constantbuffer);
			break;
		}
		case ShaderType::Vertex:
		{
			context->VSSetConstantBuffers(0, 1, &this->_constantbuffer);
			break;
		}
		case ShaderType::Hull:
		{
			context->HSSetConstantBuffers(0, 1, &this->_constantbuffer);
			break;
		}
		case ShaderType::Domain:
		{
			context->DSSetConstantBuffers(0, 1, &this->_constantbuffer);
			break;
		}
		case ShaderType::Geometry:
		{
			context->GSSetConstantBuffers(0, 1, &this->_constantbuffer);
			break;
		}
		case ShaderType::Pixel:
		{
			context->PSSetConstantBuffers(0, 1, &this->_constantbuffer);
			break;
		}
		default: break;
	}
}

void Shader::SetShaderParameters(ID3D11DeviceContext* context, void* arguments, size_t size)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	context->Map(this->_constantbuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	memcpy(mappedSubresource.pData, arguments, size);
	context->Unmap(this->_constantbuffer, 0);
}

void Shader::SetShaderTexture(ID3D11DeviceContext* context, Texture2D* texture)
{
	ID3D11ShaderResourceView* srv = texture->GetShaderResourceView();

	switch (this->_shadertype)
	{
		case ShaderType::Compute:
		{
			context->CSSetShaderResources(0, 1,&srv);
			break;
		}
		case ShaderType::Vertex:
		{
			context->VSSetShaderResources(0, 1, &srv);
			break;
		}
		case ShaderType::Hull:
		{
			context->HSSetShaderResources(0, 1, &srv);
			break;
		}
		case ShaderType::Domain:
		{
			context->DSSetShaderResources(0, 1, &srv);
			break;
		}
		case ShaderType::Geometry:
		{
			context->GSSetShaderResources(0, 1, &srv);
			break;
		}
		case ShaderType::Pixel:
		{
			context->PSSetShaderResources(0, 1, &srv);
			break;
		}
		default: break;
	}
}

void Shader::SetShaderTextures(ID3D11DeviceContext* context, Texture2D** textures, size_t numtextures)
{
	ID3D11ShaderResourceView** srv = new ID3D11ShaderResourceView *[numtextures];
	for (unsigned i = 0; i < numtextures; i++)
	{
		srv[i] = textures[i]->GetShaderResourceView();
	}

	switch (this->_shadertype)
	{
		case ShaderType::Compute:
		{
			context->CSSetShaderResources(0, numtextures, srv);
			break;
		}
		case ShaderType::Vertex:
		{
			context->VSSetShaderResources(0, numtextures, srv);
			break;
		}
		case ShaderType::Hull:
		{
			context->HSSetShaderResources(0, numtextures, srv);
			break;
		}
		case ShaderType::Domain:
		{
			context->DSSetShaderResources(0, numtextures, srv);
			break;
		}
		case ShaderType::Geometry:
		{
			context->GSSetShaderResources(0, numtextures, srv);
			break;
		}
		case ShaderType::Pixel:
		{
			context->PSSetShaderResources(0,numtextures, srv);
			break;
		}
		default: break;
	}
	delete[] srv; //inb4 it is segfault time
}

ID3DBlob* Shader::GetShaderBlob() const
{
	return this->_shadercode;
}

ID3DBlob* Shader::GetErrorBlob() const
{
	return this->_errorblob;
}

Shader::~Shader()
{
	if (this->_shadercode != nullptr) this->_shadercode->Release();
	if (this->_errorblob != nullptr) this->_errorblob->Release();
	if (this->_shader != nullptr) this->_shader->Release();
	if (this->_constantbuffer != nullptr) this->_constantbuffer->Release();
	if (this->_constantbufferstruct != nullptr) free(this->_constantbufferstruct);
}
#endif