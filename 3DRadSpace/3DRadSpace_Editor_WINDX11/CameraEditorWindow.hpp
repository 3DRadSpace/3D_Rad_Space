#pragma once
#include "IObjectEditorWindow.hpp"

class CameraEditorWindow : public IObjectEditorWindow
{
public:
	virtual Engine3DRadSpace::IObject* CreateObject(EditableFieldCollection* editableFields) override;
	virtual const __rawstring GetHelpURL() override;
	virtual const char* GetObjectName() override;
	virtual EditableFieldCollection GetFields() override;
};

