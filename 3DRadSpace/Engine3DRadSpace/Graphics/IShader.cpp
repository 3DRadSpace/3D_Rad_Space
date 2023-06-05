#include "IShader.hpp"
#include "../Logging/Error.hpp"
#include "../Logging/Warning.hpp"

#ifdef _DX11
#pragma comment(lib,"d3dcompiler.lib")
#endif

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

Array_ValidConstantBuffers IShader::validConstantBuffers(unsigned &numConstantBuffers)
{
	const unsigned maxConstBuffers = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	Array_ValidConstantBuffers ppConstantBuffers = {nullptr};

	unsigned &i = numConstantBuffers;
	for(i = 0; i < maxConstBuffers; i++)
	{
		ID3D11Buffer *constBuffer = constantBuffers[i].Get();
		if(constBuffer == nullptr) break;

		ppConstantBuffers[i] = constBuffer;
	}

	return ppConstantBuffers;
}

void IShader::compileShader(const char *source, const char* target)
{
#ifdef _WIN32
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
		entry,
		target,
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob.Get() != nullptr)
	{
		RaiseFatalErrorIfFailed(
			r,
			(std::string("Shader compilation failure! \r\n") + static_cast<char*>(errorBlob->GetBufferPointer())).c_str(),
			source
		);
	}
	else SetLastWarning(Warning(r, (char*)errorBlob->GetBufferPointer(), 2, nullptr));
#endif
}

void IShader::compileShaderFromFile(const char* path, const char* target)
{
#ifdef _WIN32
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
		entry,
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
		
		SetLastWarning(Warning(r, (char*)errorBlob->GetBufferPointer(), 2, nullptr));
	}
#endif
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice *Device, const char *shaderSourceCode, const char *entry_function, ShaderFeatureLevel fl):
	device(Device),
	entry(entry_function),
	featureLevel(fl),
	constantBuffers({nullptr}),
	shaderBlob(nullptr),
	errorBlob(nullptr)
{
}

Engine3DRadSpace::Graphics::IShader::IShader(GraphicsDevice *Device, const std::filesystem::path &path, const char *entry_function, ShaderFeatureLevel fl) :
	device(Device),
	entry(entry_function),
	featureLevel(fl),
	constantBuffers({nullptr}),
	shaderBlob(nullptr),
	errorBlob(nullptr)
{
}

void IShader::SetData(unsigned index, void *data, unsigned dataSize)
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

		HRESULT r = device->device->CreateBuffer(&constantBufferDesc, &res, constantBuffers[index].ReleaseAndGetAddressOf());
		Logging::RaiseFatalErrorIfFailed(r, "Failed to create a constant buffer for a shader!");
	}
	else
	{
		D3D11_MAPPED_SUBRESOURCE res;
		HRESULT r = device->context->Map(constantBuffers[index].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
		Logging::RaiseFatalErrorIfFailed(r, "Failed to write the shader data!");
		memcpy(res.pData, data, dataSize);
		device->context->Unmap(constantBuffers[index].Get(), 0);
	}
}


ShaderFeatureLevel IShader::GetFeatureLevel()
{
	return featureLevel;
}

std::string IShader::GetEntryName()
{
	return std::string(entry);
}

const char* IShader::GetCompilationErrorsAndWarnings()
{
	if(this->errorBlob == nullptr) return nullptr;
	return static_cast<const char*>(this->errorBlob->GetBufferPointer());
}