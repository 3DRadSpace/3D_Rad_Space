#pragma once
#include "../Controls/Dialog.hpp"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>

class FindObjectDialog : public Dialog
{
	HWND _listBox;
	HWND _okButton;
	HWND _cancelButton;

	Engine3DRadSpace::Objects::ObjectList* _list;
	size_t _selectedObjectID;

	void _createForms();
public:
	FindObjectDialog(HWND owner, HINSTANCE hInstance, Engine3DRadSpace::Objects::ObjectList* list);

	std::optional<size_t> ShowDialog();

	friend INT_PTR WINAPI FindObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};