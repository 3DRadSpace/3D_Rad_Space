#pragma once
#include "Libs.hpp"
#include "ResourceCreationException.hpp"

/*
class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	HWND _window;
	HWND _owner;
	HGLOBAL _hGlobal;
	LPDLGTEMPLATE _dialogTemplate;
	LPWORD _templateMemIndex;
	//IObjectEditorWindow* _objectType;
	ObjectEditorDialog* _globalInstance;
	HWND* _controls;
	size_t numControls;

	void _createForms();

	void update_rX(int& x, int newVal);

	Engine3DRadSpace::Point _calculateGroupSize(size_t index);
	size_t _countControls();

public:
	ObjectEditorDialog(HINSTANCE hInstance, HWND owner, void* objectType);

	int ShowDialog();

	ObjectEditorDialog* GetGlobalInstance();
	HWND GetWindow();

	friend INT_PTR CALLBACK ObjectEditor_DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	~ObjectEditorDialog();
};

INT_PTR ObjectEditor_DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
*/