#pragma once
#include "Libs.hpp"
#include "ResourceCreationException.hpp"
#include "ObjectEditorWindow.hpp"
#include "NumericTextbox.hpp"
#include "ColorBox.hpp"

class ObjectEditorDialog
{
	HINSTANCE _hInstance;
	HWND _window;
	HWND _owner;
	HGLOBAL _hGlobal;
	LPDLGTEMPLATE _dialogTemplate;
	LPWORD _templateMemIndex;
	ObjectEditorWindow* _objectWndInfo;
	static ObjectEditorDialog* _globalInstance;
	HWND* _controls;
	size_t numControls;
	std::vector<std::unique_ptr<ISubclassedControl>> _subclassedControls;
	HWND _okButton;
	HWND _cancelButton;
	HWND _helpButton;
	Engine3DRadSpace::IObject* _resultObject;

	void _createForms();
	Engine3DRadSpace::Point _calculateControlSize(const size_t index);
	Engine3DRadSpace::Point _calculateGroupSize(size_t index);
	size_t _countControls();

public:
	ObjectEditorDialog(HINSTANCE hInstance, HWND owner, ObjectEditorWindow* objectType, Engine3DRadSpace::IObject* obj);
	ObjectEditorDialog(ObjectEditorDialog&&) = delete;

	int ShowDialog();

	ObjectEditorDialog* GetGlobalInstance();
	HWND GetWindow();

	friend INT_PTR CALLBACK ObjectEditor_DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	~ObjectEditorDialog();
};

INT_PTR ObjectEditor_DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void _update_mX(int& x, int newVal);