#pragma once
#include "IObject3D.hpp"
#include "IObject2D.hpp"
#include "Reflection/ReflectedObject.hpp"

namespace Engine3DRadSpace
{
	template<typename O>
	concept GameObject = Reflection::ReflectableObject<O> || std::is_same_v<IObject, O> || std::is_same_v<IObject2D, O> || std::is_same_v<IObject3D, O>;

	class DLLEXPORT ObjectList
	{
	public:
		struct ObjectInstance
		{
			std::shared_ptr<IObject> Object;

			enum class ObjectType : uint8_t
			{
				None = 0,
				IObject = 1,
				IObject2D,
				IObject3D,
			} InternalType;

			template<GameObject O>
			ObjectInstance(std::shared_ptr<O>&& obj);

			template<>
			ObjectInstance(std::shared_ptr<IObject> &&obj);
		};
	private:
		std::vector<ObjectInstance> objects;
	public:
		ObjectList() = default;
		ObjectList(ObjectList&) = delete;
		ObjectList(ObjectList&&) noexcept = default;

		ObjectList& operator=(ObjectList&) = delete;
		ObjectList& operator=(ObjectList&&) noexcept = default;

		template<GameObject O, typename ...Params>
		std::pair<O*, unsigned> AddNew(Params&& ...p);

		template<GameObject O>
		unsigned AddNew(O&& object);

		unsigned Add(IObject* obj);
		unsigned Add(IObject2D* obj);
		unsigned Add(IObject3D* obj);

		IObject* Find(unsigned id);
		IObject* Find(const std::string& name);
		/// <summary>
		/// Finds and the i-th object of the type O.
		/// </summary>
		/// <typeparam name="O">Object type.</typeparam>
		/// <param name="i">Index</param>
		/// <returns>Returns the i-th object of the type O.</returns>
		template<GameObject O>
		O* Find(unsigned i = 0);

		void Remove(unsigned id);
		void Remove(const std::string& name);
		void Remove(IObject* obj);

		void RemoveIf(std::function<bool(IObject*)> f);

		void Replace(IObject* obj, unsigned id);

		void Clear();

		std::vector<ObjectInstance>::iterator begin();
		std::vector<ObjectInstance>::iterator end();
	};

	template<GameObject O>
	inline ObjectList::ObjectInstance::ObjectInstance(std::shared_ptr<O>&& obj) : Object(std::move(obj))
	{
		InternalType = ObjectType::IObject;
		if constexpr (std::is_base_of_v<IObject2D, O>) InternalType = ObjectType::IObject2D;
		else if constexpr (std::is_base_of_v<IObject3D, O>) InternalType = ObjectType::IObject3D;
	}

	template<GameObject O, typename... Params>
	inline std::pair<O*, unsigned> ObjectList::AddNew(Params&&... p)
	{
		auto obj = objects.emplace_back(std::make_shared<O>(std::forward<Params>(p)...));
		return std::make_pair(static_cast<O*>(obj.Object.get()), unsigned(objects.size() - 1));
	}

	template<GameObject O>
	inline unsigned ObjectList::AddNew(O&& object)
	{
		auto new_obj = std::make_unique<O>(std::move(object));

		objects.emplace_back(_get_list_type_index<O>(), std::move(new_obj));
		return objects.size() - 1;
	}

	template<GameObject O>
	inline O* ObjectList::Find(unsigned i)
	{
		unsigned c = 0;
		O* ptr = nullptr;

		for (auto& [type, object] : objects)
		{
			ptr = dynamic_cast<O*>(object.get());
			if (ptr != nullptr)
			{
				c++;
				if (c == i) return ptr;
			}
		}
		return ptr;
	}
}