#pragma once
#include "IObjectReflection.hpp"

struct FieldGroup
{
	const char* const Name;
	const int NumFields;
};

struct ObjectEditorWindow
{
	ObjectEditorWindow(
		std::function<Engine3DRadSpace::IObject* ()> f,
		Engine3DRadSpace::Reflection::Reflect& refl,
		Engine3DRadSpace::Point WndSize,
		const char* helpUrl,
		const char* helpFile,
		const char* objName,
		FieldGroup* groups,
		size_t numGroups
	);

	const std::function<Engine3DRadSpace::IObject* ()> CreateEmptyObject;

	const Engine3DRadSpace::Reflection::Reflect& Reflection;
	const Engine3DRadSpace::Point WindowSize;
	const char* const HelpURLAddress;
	const char* const OfflineHelpPath;
	const char* const Name;
	const FieldGroup* const Groups;
	const size_t NumGroups;
};