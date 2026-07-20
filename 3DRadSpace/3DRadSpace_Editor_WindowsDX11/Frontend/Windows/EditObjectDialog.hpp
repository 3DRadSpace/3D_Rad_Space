#pragma once

#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "..\Controls\Dialog.hpp"
#include <variant>
#include "..\Controls\IControl.hpp"

class EditObjectDialog : public Dialog
{
	Engine3DRadSpace::Reflection::ReflectedObject* objRefl;
	Engine3DRadSpace::Content::ContentManager *_content;
	std::vector<std::variant<HWND,IControl*>> windows;
	std::vector<HBITMAP> images;
	Engine3DRadSpace::Objects::IObject* object;

	HWND helpButton;
	HWND okButton;
	HWND cancelButton;

	std::string _helpUrl = "https://3dradspace.github.io/docs/objects.html";

	void createForms();
	void setObject();
public:
	EditObjectDialog(
		HWND owner,
		HINSTANCE hInstance, 
		Engine3DRadSpace::Reflection::ReflectedObject *data,
		Engine3DRadSpace::Content::ContentManager* content,
		Engine3DRadSpace::Objects::IObject *object = nullptr
	);

	[[nodiscard]] Engine3DRadSpace::Objects::IObject* ShowDialog();

	~EditObjectDialog();

	friend INT_PTR WINAPI EditObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};