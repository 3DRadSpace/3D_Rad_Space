#pragma once

///Reflecting IObject types:
#include "ReflectedObject.hpp"

///Reflects a class that inherits IObject.
#define REFL_BEGIN(ObjectType, ObjectName, ObjectCategory, ObjectDescription) ::Engine3DRadSpace::Reflection::ReflectedObject ObjectType##ReflInstance( ::Engine3DRadSpace::Reflection::ObjectTag<ObjectType>{}, ObjectName, ObjectCategory, ObjectDescription, {

/// Reflects a field, with given information. 
#define REFL_FIELD(ObjectType,FieldType, FieldName, FieldVisibleName, DefaultValue, Description) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedField<FieldType>(offsetof(ObjectType, FieldName), FieldVisibleName, Description, DefaultValue)),

//Reflection "declaration" ending.
#define REFL_END static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedField<void>())});

//Class reflection forward declaration.
#define REFL_FWD(ObjectName) extern DLLEXPORT ::Engine3DRadSpace::Reflection::ReflectedObject ObjectName##ReflInstance;






///Reflecting enums:
#include "ReflectedEnum.hpp"

//Reflects a enum, for use in editor
#define REFL_ENUM_BEGIN(EnumType) ::Engine3DRadSpace::Reflection::ReflectedEnum EnumType##EnumReflInstance(::Engine3DRadSpace::Tag<EnumType>{}, std::initializer_list<::Engine3DRadSpace::Reflection::EnumEntry>{

//Reflects a enum entry, with a visible name and a number
#define REFL_ENUM_ENTRY(Name, Num) ::Engine3DRadSpace::Reflection::EnumEntry{ .VisibleName = Name, .Value = static_cast<int>(Num)},

//Ends enum reflection
#define REFL_ENUM_END ::Engine3DRadSpace::Reflection::EnumEntry{ .VisibleName = "__SentinelValue", .Value = std::numeric_limits<int>::max()}});

//Forward reference to enumeration reflection instance
#define REFL_ENUM_FWD(EnumType) extern ::Engine3DRadSpace::Reflection::ReflectedEnum EnumName##EnumReflInstance;

#define REFL_FIELD_ENUM(ObjectType, EnumType, FieldName, FieldVisibleName, DefaultValue, Description) static_cast<::Engine3DRadSpace::Reflection::IReflectedEnum*>()