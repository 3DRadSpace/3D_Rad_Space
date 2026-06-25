#include "ObjectID.hpp"
#include "ObjectList.hpp"
#include "ChildObjectCollection.hpp"

using namespace Engine3DRadSpace::Objects;

ObjectID::operator size_t() const noexcept
{
	return ID;
}

IObject* ObjectID::Get(ObjectList* list) const noexcept
{
	return list->operator[](ID);
}

IObject* ObjectID::Get(ChildObjectCollection* collection) const noexcept
{
	return collection->operator[](ID);
}