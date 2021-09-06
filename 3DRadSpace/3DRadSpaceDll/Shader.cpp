#include "Shader.h"

#ifdef __DIRECTXVER
void Shader::LoadFromFile(const wchar_t* path, const char* entryfunction)
{
	switch (this->_shadertype)
	{
		case ShaderType::Vertex:
		{
			HRESULT res = D3DCompileFromFile(path, nullptr, nullptr, entryfunction, "vs_4_0", 0, 0, &_shadercode, &_errorblob);
			if (FAILED(res))
			{
				throw std::runtime_error("Possible compilation failure!");
			}
			break;
		}
		case ShaderType::Pixel:
		{
			HRESULT res = D3DCompileFromFile(path, nullptr, nullptr, entryfunction, "ps_4_0", 0, 0, &_shadercode, &_errorblob);
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
			HRESULT r = D3DCompile(memory, lenght, "VertexShader", nullptr, nullptr, entryfunction, "vs_4_0", 0, 0, &this->_shadercode, &this->_errorblob);
			if (FAILED(r))
			{
				throw std::runtime_error("Possible compilation error!");
			}
			break;
		}
		case ShaderType::Pixel:
		{
			HRESULT r = D3DCompile(memory, lenght, "PixelShader", nullptr, nullptr, entryfunction, "ps_4_0", 0, 0, &this->_shadercode, &this->_errorblob);
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
			context->VSSetShader((ID3D11VertexShader*)this->_shader, nullptr, 0);
			break;
		}
		case ShaderType::Pixel:
		{
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
	if (_shadercode != nullptr) _shadercode->Release();
	if (_errorblob != nullptr) _errorblob->Release();
	if (_shader != nullptr) _shader->Release();
}
#endif