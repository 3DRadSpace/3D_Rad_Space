#pragma once
#include "Libs.hpp"
#include "resource.h"
#include "Utilities.hpp"
#include "EditableFieldCollection.hpp"
#include "IObjectEditorWindow.hpp"

class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	int result;
	HGLOBAL hGlobal;
	HWND _dlgWindow;

	LPDLGTEMPLATE dlgTemplate;

	EditableFieldCollection _fields;

	IObjectEditorWindow* _objectData;

	HWND* dlgControls;

public:
	ObjectEditorDialog(HINSTANCE hInstance, const char* object_name, const EditableFieldCollection& visibleFields, IObjectEditorWindow* object_info);
	
	int ShowDialog(HWND parent);

	HINSTANCE GetHINSTANCE();
	HWND GetDialogWindow();

	~ObjectEditorDialog();
};

