#pragma once
#include "Globals.hpp"

#ifdef __DIRECTXVER

#include <d3d11.h>

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include "Game.hpp"
#include "ShaderInputLayout.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace
{
	enum class InputLayoutElement : uint8_t; //forward declaration is needed and I don't know why

	/// <summary>
	/// Represents the shader type
	/// </summary>
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

	/// <summary>
	/// Represents a shader (pixel, fragment, compute, etc)
	/// </summary>
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

		ShaderInputLayout* layout;
		bool _layoutcreated;
	public:
		/// <summary>
		/// Constructs a shader that is unloaded
		/// </summary>
		/// <param name="t">Shader type</param>
		explicit Shader(ShaderType t) :
			_shadertype(t), _shadercode(nullptr), _errorblob(nullptr), _shadercreated(nullptr), _shader(nullptr), _shadercompiled(false),
			_constantbuffercreated(false), _constantbuffer(nullptr), _constantbufferstruct(nullptr), _layoutcreated(false), layout(nullptr) {};
		/// <summary>
		/// Loads the shader from a file
		/// </summary>
		/// <param name="path">Path to shader file</param>
		/// <param name="entryfunction">Shader entry function</param>
		void LoadFromFile(const wchar_t* path, const char* entryfunction);
		/// <summary>
		/// Loads a shader from the memory
		/// </summary>
		/// <param name="memory">Memory buffer</param>
		/// <param name="lenght">Memory buffer size</param>
		/// <param name="entryfunction">Shader entry function name</param>
		void LoadFromMemory(const char* memory, size_t lenght, const char* entryfunction);
		/// <summary>
		/// Compiles the shader
		/// </summary>
		/// <param name="device"></param>
		void CompileShader(ID3D11Device* device);
		/// <summary>
		/// Sets the shader to the command list
		/// </summary>
		/// <param name="context">Graphics handle</param>
		void SetShader(ID3D11DeviceContext* context);

		/// <summary>
		/// Creates the input layout used for the shader to parse the types
		/// </summary>
		/// <param name="device">Device handle</param>
		/// <param name="list">List of input layout elements</param>
		void CreateInputLayout(ID3D11Device* device, const std::vector<InputLayoutElement>& list);
		/// <summary>
		/// Sets the input layout elements
		/// </summary>
		/// <param name="context"></param>
		void SetInputLayout(ID3D11DeviceContext* context);

		/// <summary>
		/// Prepares the shader constant buffer
		/// </summary>
		/// <param name="device">Device handle</param>
		/// <param name="context">Device handle</param>
		/// <param name="size">Size of the constant buffer</param>
		void SetShaderParametersLayout(ID3D11Device* device, ID3D11DeviceContext* context, size_t size);

		/// <summary>
		/// Sets values in the shader constant buffer
		/// </summary>
		/// <param name="context">Device handle</param>
		/// <param name="arguments">Values in the constant buffer</param>
		/// <param name="size">Size of the values</param>
		void SetShaderParameters(ID3D11DeviceContext* context, void* arguments, size_t size);

		/// <summary>
		/// Sets a texture inside the shader
		/// </summary>
		/// <param name="context">Device handle</param>
		/// <param name="texture">2D texture for the shader</param>
		void SetShaderTexture(ID3D11DeviceContext* context, Texture2D* texture);
		/// <summary>
		/// Sets multiple texture in the shader.
		/// </summary>
		/// <param name="context">Device handle</param>
		/// <param name="textures">Array of textures</param>
		/// <param name="numtextures">Number of textures that are being used in the shader</param>
		void SetShaderTextures(ID3D11DeviceContext* context, Texture2D** textures, size_t numtextures);

		/// <summary>
		/// Sets values in the shader constant buffer with a predefined type
		/// </summary>
		/// <typeparam name="P">The given struct</typeparam>
		/// <param name="context">Device handle</param>
		/// <param name="arguments">Data</param>
		template <class P>
		void SetShaderParameters(ID3D11DeviceContext* context, P* arguments);

		/// <summary>
		/// Gets the compiled shader code
		/// </summary>
		/// <returns></returns>
		ID3DBlob* GetShaderBlob() const;
		/// <summary>
		/// Gets the compilation code if any
		/// </summary>
		/// <returns></returns>
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
}
#endif // __DIRECTXVER