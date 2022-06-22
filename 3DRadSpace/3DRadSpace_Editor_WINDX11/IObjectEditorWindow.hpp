#pragma once
#include "Libs.hpp"

enum EditableFieldType
{
	Undefined = 0,
	//used for strings
	TextboxOneLine,
	Checkbox, // used for booleans
	Coords3D, // used for Vector3's (position, rotation (Euler angles), scale
	Coords4D, //used for quaternions (rotations?)
	Integer, //used for natural numbers (for example the number of particles emtited )
	Color, //used for colors (for example the color mask of a sprite)
	Key, //keyboard key (for example, the controls of a First Person View camera)
	MultilineTextbox, //multiline string (for example the text of a TextPrint object)
	ImplementationDefined //custom controls
};

struct EditableFieldGroup
{
	char* Name;
	unsigned NumFields;
};

class IObjectEditorWindow
{
public:
	virtual Engine3DRadSpace::IObject* CreateObject(std::vector<__stdstring> &fieldsInput) = 0;
	virtual const char* GetObjectName() = 0;
	virtual const __rawstring GetHelpURL() = 0;

	virtual __rawstring* GetFieldNames() = 0;
	virtual size_t GetFieldNamesCount() = 0;

	virtual __rawstring* GetFieldValues() = 0;
	virtual size_t GetFieldValuesCount() = 0;

	virtual EditableFieldType* GetFieldFormTypes() = 0;
	virtual size_t GetFieldFormTypesCount() = 0;

	virtual unsigned GetWindowWidth() = 0;
	virtual unsigned GetWindowHeight() = 0;

	Engine3DRadSpace::IObject* GameObject;
};