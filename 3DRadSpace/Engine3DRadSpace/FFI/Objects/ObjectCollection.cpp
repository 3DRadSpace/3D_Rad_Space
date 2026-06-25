#include "ObjectCollection.h"
#include "../../Objects/ObjectCollection.hpp"
#include "../../Objects/IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

E3DRSP_ObjectCollection E3DRSP_ObjectCollection_Create(E3DRSP_IObject owner)
{
	return new ChildObjectCollection(static_cast<IObject*>(owner));
}

void E3DRSP_ObjectCollection_Add(E3DRSP_ObjectCollection collection, E3DRSP_IObject object)
{
	static_cast<ChildObjectCollection*>(collection)->Add(static_cast<IObject*>(object));
}

void E3DRSP_ObjectCollection_Remove(E3DRSP_ObjectCollection collection, E3DRSP_IObject object)
{
	static_cast<ChildObjectCollection*>(collection)->Remove(static_cast<IObject*>(object));
}

void E3DRSP_ObjectCollection_RemoveID(E3DRSP_ObjectCollection collection, size_t index)
{
	static_cast<ChildObjectCollection*>(collection)->Remove(index);
}

E3DRSP_IObject E3DRSP_ObjectCollection_At(E3DRSP_ObjectCollection collection, size_t index)
{
	return static_cast<E3DRSP_IObject>(static_cast<ChildObjectCollection*>(collection)->operator[](index));
}

size_t E3DRSP_ObjectCollection_Count(E3DRSP_ObjectCollection collection)
{
	return static_cast<ChildObjectCollection*>(collection)->Count();
}

void E3DRSP_ObjectCollection_Clear(E3DRSP_ObjectCollection collection)
{
	static_cast<ChildObjectCollection*>(collection)->Clear();
}