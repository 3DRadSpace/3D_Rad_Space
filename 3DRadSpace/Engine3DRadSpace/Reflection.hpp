#pragma once
#include "Keyboard.hpp"
#include "Texture2D.hpp"
#include "Model3D.hpp"
#include "Vector4.hpp"
#include "UUID.hpp"
#include "IObject.hpp"

namespace Engine3DRadSpace
{
	class IObject;
}
namespace Engine3DRadSpace::Reflection
{
	template<typename N>
	concept signed_integer = std::is_same_v<N, int8_t> || std::is_same_v<N, int16_t> || std::is_same_v<N, int32_t> || std::is_same_v<N, int64_t>;

	template<typename N>
	concept unsigned_integer = std::is_same_v<N, uint8_t> || std::is_same_v<N, uint16_t> || std::is_same_v<N, uint32_t> || std::is_same_v<N, uint64_t>;

	enum class FieldRepresentationType
	{
		Unknown,
		Boolean,
		Integer,
		Unsigned,
		Float,
		Quaternion,
		String,
		Image,
		Model,
		Key,
		Enum,
		Color,
		Custom,
	};

	using FieldRepresentation = std::vector<std::pair<FieldRepresentationType, const std::string>>;

	template<typename T> FieldRepresentation GetFieldRepresentation() = delete; //Only default and useer-written allow GetFieldRepresentation() specializations.

	//GetFieldRepresentation() specializations, as defined in FieldRepresentationType
	template<> FieldRepresentation GetFieldRepresentation<void>();
	template<> FieldRepresentation GetFieldRepresentation<bool>();
	template<signed_integer T> FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Integer,""} }; }
	template<unsigned_integer T> FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Unsigned,""} }; }
	template<std::floating_point T> FieldRepresentation GetFieldRepresentation() { return { { FieldRepresentationType::Float,""} }; }
	template<> FieldRepresentation GetFieldRepresentation<std::string>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Graphics::Texture2D>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Graphics::Model3D>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Input::Key>();

	//FieldRepresentationType() specializations for mathematical types
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Vector2>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Point>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Vector3>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Vector4>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Quaternion>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Color>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Rectangle>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::RectangleF>();

	template<typename T>
	concept ReflectableType = requires
	{
		GetFieldRepresentation<T>();
	};

	class IReflectedField
	{
	public:
		virtual const size_t TypeHash() const = 0;
		virtual const std::string FieldName() const = 0;
		virtual const std::string FieldDesc() const = 0;
		virtual const size_t TypeSize() const = 0;
		virtual const ptrdiff_t FieldOffset() const = 0;

		virtual void* Get(void* objPtr) const = 0;
		virtual void Set(void* objPtr, void* value) const = 0;

		virtual const void* DefaultValue() const = 0;

		virtual FieldRepresentation Representation() const = 0;

		virtual ~IReflectedField() = default;
	};

	template<ReflectableType T>
	class ReflectedField : public IReflectedField
	{
		const size_t offset;
		const std::string name;
		const std::string desc;
		const T defaultVal;
	public:
		ReflectedField(const size_t offset_obj_field,std::string visibleName, std::string description, T defaultValue) : 
			offset(offset_obj_field), 
			name(visibleName),
			desc(description),
			defaultVal(defaultValue)
		{
		}

		const size_t TypeHash() const override
		{
			return typeid(T).hash_code();
		}
		const std::string FieldName() const override
		{
			return name;
		}
		const std::string FieldDesc() const override
		{
			return desc;
		}
		const size_t TypeSize() const override
		{
			return sizeof(T);
		}
		const ptrdiff_t FieldOffset() const override
		{
			return offset;
		}

		const void* DefaultValue() const override
		{
			return reinterpret_cast<const void*>(&defaultVal);
		}

		void* Get(void* objPtr) const override
		{
			if (objPtr == nullptr) throw std::invalid_argument("Get(): objPtr = nullptr");

			return reinterpret_cast<T*>(reinterpret_cast<char*>(objPtr) + offset);
		}

		void Set(void* objPtr, void* value) const override
		{
			if (objPtr == nullptr) throw std::invalid_argument("Set(): objPtr = nullptr");
			if (value == nullptr) throw std::invalid_argument("Set(): value = nullptr");

			T* lhs = reinterpret_cast<T*>(reinterpret_cast<char*>(objPtr) + offset);
			T* rhs = reinterpret_cast<T*>(value);

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
		void* Get(void* objPtr) const override
		{
			return nullptr;
		}
		void Set(void* objPtr, void* value) const override
		{
		}
		const void* DefaultValue() const override
		{
			return nullptr;
		}
		FieldRepresentation Representation() const override
		{
			return GetFieldRepresentation<void>();
		}
	};

	template<typename O>
	concept ReflectableObject = std::is_base_of_v<Engine3DRadSpace::IObject, O> && std::is_default_constructible_v<O>;

	template<ReflectableObject O>
	struct ObjectTag{ };

	class ReflectedObject
	{
		std::vector<IReflectedField*> fields;

		template<ReflectableObject O>
		Reflection::UUID determineUUID(ObjectTag<O> tag)
		{
			auto obj = std::make_unique<O>();
			return obj->GetUUID();
		}
	public:
		template<ReflectableObject O>
		ReflectedObject(ObjectTag<O> tag, const std::string &name, const std::string &category, const std::string &desc, std::initializer_list<IReflectedField *> obj_fields) :
			Name(name),
			fields(obj_fields),
			Category(category),
			Description(desc),
			ObjectUUID(determineUUID<O>(tag))
		{
			CreateBlankObject = []()
			{
				return new O();
			};
		}

		const std::string Name;
		const std::string Category;
		const std::string Description;
		const Reflection::UUID ObjectUUID;

		const size_t NumFields();
		const IReflectedField* operator[](unsigned i);
		const IReflectedField* operator[](const std::string& name);

		std::vector<IReflectedField*>::iterator begin();
		std::vector<IReflectedField*>::iterator end();

		std::function<Engine3DRadSpace::IObject *()> CreateBlankObject;

		~ReflectedObject();
	};
}

#define __REFL_BEGIN(ObjectType,ObjectName, ObjectCategory, ObjectDescription) Engine3DRadSpace::Reflection::ReflectedObject ObjectType##ReflInstance( Engine3DRadSpace::Reflection::ObjectTag<ObjectType>{},ObjectName,ObjectCategory,ObjectDescription, {

/// Reflects a fields, with given information. 
/// NOTE: This does not invoke undefined behiavour with > C++ 17 compilers that conditionally support non-standard-layout classes/structs.
#define __REFL_FIELD(ObjectType,FieldType, FieldName, FieldVisibleName, DefaultValue, Description) \
static_cast<Engine3DRadSpace::Reflection::IReflectedField*>( new Engine3DRadSpace::Reflection::ReflectedField<FieldType>(offsetof(ObjectType, FieldName), FieldVisibleName, Description, DefaultValue)),

#define __REFL_END static_cast<Engine3DRadSpace::Reflection::IReflectedField*>( new Engine3DRadSpace::Reflection::ReflectedField<void>())});

#define __REFL_DEF(ObjectName) extern Engine3DRadSpace::Reflection::ReflectedObject ObjectName##ReflInstance;