#pragma once
#include "ReflectedField.hpp"
#include "UUID.hpp"
#include "../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Objects that are being reflected must be default constructible for serialization.
	/// </summary>
	template<typename O>
	concept ReflectableObject = std::is_default_constructible_v<O>;

	template<ReflectableObject O>
	struct ObjectTag 
	{
		using Type = O;
	};

	class E3DRSP_REFLECTION_EXPORT ReflectedObject
	{
		std::vector<IReflectedField*> _fields;

		template<ReflectableObject O>
		UUID determineUUID(ObjectTag<O> tag)
		{
			auto obj = std::make_unique<O>();
			return obj->GetUUID();
		}
	public:
		template<ReflectableObject O>
		ReflectedObject(ObjectTag<O> tag, const std::string &name, const std::string &category, const std::string &desc, std::initializer_list<IReflectedField *> obj_fields) :
			Name(name),
			_fields(obj_fields),
			Category(category),
			Description(desc),
			ObjectUUID(determineUUID<O>(tag))
		{
			CreateBlankObject = []()
			{
				return static_cast<void*>(new O());
			};
		}

		ReflectedObject(
			const std::string& name,
			const std::string& category,
			const std::string& desc,
			const std::span<IReflectedField*> obj_fields,
			const UUID& uuid
		);

		ReflectedObject(const ReflectedObject& other) = default;
		ReflectedObject(ReflectedObject&& other) noexcept = default;

		ReflectedObject& operator=(const ReflectedObject& other) = default;
		ReflectedObject& operator=(ReflectedObject&& other) noexcept = default;

		std::string Name;
		std::string Category;
		std::string Description;
		UUID ObjectUUID;

		size_t NumFields() const noexcept;
		const IReflectedField *operator[](unsigned i);
		const IReflectedField *operator[](const std::string &name);

		std::vector<IReflectedField *>::iterator begin();
		std::vector<IReflectedField *>::iterator end();

		std::function<void*()> CreateBlankObject;

		std::unique_ptr<ReflectedObject> Clone() const;

		~ReflectedObject();
	};
}