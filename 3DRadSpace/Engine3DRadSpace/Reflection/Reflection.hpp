#pragma once

/// ---------------------------------------------------------------------------
///								Reflecting objects:
/// ---------------------------------------------------------------------------
#include "ReflectedObject.hpp"

///Reflects a class that inherits IObject.
#define REFL_BEGIN(ObjectType, ObjectName, ObjectCategory, ObjectDescription) ::Engine3DRadSpace::Reflection::ReflectedObject ObjectType##ReflInstance( ::Engine3DRadSpace::Reflection::ObjectTag<ObjectType>{}, ObjectName, ObjectCategory, ObjectDescription, {

/// Reflects a field, with given information. 
#define REFL_FIELD(ObjectType,FieldType, FieldName, FieldVisibleName, DefaultValue, Description) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedField<FieldType>(offsetof(ObjectType, FieldName), FieldVisibleName, Description, DefaultValue)),

/// Reflects a field with specified get/set functions.
#define REFL_FIELD_GS(ObjectType, FieldType, FnGet, FnSet, FieldVisibleName, DefaultValue, Description) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>(new ::Engine3DRadSpace::Reflection::ReflectedFieldGS<FieldType, ObjectType>( FieldVisibleName, Description, FnGet, FnSet, DefaultValue)),

//Reflection "declaration" ending.
#define REFL_END static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedField<void>())});

//Class reflection forward declaration.
#define REFL_FWD(ObjectName) extern __declspec(dllexport) ::Engine3DRadSpace::Reflection::ReflectedObject ObjectName##ReflInstance;

/// ---------------------------------------------------------------------------
///								Reflecting enums:
/// ---------------------------------------------------------------------------
#include "ReflectedEnum.hpp"

//Reflects a enum, for use in editor
#define REFL_ENUM_BEGIN(EnumType, EnumName) ::Engine3DRadSpace::Reflection::ReflectedEnum EnumType##EnumReflInstance(::Engine3DRadSpace::Tag<EnumType>{}, EnumName, std::initializer_list<::Engine3DRadSpace::Reflection::EnumEntry>{

//Reflects a enum entry, with a visible name and a number
#define REFL_ENUM_ENTRY(Name, Num) ::Engine3DRadSpace::Reflection::EnumEntry{ .VisibleName = Name, .Value = static_cast<int>(Num)},

//Ends enum reflection
#define REFL_ENUM_END ::Engine3DRadSpace::Reflection::EnumEntry{ .VisibleName = "INT_MAX", .Value = std::numeric_limits<int>::max()}});

//Forward reference to enumeration reflection instance
#define REFL_ENUM_FWD(EnumType) extern ::Engine3DRadSpace::Reflection::ReflectedEnum EnumName##EnumReflInstance;

//Reflect a enum field
#define REFL_FIELD_ENUM(ObjectType, EnumType, FieldName, FieldVisibleName, DefaultValue, Description) static_cast<::Engine3DRadSpace::Reflection::IReflectedEnum*>()

/// ---------------------------------------------------------------------------
///								Reflecting assets:
/// ---------------------------------------------------------------------------
#include "ReflectedAsset.hpp"

#define REFL_ASSET_ID(ObjectType, AssetType, FieldName, FieldVisibleName, Description) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedAsset<ObjectType, AssetType>(offsetof(ObjectType, FieldName), FieldVisibleName, Description)),


/// ---------------------------------------------------------------------------
///								Reflecting functions:
/// ---------------------------------------------------------------------------
#include "ReflectedMemberFunction.hpp"

//Reflect a member function(method)
#define REFL_METHOD(ObjectType, ReturnType, Function, Name, ...) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedMemberFunction<ReturnType, ObjectType, __VA_ARGS__>(Name, Function)),

#include "ReflectedFunction.hpp"
#define REFL_FUNCTION(ReturnType, Function, Name, ...) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::ReflectedFunction<ReturnType, __VA_ARGS__>(Name, Function)),

/// ---------------------------------------------------------------------------
///								Metadata
/// ---------------------------------------------------------------------------
/// Supported attributes are:
/// - "HelpURL": Provides a URL to the help documentation for the object being reflected.
/// - "CustomWindow": Specifies that the given object doesn't use the default editor window, but an custom one instead. The value is the name of the function that creates the custom window.
///                   Refer to CustomEditObjectWindow inside the Plugin library for more details.
#include "Attribute.hpp"

#define REFL_ATTR(Name, Value) static_cast<::Engine3DRadSpace::Reflection::IReflectedField*>( new ::Engine3DRadSpace::Reflection::Attribute(Name, Value)),