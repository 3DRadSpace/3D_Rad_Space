#pragma once
#include "ReflectedField.hpp"
#include "ReflectedEnum.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename E>
	concept ReflectableEnum = std::is_enum_v<E>;

	class DLLEXPORT IReflectedEnumField : public IReflectedField
	{
	protected:
		IReflectedEnumField() = default;
		IReflectedEnumField(const IReflectedEnumField&) = default;
		IReflectedEnumField(IReflectedEnumField&&) = default;

		IReflectedEnumField& operator=(const IReflectedEnumField&) = default;
		IReflectedEnumField& operator=(IReflectedEnumField&&) = default;
	public:
		virtual ReflectedEnum GetEnum() = 0;
		~IReflectedEnumField() = default;
	};

	template<ReflectableEnum E>
	class ReflectedEnumField : public IReflectedEnumField
	{
		std::string _name;
		intptr_t _offset;
		std::string _desc;
		E _defaultValue;
		ReflectedEnum _enum;
	public:
		ReflectedEnumField(const size_t offset_obj_field, const std::string& visibleName, const std::string& description,const ReflectedEnum &enumEntries, E defaultValue):
			_name(visibleName),
			_offset(offset_obj_field),
			_desc(description),
			_defaultValue(defaultValue),
			_enum(enumEntries)
		{
		}

		const size_t TypeHash() const override
		{
			return typeid(E).hash_code();
		}

		const std::string FieldName() const override
		{
			return _name;
		}

		const std::string FieldDesc() const override
		{
			return _desc;
		}

		const size_t TypeSize() const override
		{
			return sizeof(E);
		}

		const ptrdiff_t FieldOffset() const override
		{
			return _offset;
		}

		const void* Get(void* objPtr) const override
		{
			assert(objPtr != nullptr);

			return std::launder<E>(reinterpret_cast<E*>(static_cast<std::byte*>(objPtr) + _offset));
		}

		void Set(void* objPtr, const void* value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			auto lhs = std::launder<E>(reinterpret_cast<E*>(static_cast<std::byte*>(objPtr) + _offset));
			const auto rhs = static_cast<const E*>(value);

			*lhs = *rhs;
		}

		const void* DefaultValue() const override
		{
			return static_cast<void*>(&_defaultValue);
		}

		FieldRepresentation Representation() const override
		{
			return FieldRepresentation({ FieldRepresentationType::Enum, "" });
		}

		ReflectedEnum GetEnum() override
		{
			return _enum;
		}

	};
}