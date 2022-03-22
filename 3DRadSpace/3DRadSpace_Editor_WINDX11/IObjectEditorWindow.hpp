#pragma once
#include "Libs.hpp"

enum EditableFieldType
{
	Undefined = 0,
	TextboxesOneLine,
	MultilineTextbox,
	NumericTextboxes,
	UpDowns,
	Color,
	Key,
	MultipleKeys
};

class IObjectEditorWindow
{
public:
	virtual Engine3DRadSpace::IObject* CreateObject(std::vector<__stdstring> &fieldsInput) = 0;
	virtual const char* GetObjectName() = 0;
	virtual const __rawstring GetHelpURL() = 0;

	virtual __stdstring* GetFieldNames() = 0;
	virtual size_t GetFieldNamesCount() = 0;

	virtual __stdstring* GetFieldValues() = 0;
	virtual size_t GetFieldValuesCount() = 0;

	virtual std::vector<EditableFieldType> GetFieldFormTypes() = 0;


	Engine3DRadSpace::IObject* GameObject;
};