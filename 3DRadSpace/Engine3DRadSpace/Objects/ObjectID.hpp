#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Objects
{
	class ObjectList;
	class ChildObjectCollection;
	class IObject;
	/// <summary>
	/// Alias for object numerical IDs.
	/// </summary>
	/// <remarks>
	/// This is used to reference objects when (de)serializing.
	/// </remarks>
	struct E3DRSP_OBJECTS_EXPORT ObjectID
	{
		/// <summary>
		/// Trival constructor.
		/// </summary>
		ObjectID() = default;
		/// <summary>
		/// Constructs an ObjectID from a size_t.
		///	</summary>
		ObjectID(size_t id) : ID(id) {}

		/// <summary>
		/// Trivial copy constructor.
		/// </summary>
		ObjectID(const ObjectID&) = default;
		/// <summary>
		/// Trivial move constructor.
		/// </summary>
		ObjectID(ObjectID&&) noexcept = default;

		/// <summary>
		/// Trivial copy assignment operator.
		/// </summary>
		ObjectID& operator=(const ObjectID&) = default;

		/// <summary>
		/// Trivial move assignment operator.
		/// </summary>
		ObjectID& operator=(ObjectID&&) noexcept = default;

		/// <summary>
		/// Underlying ID value.
		/// </summary>
		size_t ID;

		/// <summary>
		/// Conversion operator to size_t.
		/// </summary>
		operator size_t() const noexcept;

		/// <summary>
		/// Same as list[ID].
		/// </summary>
		/// <param name="list"></param>
		/// <returns></returns>
		IObject* Get(ObjectList* list) const noexcept;
		IObject* Get(ChildObjectCollection* collection) const noexcept;
	};
}