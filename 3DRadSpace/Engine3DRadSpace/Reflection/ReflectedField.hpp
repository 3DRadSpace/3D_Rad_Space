#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename Invalid>
	class ReflectedField
	{
		static_assert(false, "ReflectedField is only defined for types that satisfy ReflectableType.");
	};

	/// <summary>
	/// Concrete reflected field type.
	/// </summary>
	/// <typeparam name="T">Type of the field. Must be serializable.</typeparam>
	template<ReflectableType T>
	class ReflectedField<T> : public IReflectedField
	{
		T _defaultVal;
	public:
		/// <summary>
		/// Constructs a ReflectedField with the given name and default value.
		/// </summary>
		/// <param name="offset_obj_field">offsetof between the instance and field</param>
		/// <param name="visibleName">visible name</param>
		/// <param name="description">visible description</param>
		/// <param name="defaultValue">defalut value</param>
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

		/// <summary>
		///	Returns a reference to the default value.
		/// </summary>
		/// <returns>pointer to deefault value</returns>
		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			return static_cast<const void *>(&_defaultVal);
		}
		/// <summary>
		/// Reads the field given the pointer to the object.
		/// </summary>
		/// <param name="objPtr">Pointer to the object containing this field</param>
		/// <returns>Pointer to the field</returns>
		[[nodiscard]] const void* Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			return std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
		}
		/// <summary>
		/// Sets the field given the pointer to the object and the value.
		/// </summary>
		/// <param name="objPtr">Pointer to the object</param>
		/// <param name="value">Pointer to the new value. The new value must be the same type.</param>
		void Set(void *objPtr, const void *value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)); 
			const T* rhs = static_cast<const T*>(value);

			*lhs = *rhs;
		}
		/// <summary>
		/// Sets the field given the pointer to the object and the value.
		/// </summary>
		/// <typeparam name="T">Type</typeparam>
		/// <param name="objPtr">Pointer to the object.</param>
		/// <param name="value">New value.</param>
		template<typename T>
		void Set(void* objPtr, const T* value)  const
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
			const T* rhs = static_cast<const T*>(value);
			
			*lhs = *rhs;
		}
		/// <summary>
		/// Gets a copy of the field given the pointer to the object.
		/// </summary>
		/// <typeparam name="T">Type of the field</typeparam>
		/// <param name="objPtr"Pointer to the object containing this field></param>
		/// <returns>Copy of the field</returns>
		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);

			return T(*std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)));
		}
		/// <summary>
		/// Returns the field representation
		/// </summary>
		/// <returns></returns>
		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}
		/// <summary>
		/// Performs a deep clone of this instance.
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedField<T>>(_offset, _name, _desc, _defaultVal);
		}

		~ReflectedField() override = default;
	};

	/// <summary>
	/// Concrete reflected field type with fields that require get/set functions.
	/// </summary>
	/// <typeparam name="T">Type</typeparam>
	/// <typeparam name="C">Class that has this field</typeparam>
	template<typename T, typename C>
	class ReflectedFieldGS : public IReflectedField
	{
		T _defaultVal;
		mutable T _copy;

		T (*_getter)(C&);
		void (*_setter)(C&, const T&);
	public:
		/// <summary>
		/// Constructs a new ReflectedFieldGS with the given name, default value, getter and setter.
		/// </summary>
		/// <param name="visibleName">visible name</param>
		/// <param name="description">description</param>
		/// <param name="getter">getter function. Must be of the form T Fn(C&)</param>
		/// <param name="setter">setter function. Must be of the form void Fn(C&, const T&)</param>
		/// <param name="defaultValue">default value</param>
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
		/// <summary>
		/// Gets a reference to the default value.
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			return static_cast<const void *>(&_defaultVal);
		}
		/// <summary>
		/// Calls the getter function.
		/// </summary>
		/// <param name="objPtr">pointer to the object instance that has this field</param>
		/// <returns>the value returned by the getter</returns>
		[[nodiscard]] const void* Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			_copy = (_getter)(*static_cast<C*>(objPtr));
			return &_copy;
		}
		/// <summary>
		/// Calls the setter function.
		/// </summary>
		/// <param name="objPtr">Pointer to the object instance that has this field</param>
		/// <param name="value">new value</param>
		void Set(void *objPtr, const void *value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			_setter(*static_cast<C*>(objPtr), *static_cast<const T*>(value));
			_copy = (_getter)(*static_cast<C*>(objPtr));
		}
		/// <summary>
		/// Calls the setter function
		/// </summary>
		/// <typeparam name="T">Field type</typeparam>
		/// <param name="objPtr">Pointer to the object instance that has this field</param>
		/// <param name="value">new value</param>
		template<typename T>
		void Set(void* objPtr, const T* value)  const
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			_setter(*static_cast<C*>(objPtr), *value);
			Get<T>(objPtr); // update the copy
		}
		/// <summary>
		/// Calls the getter function
		/// </summary>
		/// <typeparam name="T">Field type</typeparam>
		/// <param name="objPtr">Pointer to the object instance that has this field</param>
		/// <param name="value">new value</param>
		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);
			auto value = (_getter)(*static_cast<C*>(objPtr));
			_copy = value;
		}
		/// <summary>
		/// Returns the field representation.
		/// </summary>
		/// <returns>field representation</returns>
		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}
		/// <summary>
		/// Performs a deep clone of this instance.
		/// </summary>
		/// <returns></returns>
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
		/// <summary>
		/// Constructs a new null specialization.
		/// </summary>
		ReflectedField() : IReflectedField(0, 0, "", "", typeid(void))
		{
		}
		/// <summary>
		/// Returns nullptr.
		/// </summary>
		/// <param name="objPtr">unused</param>
		/// <returns>nullptr</returns>
		const void *Get(void *objPtr) const override
		{
			(void)objPtr;
			return nullptr;
		}

		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="objPtr">unused</param>
		/// <param name="value">unused</param>
		void Set(void *objPtr, const void *value) const override
		{
			(void)objPtr;
			(void)value;
		}
		/// <summary>
		/// Returns nullptr.
		/// </summary>
		/// <returns>nullptr</returns>
		const void *DefaultValue() const noexcept override
		{
			return nullptr;
		}
		/// <summary>
		/// Returns a null field representation.
		/// </summary>
		/// <returns>empty representation</returns>
		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<void>();
		}
		/// <summary>
		/// Performs a deep clone of this instance.
		/// </summary>
		/// <returns>a unique pointer to the new cloned instance</returns>
		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedField<void>>(*this);
		}
	};

	/// <summary>
	/// Concrete reflected field type for optional types.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<ReflectableType T>
	class E3DRSP_REFLECTION_EXPORT ReflectedField<std::optional<T>> final : public IReflectedField
	{
	public:
		using OptT = std::optional<T>;
	private:

		OptT _defaultVal;
	public:
		/// <summary>
		/// Creates a new ReflectedField for an optional type.
		/// </summary>
		/// <param name="offset_obj_field">offsetof between the class type and the field</param>
		/// <param name="visibleName">visible name</param>
		/// <param name="description">description</param>
		/// <param name="defaultValue">default value. Can be std::nullopt.</param>
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
		/// <summary>
		/// Returns the default value.
		/// </summary>
		/// <returns>default value. nullptr if unspecified.</returns>
		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			if(_defaultVal.has_value()) return static_cast<const void*>(&_defaultVal);
			else return nullptr;
		}
		/// <summary>
		/// Returns a pointer to the field value if the underlying optional field has a value. Otherwise, returns nullptr.
		/// </summary>
		/// <param name="objPtr">Pointer to the object that contains this field</param>
		/// <returns>pointer to the value, nullptr if the optional field is empty</returns>
		[[nodiscard]] const void* Get(void* objPtr) const override
		{
			assert(objPtr != nullptr);

			auto ptrOptional = std::launder(reinterpret_cast<std::optional<T>*>(static_cast<std::byte*>(objPtr) + _offset));
			if(ptrOptional->has_value())
				return ptrOptional->operator->();
			else return nullptr;
		}
		/// <summary>
		/// Sets the field value.
		/// </summary>
		/// <param name="objPtr">Pointer to the object that contains this field</param>
		/// <param name="value">new value</param>
		void Set(void* objPtr, const void* value) const override
		{
			assert(objPtr != nullptr);

			OptT* lhs = std::launder(reinterpret_cast<OptT*>(static_cast<std::byte*>(objPtr) + _offset));
			const T* rhs = static_cast<const T*>(value);

			if(value != nullptr) *lhs = *rhs;
			else *lhs = std::nullopt;
		}
		/// <summary>
		/// Sets the field value.
		/// </summary>
		/// <typeparam name="T">Type of the field</typeparam>
		/// <param name="objPtr">Pointer to the object that contains this field</param>
		/// <param name="value">new value</param>
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
		/// <summary>
		/// Returns a copy of the field value if the underlying optional field has a value. Otherwise, returns nullptr.
		/// </summary>
		/// <typeparam name="T">Type of the field</typeparam>
		/// <param name="objPtr">Pointer to the object that contains this field</param>
		/// <returns>pointer to the value, nullptr if the optional field is empty</returns>
		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);

			return (*std::launder(reinterpret_cast<OptT*>(static_cast<std::byte*>(objPtr) + _offset))).value();
		}
		/// <summary>
		/// Returns the field representation of the underlying type.
		/// </summary>
		/// <returns>Field representation.</returns>
		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}
		/// <summary>
		/// Performs a deep clone.
		/// </summary>
		/// <returns>A unique pointer to the deep clone.</returns>
		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedField<std::optional<T>>>(_offset, _name, _desc, _defaultVal);
		}

		~ReflectedField() override = default;
	};
}