#pragma once
#include "../Reflection/IReflectedField.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Represents the reflection data of a shader variable, which is a field in a constant buffer.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ShaderVariable final: public Reflection::IReflectedField
	{
		int _idxCbuffer;
	public:
		/// <summary>
		/// Constructs an shader variable reflection data with the given name, constant buffer index, offset, and size.
		/// </summary>
		/// <param name="name">The name of the shader variable.</param>
		/// <param name="idxCbuffer">The index of the constant buffer that this shader variable belongs to.</param>
		/// <param name="offset">The offset of the shader variable within the constant buffer.</param>
		/// <param name="size">The size of the shader variable.</param>
		ShaderVariable(
			const std::string& name,
			int idxCbuffer,
			size_t offset,
			size_t size
		);

		virtual const void* Get(void* objPtr) const override;
		/// <summary>
		/// Sets the value of this shader variable in the given object pointer to the specified value.
		/// </summary>
		/// <param name="objPtr">A pointer to the constant buffer.</param>
		/// <param name="value">A pointer to the value to set.</param>
		virtual void Set(void* objPtr, const void* value) const override;

		const void* DefaultValue() const override;
		/// <summary>
		/// Returns an empty field representation, as shader variables aren't serializable in an editor.
		/// </summary>
		Reflection::FieldRepresentation Representation() const override;

		/// <summary>
		///	Returns the id of the constant buffer that this shader variable belongs to.
		/// </summary>
		/// <returns></returns>
		int ConstantBuffer() const noexcept;

		/// <summary>
		/// Creates a deep clone of this shader variable reflection data.
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<Reflection::IReflectedField> Clone() const override;

		~ShaderVariable() override = default;
	};
}