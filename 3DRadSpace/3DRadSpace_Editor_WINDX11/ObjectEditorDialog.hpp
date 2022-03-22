#pragma once
#include "Libs.hpp"
#include "resource.h"
#include "GDIFuncs.hpp"
#include "IObjectEditorWindow.hpp"

class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	int result;
	HGLOBAL hGlobal;
	HWND _dlgWindow;

	LPDLGTEMPLATE dlgTemplate;
	IObjectEditorWindow* _objectData;
	HWND* dlgControls;
public:
	static ObjectEditorDialog* GlobalInstance;

	ObjectEditorDialog(HINSTANCE hInstance, IObjectEditorWindow* object_info);
	
	int ShowDialog(HWND parent);
	void CreateDialogForms();

	HINSTANCE GetHINSTANCE();
	HWND GetDialogWindow();

	~ObjectEditorDialog();

	friend INT_PTR CALLBACK ObjectEditor_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

INT_PTR CALLBACK ObjectEditor_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
