#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include "../HelperFunctions.hpp"

class Dialog
{
protected:
	HGLOBAL hGlobal;
	HWND window;
	HWND owner;
	HINSTANCE hInstance;
	LPDLGTEMPLATE dialogTemplate;
	DLGPROC dialogProc;

	Dialog(HWND hwndOwner, HINSTANCE instance, DLGPROC dlgproc, const std::string& windowTitle);
	INT_PTR ShowDialog(void* data);
public:
	Dialog(Dialog&) = delete;
	Dialog(Dialog&&) = delete;

	Dialog& operator =(Dialog&) = delete;
	Dialog&& operator = (Dialog&&) = delete;

	virtual ~Dialog();
};