#pragma once
#include "ReflectedObject.hpp"

///Reflects a class that inherits IObject.
#define REFL_BEGIN(ObjectType, ObjectName, ObjectCategory, ObjectDescription) Engine3DRadSpace::Reflection::ReflectedObject ObjectType##ReflInstance( Engine3DRadSpace::Reflection::ObjectTag<ObjectType>{}, ObjectName, ObjectCategory, ObjectDescription, {

/// Reflects a field, with given information. 
#define REFL_FIELD(ObjectType,FieldType, FieldName, FieldVisibleName, DefaultValue, Description) \
static_cast<Engine3DRadSpace::Reflection::IReflectedField*>( new Engine3DRadSpace::Reflection::ReflectedField<FieldType>(offsetof(ObjectType, FieldName), FieldVisibleName, Description, DefaultValue)),

//Reflection "declaration" ending.
#define REFL_END static_cast<Engine3DRadSpace::Reflection::IReflectedField*>( new Engine3DRadSpace::Reflection::ReflectedField<void>())});

//Class reflection forward declaration.
#define REFL_DEF(ObjectName) extern DLLEXPORT Engine3DRadSpace::Reflection::ReflectedObject ObjectName##ReflInstance;