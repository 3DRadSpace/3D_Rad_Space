#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename Invalid>
	class ReflectedField
	{
		static_assert(false, "ReflectedField is only defined for types that satisfy ReflectableType.");
	};

	template<ReflectableType T>
	class ReflectedField<T> : public IReflectedField
	{
		T _defaultVal;
	public:
		ReflectedField(
			const size_t offset_obj_field,
			const std::string &visibleName,
			const std::string &description,
			T defaultValue
		) :
			IReflectedField(offset_obj_field, sizeof(T), visibleName, description, typeid(T)),
			_defaultVal(defaultValue)
		{
		}

		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			return static_cast<const void *>(&_defaultVal);
		}

		[[nodiscard]] const void* Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			return std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
		}

		void Set(void *objPtr, const void *value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)); 
			const T* rhs = static_cast<const T*>(value);

			*lhs = *rhs;
		}

		template<typename T>
		void Set(void* objPtr, const T* value)  const
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
			const T* rhs = static_cast<const T*>(value);
			
			*lhs = *rhs;
		}

		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);

			return T(*std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)));
		}

		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}

		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedField<T>>(_offset, _name, _desc, _defaultVal);
		}

		~ReflectedField() override = default;
	};

	template<typename T, typename C>
	class ReflectedFieldGS : public IReflectedField
	{
		T _defaultVal;
		mutable T _copy;

		T (*_getter)(C&);
		void (*_setter)(C&, const T&);
	public:
		ReflectedFieldGS(
			const std::string &visibleName,
			const std::string &description,
			T (*getter)(C&),
			void (*setter)(C&, const T&),
			T defaultValue
		) :
			IReflectedField(0, sizeof(T), visibleName, description, typeid(T)),
			_defaultVal(defaultValue),
			_copy(defaultValue),
			_getter(getter),
			_setter(setter)
		{
		}

		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			return static_cast<const void *>(&_defaultVal);
		}

		[[nodiscard]] const void* Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			_copy = (_getter)(*static_cast<C*>(objPtr));
			return &_copy;
		}

		void Set(void *objPtr, const void *value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			_setter(*static_cast<C*>(objPtr), *static_cast<const T*>(value));
		}

		template<typename T>
		void Set(void* objPtr, const T* value)  const
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			_setter(*static_cast<C*>(objPtr), *value);
		}

		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);

			return (_getter)(*static_cast<C*>(objPtr));
		}

		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}

		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedFieldGS<T, C>>(_name, _desc, _getter, _setter, _defaultVal);
		}

		~ReflectedFieldGS() override = default;
	};

	/// Null specialization. Sentinel value.
	template<>
	class E3DRSP_REFLECTION_EXPORT ReflectedField<void> final : public IReflectedField
	{
	public:
		ReflectedField() : IReflectedField(0, 0, "", "", typeid(void))
		{
		}

		const void *Get(void *objPtr) const override
		{
			return nullptr;
		}

		void Set(void *objPtr, const void *value) const override
		{
		}

		const void *DefaultValue() const noexcept override
		{
			return nullptr;
		}

		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<void>();
		}

		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedField<void>>(*this);
		}
	};

	template<ReflectableType T>
	class E3DRSP_REFLECTION_EXPORT ReflectedField<std::optional<T>> final : public IReflectedField
	{
	public:
		using OptT = std::optional<T>;
	private:

		OptT _defaultVal;
	public:
		ReflectedField(
			const size_t offset_obj_field,
			const std::string& visibleName,
			const std::string& description,
			OptT defaultValue
		) :
			IReflectedField(offset_obj_field, sizeof(OptT), visibleName, description, typeid(OptT)),
			_defaultVal(defaultValue)
		{
		}

		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			if(_defaultVal.has_value()) return static_cast<const void*>(&_defaultVal);
			else return nullptr;
		}

		[[nodiscard]] const void* Get(void* objPtr) const override
		{
			assert(objPtr != nullptr);

			auto ptrOptional = std::launder(reinterpret_cast<std::optional<T>*>(static_cast<std::byte*>(objPtr) + _offset));
			if(ptrOptional->has_value())
				return ptrOptional->operator->();
			else return nullptr;
		}

		void Set(void* objPtr, const void* value) const override
		{
			assert(objPtr != nullptr);

			OptT* lhs = std::launder(reinterpret_cast<OptT*>(static_cast<std::byte*>(objPtr) + _offset));
			const T* rhs = static_cast<const T*>(value);

			if(value != nullptr) *lhs = *rhs;
			else *lhs = std::nullopt;
		}

		template<typename T>
		void Set(void* objPtr, const T* value)  const
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			OptT* lhs = std::launder<T>(reinterpret_cast<OptT*>(static_cast<std::byte*>(objPtr) + _offset));

			if(value != nullptr)
			{
				const T* rhs = static_cast<const T*>(value);
				*lhs = *rhs;
			}
			else *lhs = std::nullopt;
		}

		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);

			return (*std::launder(reinterpret_cast<OptT*>(static_cast<std::byte*>(objPtr) + _offset))).value();
		}

		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}

		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedField<std::optional<T>>>(_offset, _name, _desc, _defaultVal);
		}

		~ReflectedField() override = default;
	};
}