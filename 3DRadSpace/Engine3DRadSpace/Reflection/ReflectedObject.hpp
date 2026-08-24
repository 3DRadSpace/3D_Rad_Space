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
	/// <summary>
	/// Metadata of an object that is being reflected. This is used for serialization and deserialization.
	/// </summary>
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
		/// <summary>
		/// Constructs metadata of an object that is being reflected.
		/// </summary>
		/// <typeparam name="O">object type</typeparam>
		/// <param name="tag">{}</param>
		/// <param name="name">visible object name</param>
		/// <param name="category">object category</param>
		/// <param name="desc">object description</param>
		/// <param name="obj_fields">list of fields, attributes, functions, et cetera</param>
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

		/// <summary>
		/// Constructs metadata of an object that is being reflected.
		/// </summary>
		/// <typeparam name="O">object type</typeparam>
		/// <param name="uuid">UUID of the object</param>
		/// <param name="name">visible object name</param>
		/// <param name="category">object category</param>
		/// <param name="desc">object description</param>
		/// <param name="obj_fields">list of fields, attributes, functions, et cetera</param>
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
		/// <summary>
		/// Visible name of the object.
		/// </summary>
		std::string Name;
		/// <summary>
		/// Object category, used for grouping objects in the editor.
		/// </summary>
		std::string Category;
		/// <summary>
		/// Object description.
		/// </summary>
		std::string Description;
		/// <summary>
		/// Object UUID.
		/// </summary>
		UUID ObjectUUID;
		/// <summary>
		/// Returns the number of fields (including functions and attributes).
		/// </summary>
		/// <returns></returns>
		size_t NumFields() const noexcept;
		/// <summary>
		/// Returns the i-th field (including functions and attributes).
		/// </summary>
		/// <param name="i">index</param>
		/// <returns>field metadata</returns>
		const IReflectedField *operator[](unsigned i);
		/// <summary>
		///	Returns the field with the given name (including functions and attributes).
		/// </summary>
		/// <param name="name">name of the field/attribute/function</param>
		/// <returns>reflected field</returns>
		const IReflectedField *operator[](const std::string &name);

		std::vector<IReflectedField *>::iterator begin();
		std::vector<IReflectedField *>::iterator end();
		/// <summary>
		/// Creates a blank object of the reflected type in heap memory.
		/// </summary>
		std::function<void*()> CreateBlankObject;
		/// <summary>
		/// Performs a deep clone of the metadata.
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<ReflectedObject> Clone() const;

		~ReflectedObject();
	};
}