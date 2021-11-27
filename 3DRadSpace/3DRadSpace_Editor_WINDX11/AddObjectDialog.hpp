#pragma once
#include <Windows.h>
#include "Libs.hpp"
#include "resource.h"

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

	HIMAGELIST _hImageListSmall,_hImageListBig;

	void _createItemForList(LVITEM* item,__rawstring* name,int imageIndex,int groupIndex);
	void _createGroupForList(LVGROUP* group, wchar_t* name, int index);

	void _insertImage(HICON icon);
public:
	static AddObjectDialog* GlobalInstance;


	AddObjectDialog(HINSTANCE hInstance);

	bool DialogOpen;

	int ShowDialog(HWND owner);
	HWND GetWindow();

	~AddObjectDialog();
};

