#pragma once
#include "../Reflection/IReflectedField.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IVertexShader
	{
	protected:
		IVertexShader() = default;

		IVertexShader(const IVertexShader&) = delete;
		IVertexShader& operator=(const IVertexShader&) = delete;

		IVertexShader(IVertexShader&&) noexcept = default;
		IVertexShader& operator=(IVertexShader&&) noexcept = default;
	public:
		/// <summary>
		/// Returns a description of the vertex input layout required by this vertex shader.
		/// </summary>
		/// <returns>A copy of the input layout description.</returns>
		virtual std::vector<Reflection::IReflectedField*> GetInputLayout() const noexcept = 0;

		virtual ~IVertexShader() = default;
	};
}