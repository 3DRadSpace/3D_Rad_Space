#pragma once
#include "Globals.h"

#ifdef __DIRECTXVER

#include <d3d11.h>

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include "Game.h"
#include "ShaderInputLayout.h"

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
public:
	Shader(ShaderType t) : _shadertype(t), _shadercode(nullptr), _errorblob(nullptr),_shadercreated(nullptr),_shader(nullptr), _shadercompiled(false){};
	
	void LoadFromFile(const wchar_t* path, const char* entryfunction);
	void LoadFromMemory(const char* memory, size_t lenght, const char* entryfunction);
	void CompileShader(ID3D11Device* device);
	void SetShader(ID3D11DeviceContext* context);

	void CreateInputLayout(ID3D11Device* device, ShaderInputLayout* input);
	void SetInputLayout(ID3D11DeviceContext *context,ShaderInputLayout *input);

	//void SetShaderParameters(...);

	ID3DBlob* GetShaderBlob() const;
	ID3DBlob* GetErrorBlob() const;

	~Shader();
};

#endif // __DIRECTXVER

