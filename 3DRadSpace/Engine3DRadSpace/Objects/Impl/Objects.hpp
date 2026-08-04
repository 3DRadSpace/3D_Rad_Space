#pragma once
#include "../../Reflection/ReflectedObject.hpp"
#include "../ObjectRegistry/ObjectRegistry.hpp"

/// ------------------------------------------------------------------------------------------------
///
///					!!NOTICE!!
/// 
///		This is not meant to be used by the user, but by the engine itself.
///		This header only contains a forward reference to a function that loads the default 3DRadSpace objects (Skinmesh, Camera, etc).
/// 
/// ------------------------------------------------------------------------------------------------

namespace Engine3DRadSpace::Internal
{
	void E3DRSP_OBJECTS_IMPL_EXPORT LoadDefaultObjects();
	E3DRSP_OBJECTS_IMPL_EXPORT Reflection::ReflectedObject* GetReflDataFromUUID(const Reflection::UUID &uuid);
}