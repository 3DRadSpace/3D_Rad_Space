#pragma once
#include "../../Reflection/ReflectedObject.hpp"
#include <vector>

#ifdef BUILDING_OBJECT_REGISTRY
	#define E3DRSP_OBJREG_EXPORT __declspec(dllexport)
#else
	#define E3DRSP_OBJREG_EXPORT __declspec(dllimport)
#endif

namespace Engine3DRadSpace::Internal
{
	/// <summary>
	/// Returns the singleton list of registered object types.
	/// This function guarantees a single shared instance across all DLLs.
	/// </summary>
	E3DRSP_OBJREG_EXPORT std::vector<Engine3DRadSpace::Reflection::ReflectedObject*>& GetInternalObjectsList();
}
