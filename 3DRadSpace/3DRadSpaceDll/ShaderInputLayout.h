#pragma once
#include "Globals.h"

#ifdef __DIRECTXVER

#include <d3d11.h>
#include "Shader.h"

namespace Engine3DRadSpace
{
	class DLLEXPORT Shader;

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

	class DLLEXPORT ShaderInputLayout
	{
		D3D11_INPUT_ELEMENT_DESC* _inputelements;
		ID3D11InputLayout* _layout;
		size_t _num_elements;
	public:
		ShaderInputLayout(const std::vector<InputLayoutElement>& list);
		void CreateInputLayout(ID3D11Device* device, const void* shader, size_t shadersize);
		void CreateInputLayout(ID3D11Device* device, const Shader* shader);
		void SetInputLayout(ID3D11DeviceContext* context);

		~ShaderInputLayout();
	};
}
#endif