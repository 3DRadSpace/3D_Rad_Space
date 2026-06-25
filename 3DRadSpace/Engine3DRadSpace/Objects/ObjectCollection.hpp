#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Objects
{
	class IObject;
	/// <summary>
	/// Represents a collection of objects. Unlike <see cref="ObjectList"/>, this doesn't revalidate the container objects nor has ownership.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT ObjectCollection
	{
		std::vector<IObject*> _objects;
		IObject* _owner = nullptr;
	public:
		ObjectCollection(IObject* owner);
		/// <summary>
		/// Adds an IObject pointer reference to this list.
		/// </summary>
		/// <param name="ptr">IObject</param>
		void Add(IObject* ptr);

		/// <summary>
		/// Removes the specified object.
		/// </summary>
		/// <param name="ptr">Object to be removed</param>
		void Remove(IObject* ptr);
		/// <summary>
		/// Removes the ith object in this list.
		/// </summary>
		/// <param name="index">i</param>
		void Remove(size_t index);

		/// <summary>
		/// Returns the ith object in this list.
		/// </summary>
		/// <param name="index">Index</param>
		/// <returns>Object reference.</returns>
		IObject* operator[](size_t index) const;

		/// <summary>
		/// Returns an reference to the ith's object pointer in this list. 
		/// </summary>
		/// <param name="index">Index. Must be smaller than <see cref="Count"/></param>
		/// <returns>Reference to the i-th object pointer.</returns>
		IObject*& operator[](size_t index);

		/// <summary>
		/// Returns how many objects are in this list.
		/// </summary>
		/// <returns>Number of objects in the list.</returns>
		size_t Count() const noexcept;

		/// <summary>
		/// Empties this list.
		/// </summary>
		void Clear();

		/// <summary>
		/// Finds objects that match the specified predicate.
		/// </summary>
		/// <param name="predicate">Predicate : (IObject*) -> bool </param>
		/// <returns>A vector of IObject pointers that match the predicate.</returns>
		std::vector<IObject*> Find(std::function<bool(IObject*)> predicate) const noexcept;

		std::vector<IObject*>::iterator begin() noexcept;
		std::vector<IObject*>::const_iterator begin() const noexcept;
		std::vector<IObject*>::iterator end() noexcept;
		std::vector<IObject*>::const_iterator end() const noexcept;

		friend class IObject;
	};
}