#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
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
		const size_t TypeHash() const noexcept;
		const std::string& FieldName() const noexcept;
		const std::string& FieldDesc() const noexcept;
		const size_t TypeSize() const noexcept;
		const ptrdiff_t FieldOffset() const noexcept;

		virtual const void* Get(void* objPtr) const = 0;
		virtual void Set(void* objPtr, const void* value) const = 0;

		template<typename T>
		T GetAtOffset(void* objPtr, intptr_t offset)
		{
			return *std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + FieldOffset() + offset));
		}

		virtual const void* DefaultValue() const = 0;

		virtual FieldRepresentation Representation() const = 0;

		virtual std::unique_ptr<IReflectedField> Clone() const = 0;

		virtual ~IReflectedField() = default;
	};
}