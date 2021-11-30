#pragma once
#include "Globals.hpp"

#ifdef __DIRECTXVER

#include <d3d11.h>
#include "Shader.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT Shader;

	/// <summary>
	/// Represents a input layout element type
	/// </summary>
	enum class InputLayoutElement : uint8_t
	{
		Position = 1,
		PositionTransformed,
		Color,
		Normal,
		Binormal,
		Tangent,
		TexureCoordinate,
		BlendIndicies,
		BlendWeight,
		PointSize,
	};

	class DLLEXPORT Shader;

	/// <summary>
	/// Represents a shader input layout
	/// </summary>
	class DLLEXPORT ShaderInputLayout
	{
		D3D11_INPUT_ELEMENT_DESC* _inputelements;
		ID3D11InputLayout* _layout;
		size_t _num_elements;
	public:
		/// <summary>
		/// Constructs a shader input layout from the given list of elements
		/// </summary>
		/// <param name="list"></param>
		explicit ShaderInputLayout(const std::vector<InputLayoutElement>& list);
		/// <summary>
		/// Creates the shader input layout in the GPU
		/// </summary>
		/// <param name="device">Device handle</param>
		/// <param name="shader">Shader used for the input layout</param>
		/// <param name="shadersize">Size of the shader</param>
		void CreateInputLayout(ID3D11Device* device, const void* shader, size_t shadersize);
		/// <summary>
		/// Creates the shader input layout in the GPU
		/// </summary>
		/// <param name="device">Device handle</param>
		/// <param name="shader">Shader used for the input layout</param>
		void CreateInputLayout(ID3D11Device* device, const Shader* shader);
		/// <summary>
		/// Sets the input layout in the GPU, so it can bs used by the shader.
		/// </summary>
		/// <param name="context"></param>
		void SetInputLayout(ID3D11DeviceContext* context);

		~ShaderInputLayout();
	};
}
#endif