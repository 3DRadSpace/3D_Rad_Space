#pragma once

#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "Dialog.hpp"
#include "EditObjectDialog.hpp"

class AddObjectDialog : public Dialog
{
	HWND listView;
	HIMAGELIST imageList;
	int itemIndex = 0;

	void addCategory(const std::string& category, int index);
	void addObject(const std::string& objectName, int imageIndex, int index);

	void createForms();
	void resize();

	Engine3DRadSpace::Content::ContentManager *_content;
public:
	AddObjectDialog(HWND owner, HINSTANCE hInstance, Engine3DRadSpace::Content::ContentManager *content);

	static std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, Engine3DRadSpace::Reflection::ReflectedObject *>> Objects;

	static Engine3DRadSpace::Reflection::ReflectedObject *GetReflDataFromUUID(const Engine3DRadSpace::Reflection::UUID &uuid);

	[[nodiscard]] Engine3DRadSpace::IObject* ShowDialog();

	friend INT_PTR WINAPI AddObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	~AddObjectDialog();
};