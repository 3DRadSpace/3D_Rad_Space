#pragma once
#include "IObjectReflection.hpp"

struct FieldGroup
{
	const char* const Name;
	const int NumFields;
};

struct ObjectEditorWindow
{
	Engine3DRadSpace::IObject* (const* CreateEmptyObject)();

	const Engine3DRadSpace::Reflection::Reflect& Reflection;
	const Engine3DRadSpace::Point WindowSize;
	const char* const HelpURLAddress;
	const char* const OfflineHelpPath;
	const char* const Name;
	const FieldGroup* const Groups;
	const size_t NumGroups;
};