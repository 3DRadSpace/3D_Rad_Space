#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Metadata interface for a reflected field.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT IReflectedField
	{
	protected:
		size_t _typeHash;
		std::type_index _typeIndex;

		size_t _size;
		size_t _offset;
		std::string _name;
		std::string _desc;

		IReflectedField() = default;
		IReflectedField(size_t offset, size_t size, const std::string& name, const std::string& desc, const std::type_info& info);

		IReflectedField(const IReflectedField& f) = default;
		IReflectedField(IReflectedField&&) = default;

		IReflectedField& operator=(const IReflectedField& f) = default;
		IReflectedField& operator=(IReflectedField&& f) = default;
	public:
		/// <summary>
		/// Type hash of the field's type, usually typeid(T).hash_code() for the field's type T.
		/// </summary>
		/// <returns></returns>
		const size_t TypeHash() const noexcept;
		/// <summary>
		/// Name of the field.
		/// </summary>
		/// <returns>Field name</returns>
		const std::string& FieldName() const noexcept;
		/// <summary>
		/// Description of the field.
		/// </summary>
		/// <returns>Field description</returns>
		const std::string& FieldDesc() const noexcept;
		/// <summary>
		/// Size of the field's type in bytes.
		/// </summary>
		/// <returns>Size of the field's type in bytes</returns>
		const size_t TypeSize() const noexcept;
		/// <summary>
		/// Offset of the field within the object, in bytes.
		/// </summary>
		/// <returns>Offset of the field within the object, in bytes</returns>
		const ptrdiff_t FieldOffset() const noexcept;
		/// <summary>
		/// Gets the value of the field from the given object pointer.
		/// </summary>
		/// <param name="objPtr">Pointer to the object containing the field.</param>
		/// <returns>Pointer to the field's value.</returns>
		virtual const void* Get(void* objPtr) const = 0;
		/// <summary>
		///  Sets the value of the field in the given object pointer.
		/// </summary>
		/// <param name="objPtr">Pointer to the object containing the field</param>
		/// <param name="value">value to be set</param>
		virtual void Set(void* objPtr, const void* value) const = 0;
		/// <summary>
		/// Gets the type T with an additional offset from the field's offset within the object.
		/// </summary>
		/// <typeparam name="T">Type</typeparam>
		/// <param name="objPtr">Object containing this field</param>
		/// <param name="offset">additional offset in bytes</param>
		/// <returns></returns>
		template<typename T>
		T GetAtOffset(void* objPtr, intptr_t offset)
		{
			return *std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + FieldOffset() + offset));
		}
		/// <summary>
		/// Returns a pointer to the default value of the field's type.
		/// </summary>
		/// <returns>Pointer to the default value of the field's type</returns>
		virtual const void* DefaultValue() const = 0;
		/// <summary>
		/// Returns the field representation type.
		/// </summary>
		/// <returns>Field representation type</returns>
		virtual FieldRepresentation Representation() const = 0;
		/// <summary>
		/// Performs a deep copy of this instance.
		/// </summary>
		/// <returns>Unique pointer to a deep clone.</returns>
		virtual std::unique_ptr<IReflectedField> Clone() const = 0;

		virtual ~IReflectedField() = default;
	};
}