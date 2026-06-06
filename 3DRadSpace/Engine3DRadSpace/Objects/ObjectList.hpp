#pragma once
#include "ICamera.hpp"
#include "IObject3D.hpp"
#include "IObject2D.hpp"
#include "ObjectType.hpp"
#include "../Reflection/ReflectedObject.hpp"
#include "../Core/IGame.hpp"

namespace Engine3DRadSpace::Objects
{
	class Camera;

	template<typename O>
	concept GameObject = Reflection::ReflectableObject<O> || std::is_same_v<IObject, O> || std::is_same_v<IObject2D, O> || std::is_same_v<IObject3D, O>;

	class E3DRSP_OBJECTS_EXPORT ObjectList : public IService
	{
	public:
		struct ObjectInstance
		{
			std::unique_ptr<IObject> Object;

			ObjectType InternalType;

			ObjectInstance(IObject* obj);

			ObjectInstance(const ObjectInstance& copy) = delete;
			ObjectInstance(ObjectInstance&&) noexcept = default;

			template<GameObject O>
			ObjectInstance(std::unique_ptr<O>&& obj);

			template<GameObject O>
			ObjectInstance(O&& obj);

			template<>
			ObjectInstance(std::unique_ptr<IObject> &&obj);

			ObjectInstance& operator=(const ObjectInstance&) = delete;
			ObjectInstance& operator=(ObjectInstance&&) noexcept = default;

			IObject* operator->() const noexcept;
		};
	private:
		std::vector<ObjectInstance> _objects;
		Objects::ICamera* _camera;

		void _validate(ObjectInstance& instance);
		void _validate(IObject* instance);
	public:
		ObjectList(IGame* owner);
		ObjectList(const ObjectList&) = delete;
		ObjectList(ObjectList&&) noexcept = default;

		ObjectList& operator=(const ObjectList&) = delete;
		ObjectList& operator=(ObjectList&&) noexcept = default;

		template<GameObject O, typename ...Params>
		std::pair<O*, unsigned> AddNew(Params&& ...p);

		template<GameObject O>
		std::pair<O*, unsigned> AddNew(O&& object);

		unsigned Add(IObject* obj);

		IObject* Find(const std::string& name) const noexcept;

		/// <summary>
		/// Finds and the i-th object of the type O.
		/// </summary>
		/// <typeparam name="O">Object type.</typeparam>
		/// <param name="i">Index</param>
		/// <returns>Returns the i-th object of the type O.</returns>
		template<GameObject O>
		O* Find(unsigned i = 0) const;

		ICamera* GetRenderingCamera() const noexcept;
		void SetRenderingCamera(ICamera* cam) noexcept;

		void Remove(unsigned id);
		void Remove(const std::string& name);
		void Remove(IObject* obj);

		void RemoveIf(std::function<bool(IObject*)> f);

		/// <summary>
		/// Replaces the object at the specified index with the given object. The new object will be initialized with the same game context as the old one.
		/// </summary>
		/// <param name="obj">New object</param>
		/// <param name="id">Index of the object to replace</param>
		void Replace(IObject* obj, unsigned id) noexcept;

		/// <summary>
		/// Empties the object list. All objects will be removed and their memory will be freed.
		/// </summary>
		void Clear() noexcept;

		IObject* operator[](size_t i) const;
		size_t Count() const noexcept;

		std::vector<ObjectInstance>::iterator begin();
		std::vector<ObjectInstance>::iterator end();

		std::vector<ObjectInstance>::const_iterator begin() const;
		std::vector<ObjectInstance>::const_iterator end() const;

		friend class Camera;

		~ObjectList() override = default;
	};

	template<GameObject O>
	inline ObjectList::ObjectInstance::ObjectInstance(std::unique_ptr<O>&& obj) : Object(std::move(obj))
	{
		InternalType = ObjectType::IObject;
		if constexpr (std::is_base_of_v<IObject2D, O>) InternalType = ObjectType::IObject2D;
		else if constexpr (std::is_base_of_v<IObject3D, O>) InternalType = ObjectType::IObject3D;
	}

	template<GameObject O>
	inline ObjectList::ObjectInstance::ObjectInstance(O&& obj)
	{
		using ObjT = std::decay_t<O>;
		Object.reset(new ObjT(std::forward<O>(obj)));

		InternalType = ObjectType::IObject;
		if constexpr (std::is_base_of_v<IObject2D, O>) InternalType = ObjectType::IObject2D;
		else if constexpr (std::is_base_of_v<IObject3D, O>) InternalType = ObjectType::IObject3D;
	}

	template<GameObject O, typename ...Params>
	inline std::pair<O*, unsigned> ObjectList::AddNew(Params&& ...p)
	{
		auto& obj = _objects.emplace_back(std::make_unique<O>(std::forward<Params>(p)...));
		_validate(obj);
		return std::make_pair(static_cast<O*>(obj.Object.get()), unsigned(_objects.size() - 1));
	}

	template<GameObject O>
	inline std::pair<O*, unsigned> ObjectList::AddNew(O&& object)
	{
		auto index = _objects.size() - 1;
		auto& obj = _objects.emplace_back(std::forward<O>(object));
		_validate(obj);
		return std::make_pair(static_cast<O*>(obj.Object.get()), unsigned(index));
	}

	template<GameObject O>
	inline O* ObjectList::Find(unsigned i) const
	{
		unsigned c = 0;
		O* ptr = nullptr;

		for (auto& [object, type] : _objects)
		{
			ptr = dynamic_cast<O*>(object.get());
			if (ptr != nullptr)
			{
				if (c++ == i) return ptr;
			}
		}
		return ptr;
	}
}