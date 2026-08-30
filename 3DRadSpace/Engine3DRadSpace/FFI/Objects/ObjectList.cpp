#include "ObjectList.h"
#include "../../Objects/ObjectList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

E3DRSP_ObjectList E3DRSP_ObjectList_Create(E3DRSP_IGame game)
{
	return new ObjectList(static_cast<IGame*>(game));
}

unsigned E3DRSP_ObjectList_Add(E3DRSP_ObjectList list, E3DRSP_IObject obj)
{
	return static_cast<ObjectList*>(list)->Add(static_cast<IObject*>(obj));
}

E3DRSP_IObject E3DRSP_ObjectList_FindByID(E3DRSP_ObjectList list, unsigned id)
{
	return static_cast<ObjectList*>(list)->operator[](id);
}

E3DRSP_IObject E3DRSP_ObjectList_FindByName(E3DRSP_ObjectList list, const char* name)
{
	return static_cast<ObjectList*>(list)->Find(name);
}

void E3DRSP_ObjectList_RemoveByID(E3DRSP_ObjectList list, unsigned id)
{
	static_cast<ObjectList*>(list)->Remove(id);
}

void E3DRSP_ObjectList_RemoveByName(E3DRSP_ObjectList list, const char* name)
{
	static_cast<ObjectList*>(list)->Remove(name);
}