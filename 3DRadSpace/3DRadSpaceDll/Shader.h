#pragma once
#include "Globals.h"

#ifdef __DIRECTXVER

#include <d3d11.h>

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include "Game.h"
#include "ShaderInputLayout.h"
#include "Texture2D.h"

enum class ShaderType : uint8_t
{
	Compute,
	Vertex,
	Hull,
	Domain,
	Geometry,
	Pixel,
};

class DLLEXPORT ShaderInputLayout;

class DLLEXPORT Shader
{
	ID3DBlob* _shadercode;
	ID3DBlob* _errorblob;
	ID3D11DeviceChild* _shader;
	ShaderType _shadertype;
	bool _shadercreated;
	bool _shadercompiled;

	ID3D11Buffer* _constantbuffer;
	void* _constantbufferstruct;
	bool _constantbuffercreated;
public:
	Shader(ShaderType t) : _shadertype(t), _shadercode(nullptr), _errorblob(nullptr),_shadercreated(nullptr),_shader(nullptr), _shadercompiled(false), _constantbuffercreated(false), _constantbuffer(nullptr),_constantbufferstruct(nullptr){};
	
	void LoadFromFile(const wchar_t* path, const char* entryfunction);
	void LoadFromMemory(const char* memory, size_t lenght, const char* entryfunction);
	void CompileShader(ID3D11Device* device);
	void SetShader(ID3D11DeviceContext* context);

	void CreateInputLayout(ID3D11Device* device, ShaderInputLayout* input);
	void SetInputLayout(ID3D11DeviceContext *context,ShaderInputLayout *input);

	void SetShaderParametersLayout(ID3D11Device* device ,ID3D11DeviceContext *context,size_t size);

	void SetShaderParameters(ID3D11DeviceContext* context, void* arguments, size_t size);

	void SetShaderTexture(ID3D11DeviceContext* context, Texture2D* texture);
	void SetShaderTextures(ID3D11DeviceContext* context, Texture2D** textures, size_t numtextures);

	template <class P>
	void SetShaderParameters(ID3D11DeviceContext* context, P* arguments);

	ID3DBlob* GetShaderBlob() const;
	ID3DBlob* GetErrorBlob() const;

	~Shader();
};

template<class P>
inline void Shader::SetShaderParameters(ID3D11DeviceContext* context, P* arguments)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	context->Map(this->_constantbuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	memcpy(mappedSubresource.pData, arguments, sizeof(P));
	context->Unmap(this->_constantbuffer, 0);
}

#endif // __DIRECTXVER