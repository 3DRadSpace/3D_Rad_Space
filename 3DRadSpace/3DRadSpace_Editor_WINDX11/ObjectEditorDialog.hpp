#pragma once
#include "Libs.hpp"
#include "resource.h"
#include "Utilities.hpp"
#include "EditableFieldCollection.hpp"

class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	int result;
	HGLOBAL hGlobal;
	HWND _dlgWindow;

	LPDLGTEMPLATE dlgTemplate;

	EditableFieldCollection _fields;

	HWND* dlgControls;

public:
	ObjectEditorDialog(HINSTANCE hInstance, const char* object_name, const EditableFieldCollection& visibleFields);
	
	int ShowDialog(HWND parent);

	HINSTANCE GetHINSTANCE();
	HWND GetDialogWindow();

	~ObjectEditorDialog();
};

