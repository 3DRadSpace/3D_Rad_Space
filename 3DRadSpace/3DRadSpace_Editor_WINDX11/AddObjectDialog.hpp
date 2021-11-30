#pragma once
#include <windows.h>
#include "Libs.hpp"
#include "resource.h"
#include "Utilities.hpp"

using namespace Engine3DRadSpace;

const __rawstring* const AddObjectDialogClassName = TEXT("3DRADSPACE_ADD0BJECT_DIALOG");

INT_PTR CALLBACK AddObject_DialogProcess(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class AddObjectDialog
{
	HGLOBAL hGlobal;
	LPDLGTEMPLATE lpDialogTemplate;
	HINSTANCE _hInstance;

	LPWORD _TemplateMemIndex;
	LPWSTR _title;
	int _nchar;

	HWND _dialogWindow;
	HWND _listView;

	HIMAGELIST _imageList;

	void _createItemForList(__rawstring* name,int imageIndex,int groupIndex);
	void _createGroupForList(wchar_t* name, int index);

	void _insertImage(HBITMAP icon);

public:
	static AddObjectDialog* GlobalInstance;

	AddObjectDialog(HINSTANCE hInstance);

	bool DialogOpen;

	int ShowDialog(HWND owner);
	HWND GetWindow();
	HWND GetListView();

	void Resize();

	~AddObjectDialog();
};

