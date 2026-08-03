#include "ObjectRegistry.hpp"

std::vector<Engine3DRadSpace::Reflection::ReflectedObject*>& Engine3DRadSpace::Internal::GetInternalObjectsList()
{
	static std::vector<Engine3DRadSpace::Reflection::ReflectedObject*> instance;
	return instance;
}
