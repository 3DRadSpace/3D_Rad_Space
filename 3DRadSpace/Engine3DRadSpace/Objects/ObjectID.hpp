#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Objects
{
	class ObjectList;
	class ObjectCollection;
	class IObject;
	struct E3DRSP_OBJECTS_EXPORT ObjectID
	{
		ObjectID() = default;
		ObjectID(size_t id) : ID(id) {}

		ObjectID(const ObjectID&) = default;
		ObjectID(ObjectID&&) noexcept = default;

		ObjectID& operator=(const ObjectID&) = default;
		ObjectID& operator=(ObjectID&&) noexcept = default;

		size_t ID;

		operator size_t() const noexcept;

		IObject* Get(ObjectList* list) const noexcept;
		IObject* Get(ObjectCollection* collection) const noexcept;
	};
}