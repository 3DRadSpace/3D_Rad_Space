#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
	class IReflectedField
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
		ReflectedField(const size_t offset_obj_field, std::string visibleName, std::string description, T defaultValue) :
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

		const void *DefaultValue() const override
		{
			return reinterpret_cast<const void *>(&_defaultVal);
		}

		void *Get(void *objPtr) const override
		{
			if(objPtr == nullptr) throw std::invalid_argument("Get(): objPtr = nullptr");

			return reinterpret_cast<T *>(reinterpret_cast<char *>(objPtr) + _offset);
		}

		void Set(void *objPtr, void *value) const override
		{
			if(objPtr == nullptr) throw std::invalid_argument("Set(): objPtr = nullptr");
			if(value == nullptr) throw std::invalid_argument("Set(): value = nullptr");

			T *lhs = reinterpret_cast<T *>(reinterpret_cast<char *>(objPtr) + _offset);
			T *rhs = reinterpret_cast<T *>(value);

			*lhs = *rhs;
		}

		FieldRepresentation Representation() const override
		{
			return GetFieldRepresentation<T>();
		}
	};

	/// Null specialization. Sentinel value.
	template<>
	class ReflectedField<void> : public IReflectedField
	{
	public:
		ReflectedField()
		{
		}
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