#pragma once

#include <Engine3DRadSpace/IObject.hpp>
#include <CommCtrl.h>
#include "HelperFunctions.hpp"

class AddObjectDialog
{
	HGLOBAL hGlobal;
	HWND window;
	HWND owner;
	HINSTANCE hInstance;
	LPDLGTEMPLATE dialogTemplate;

	HWND listView;
	HIMAGELIST imageList;
	int itemIndex = 0;

	void addCategory(const std::string& category, int index);
	void addObject(const std::string& objectName, int imageIndex, int index);
public:
	AddObjectDialog(HWND owner, HINSTANCE hInstance);

	Engine3DRadSpace::IObject* ShowDialog();
	void CreateForms();
	void Resize();

	~AddObjectDialog();

	friend INT_PTR WINAPI AddObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};