#pragma once

#include <Engine3DRadSpace/Reflection.hpp>
#include "Dialog.hpp"

class AddObjectDialog : public Dialog
{
	HWND listView;
	HIMAGELIST imageList;
	int itemIndex = 0;

	void addCategory(const std::string& category, int index);
	void addObject(const std::string& objectName, int imageIndex, int index);

	void createForms();
	void resize();

	std::vector<Engine3DRadSpace::Reflection::ReflectedObject *> objectData;
public:
	AddObjectDialog(HWND owner, HINSTANCE hInstance);

	[[nodiscard]] Engine3DRadSpace::IObject* ShowDialog();

	friend INT_PTR WINAPI AddObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	~AddObjectDialog();
};