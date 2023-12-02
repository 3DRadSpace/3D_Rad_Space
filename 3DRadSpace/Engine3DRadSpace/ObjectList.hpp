#pragma once
#include "IObject3D.hpp"
#include "IObject2D.hpp"
#include "Reflection/ReflectedObject.hpp"
#include "Internal/InitializationFlag.hpp"
#include "Game.hpp"

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
		std::vector<ObjectInstance> _objects;
		Game* _game;
	public:
		ObjectList(Game* owner);
		ObjectList(ObjectList&) = delete;
		ObjectList(ObjectList&&) noexcept = default;

		ObjectList& operator=(ObjectList&) = delete;
		ObjectList& operator=(ObjectList&&) noexcept = default;

		template<GameObject O, typename ...Params>
		std::pair<O*, unsigned> AddNew(Internal::InitializationFlag flag, Params&& ...p);

		template<GameObject O>
		unsigned AddNew(O&& object, Internal::InitializationFlag flag = Internal::InitializationFlag::InitializeAndLoad);

		unsigned Add(IObject* obj, Internal::InitializationFlag flag = Internal::InitializationFlag::InitializeAndLoad);
		unsigned Add(IObject2D* obj, Internal::InitializationFlag flag = Internal::InitializationFlag::InitializeAndLoad);
		unsigned Add(IObject3D* obj, Internal::InitializationFlag flag = Internal::InitializationFlag::InitializeAndLoad);

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

		IObject* operator[](unsigned i) const;

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
	inline std::pair<O*, unsigned> ObjectList::AddNew(Internal::InitializationFlag flag, Params&&... p)
	{
		auto &obj = _objects.emplace_back(std::make_shared<O>(std::forward<Params>(p)...));
		
		bool internalInitialize = flag != Internal::InitializationFlag::NoInitialization;
		bool initialize = flag == Internal::InitializationFlag::Initialize || flag == Internal::InitializationFlag::InitializeAndLoad;
		bool load = flag == Internal::InitializationFlag::InitializeAndLoad || flag == Internal::InitializationFlag::Load;

		if(internalInitialize) obj.internalInitialize(_game);
		if(initialize) obj.Initialize();
		if(load) obj.Load(_game->Content.get());

		return std::make_pair(static_cast<O*>(obj.Object.get()), unsigned(_objects.size() - 1));
	}

	template<GameObject O>
	inline unsigned ObjectList::AddNew(O&& object, Internal::InitializationFlag flag)
	{
		auto new_obj = std::make_shared<O>(std::move(object));

		bool internalInitialize = flag != Internal::InitializationFlag::NoInitialization;
		bool initialize = flag == Internal::InitializationFlag::Initialize || flag == Internal::InitializationFlag::InitializeAndLoad;
		bool load = flag == Internal::InitializationFlag::InitializeAndLoad || flag == Internal::InitializationFlag::Load;

		if (internalInitialize) new_obj->internalInitialize(_game);
		if (initialize) new_obj->Initialize();
		if (load) new_obj->Load(_game->Content.get());

		_objects.emplace_back(std::move(new_obj));
		return unsigned(_objects.size() - 1);
	}

	template<GameObject O>
	inline O* ObjectList::Find(unsigned i)
	{
		unsigned c = 0;
		O* ptr = nullptr;

		for (auto& [type, object] : _objects)
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