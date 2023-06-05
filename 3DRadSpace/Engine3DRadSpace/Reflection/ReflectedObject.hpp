#pragma once
#include "ReflectedField.hpp"
#include "UUID.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename O>
	concept ReflectableObject = std::is_base_of_v<Engine3DRadSpace::IObject, O> &&std::is_default_constructible_v<O>;

	template<ReflectableObject O>
	struct ObjectTag {};

	class ReflectedObject
	{
		std::vector<IReflectedField *> fields;

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
		const IReflectedField *operator[](unsigned i);
		const IReflectedField *operator[](const std::string &name);

		std::vector<IReflectedField *>::iterator begin();
		std::vector<IReflectedField *>::iterator end();

		std::function<Engine3DRadSpace::IObject *()> CreateBlankObject;

		~ReflectedObject();
	};
}