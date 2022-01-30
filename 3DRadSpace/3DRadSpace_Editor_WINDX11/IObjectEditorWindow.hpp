#pragma once
#include "EditableFieldCollection.hpp"

class IObjectEditorWindow
{
public:
	virtual Engine3DRadSpace::IObject* CreateObject(EditableFieldCollection* editableFields) = 0;
	virtual std::vector<std::variant<std::string, float>> SetEditorWindowValues(Engine3DRadSpace::IObject* obj) = 0;
	virtual std::string GetHelpURL() = 0;
};