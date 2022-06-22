#pragma once
#include "Libs.hpp"
#include "ResourceCreationException.hpp"
#include "IObjectEditorWindow.hpp"

class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	HWND _window;
	HWND _owner;
	HGLOBAL _hGlobal;
	LPDLGTEMPLATE _dialogTemplate;
	LPWORD _templateMemIndex;
	IObjectEditorWindow* _objectType;
	ObjectEditorDialog* _globalInstance;
	HWND* _controls;
	size_t numControls;

	void _createForms();

public:
	ObjectEditorDialog(HINSTANCE hInstance, HWND owner, IObjectEditorWindow* objectType);

	int ShowDialog();

	ObjectEditorDialog* GetGlobalInstance();
	HWND GetWindow();

	friend INT_PTR CALLBACK ObjectEditor_DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	~ObjectEditorDialog();
};
