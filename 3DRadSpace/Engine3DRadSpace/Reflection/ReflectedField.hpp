#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
	class DLLEXPORT IReflectedField
	{
	public:
		virtual const size_t TypeHash() const = 0;
		virtual const std::string FieldName() const = 0;
		virtual const std::string FieldDesc() const = 0;
		virtual const size_t TypeSize() const = 0;
		virtual const ptrdiff_t FieldOffset() const = 0;

		virtual void *Get(void *objPtr) const = 0;
		virtual void Set(void *objPtr, void *value) const = 0;

		virtual const void *DefaultValue() const = 0;

		virtual FieldRepresentation Representation() const = 0;

		virtual ~IReflectedField() = default;
	};

	template<ReflectableType T>
	class ReflectedField : public IReflectedField
	{
		const size_t _offset;
		const std::string _name;
		const std::string _desc;
		const T _defaultVal;
	public:
		ReflectedField(const size_t offset_obj_field,const std::string &visibleName,const std::string &description, T defaultValue) :
			_offset(offset_obj_field),
			_name(visibleName),
			_desc(description),
			_defaultVal(defaultValue)
		{
		}

		const size_t TypeHash() const override
		{
			return typeid(T).hash_code();
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
			return sizeof(T);
		}
		const ptrdiff_t FieldOffset() const override
		{
			return _offset;
		}

		[[nodiscard]] const void *DefaultValue() const override
		{
			return reinterpret_cast<const void *>(&_defaultVal);
		}

		void *Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			return std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
		}

		void Set(void *objPtr, void *value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)); 
			T* rhs = std::launder(static_cast<T*>(value));

			*lhs = *rhs;
		}

		template<typename T>
		[[nodiscard]] void Set(void* objPtr, const T* value)
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
			T* rhs = std::launder<T>(static_cast<T*>(value));
			
			*lhs = *rhs;
		}

		FieldRepresentation Representation() const override
		{
			return GetFieldRepresentation<T>();
		}

		~ReflectedField() override = default;
	};

	/// Null specialization. Sentinel value.
	template<>
	class DLLEXPORT ReflectedField<void> final : public IReflectedField
	{
	public:
		ReflectedField() = default;

		const size_t TypeHash() const override
		{
			return 0;
		}
		const std::string FieldName() const override
		{
			return std::string("");
		}
		const std::string FieldDesc() const override
		{
			return std::string("");
		}
		const size_t TypeSize() const override
		{
			return 0;
		}
		const ptrdiff_t FieldOffset() const override
		{
			return 0;
		}
		void *Get(void *objPtr) const override
		{
			return nullptr;
		}
		void Set(void *objPtr, void *value) const override
		{
		}
		const void *DefaultValue() const override
		{
			return nullptr;
		}
		FieldRepresentation Representation() const override
		{
			return GetFieldRepresentation<void>();
		}
	};
}