#pragma once
#include "IObject3D.hpp"
#include "IObject2D.hpp"
#include "ObjectType.hpp"
#include "../Reflection/ReflectedObject.hpp"
#include "../Core/IGame.hpp"
#include "../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Objects
{
	class Camera;

	template<typename O>
	concept GameObject = Reflection::ReflectableObject<O> || std::is_same_v<IObject, O> || std::is_same_v<IObject2D, O> || std::is_same_v<IObject3D, O>;

	/// <summary>
	/// Manages the lifetime of all objects in a scene.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT ObjectList : public IService
	{
	public:
		struct E3DRSP_OBJECTS_EXPORT ObjectInstance
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

		void _validate(ObjectInstance& instance);
		void _validate(IObject* instance);
	public:
		/// <summary>
		/// Creates a new ObjectList instance.
		/// </summary>
		/// <param name="owner">Owner game instance</param>
		explicit ObjectList(IGame* owner);
		ObjectList(const ObjectList&) = delete;
		ObjectList(ObjectList&&) noexcept = default;

		ObjectList& operator=(const ObjectList&) = delete;
		ObjectList& operator=(ObjectList&&) noexcept = default;

		/// <summary>
		/// Emplaces a new object into this list.
		/// </summary>
		/// <typeparam name="...Params">Parameter pack for the object's constructor	</typeparam>
		/// <typeparam name="O">Type of the object to add</typeparam>
		/// <param name="...p">Arguments for the object's constructor</param>
		/// <returns>Pair of pointer to the new object and its index</returns>
		template<GameObject O, typename ...Params>
		std::pair<O*, unsigned> AddNew(Params&& ...p);
		/// <summary>
		///	Moves the specified object into this list.
		/// </summary>
		/// <typeparam name="O">Object to be owned by this list</typeparam>
		/// <param name="object">Object to be moved into the list</param>
		/// <returns>Pair of pointer to the new object and its index</returns>
		template<GameObject O>
		std::pair<O*, unsigned> AddNew(O&& object);
		/// <summary>
		/// Add a pointer to an existing object into this list. The list will take ownership of the object and will be responsible for its lifetime.
		/// </summary>
		/// <param name="obj">Pointer to the object to be added</param>
		/// <returns>Index of the added object</returns>
		unsigned Add(IObject* obj);
		/// <summary>
		/// Finds the first object with the specified name.
		/// </summary>
		/// <param name="name">Name of the object to find</param>
		/// <returns>Pointer to the found object, or nullptr if not found</returns>
		IObject* Find(const std::string& name) const noexcept;

		/// <summary>
		/// Finds and the i-th object of the type O.
		/// </summary>
		/// <typeparam name="O">Object type.</typeparam>
		/// <param name="i">Index</param>
		/// <returns>Returns the i-th object of the type O.</returns>
		template<GameObject O>
		O* Find(unsigned i = 0) const;
		/// <summary>
		/// Removes the object with the specified ID.
		/// </summary>
		/// <param name="id">ID of the object to remove</param>
		void Remove(unsigned id);
		/// <summary>
		/// Removes the object with the specified name.
		/// </summary>
		/// <param name="name">Name of the object to remove</param>
		void Remove(const std::string& name);
		/// <summary>
		/// Remove the specified object.
		/// </summary>
		/// <param name="obj">Pointer to the object to be removed</param>
		void Remove(IObject* obj);
		/// <summary>
		/// Remove all the objects that match the specified predicate.
		/// </summary>
		/// <param name="f">Predicate function to determine which objects to remove</param>
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
		/// <summary>
		/// Returns the i-th object in this list.
		/// </summary>
		/// <param name="i">index</param>
		/// <returns>Pointer to the i-th object</returns>
		IObject* operator[](size_t i) const;
		/// <summary>
		/// Returns the number of objects in this list.
		/// </summary>
		/// <returns></returns>
		size_t Count() const noexcept;
		/// <summary>
		/// Begin iterator for the object list.
		/// </summary>
		/// <returns>Iterator to the beginning of the object list</returns>
		std::vector<ObjectInstance>::iterator begin();
		/// <summary>
		/// End iterator for the object list.
		/// </summary>
		/// <returns>Iterator to the end of the object list</returns>
		std::vector<ObjectInstance>::iterator end();
		/// <summary>
		///	Const iterator for the object list.
		/// </summary>
		/// <returns>Const iterator to the beginning of the object list</returns>
		std::vector<ObjectInstance>::const_iterator begin() const;
		/// <summary>
		/// Const iterator for the object list.
		/// </summary>
		/// <returns>Const iterator to the end of the object list</returns>
		std::vector<ObjectInstance>::const_iterator end() const;
		/// <summary>
		/// Gets the bounding box of the entire scene.
		/// </summary>
		/// <returns>Bounding box of the entire scene</returns>
		Math::BoundingBox GetBoundingBox() const noexcept;

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