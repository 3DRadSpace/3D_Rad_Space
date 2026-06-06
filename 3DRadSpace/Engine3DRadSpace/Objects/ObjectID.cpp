#include "ObjectID.hpp"
#include "ObjectList.hpp"
#include "ObjectCollection.hpp"

using namespace Engine3DRadSpace::Objects;

ObjectID::operator size_t() const noexcept
{
	return ID;
}

IObject* ObjectID::Get(ObjectList* list) const noexcept
{
	return list->operator[](ID);
}

IObject* ObjectID::Get(ObjectCollection* collection) const noexcept
{
	return collection->operator[](ID);
}