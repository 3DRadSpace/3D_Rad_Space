#pragma once
#include "Libs.hpp"
#include "resource.h"
#include "Utilities.hpp"
#include "VisiblePropertiesManager.hpp"

class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	int result;
	HGLOBAL hGlobal;
	HWND _dlgWindow;

	LPDLGTEMPLATE dlgTemplate;

	VisiblePropertiesManager* _Fields;

	HWND* dlgControls;

public:
	ObjectEditorDialog(HINSTANCE hInstance,LPCSTR object_name,const VisiblePropertiesManager &visibleFields);
	
	int ShowDialog(HWND parent);

	HINSTANCE GetHINSTANCE();
	HWND GetDialogWindow();

	~ObjectEditorDialog();
};

