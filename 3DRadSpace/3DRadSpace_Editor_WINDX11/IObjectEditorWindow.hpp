#pragma once
#include "EditableFieldCollection.hpp"

class IObjectEditorWindow
{
public:
	virtual Engine3DRadSpace::IObject* CreateObject(EditableFieldCollection* editableFields) = 0;
	virtual std::vector<std::variant<__stdstring, float>> SetEditorWindowValues(Engine3DRadSpace::IObject* obj) = 0;
	virtual std::vector<std::variant<__stdstring,float>> SetEditorWindowDefaultValues() = 0;
	virtual std::vector<__stdstring> GetEditorWindowTitles() = 0;
	virtual __stdstring GetHelpURL() = 0;

	Engine3DRadSpace::IObject* GameObject;
};