#pragma once
#include "EditableFieldCollection.hpp"

class IObjectEditorWindow
{
public:
	virtual Engine3DRadSpace::IObject* CreateObject(EditableFieldCollection* editableFields) = 0;
	virtual const char* GetObjectName() = 0;
	virtual const __rawstring GetHelpURL() = 0;
	virtual EditableFieldCollection GetFields() = 0;

	Engine3DRadSpace::IObject* GameObject;
};