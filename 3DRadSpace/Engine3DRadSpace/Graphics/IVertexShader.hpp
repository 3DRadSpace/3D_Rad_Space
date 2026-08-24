#pragma once
#include "../Reflection/IReflectedField.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Represents an interface for a vertex shader. A IVertexShader is guaranteed to be a IShader.
	/// </summary>
	/// <remarks>
	/// The interface is detached from the IShader interface to fix an diamond issue.
	/// </remarks>
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