#pragma once
#include "../Controls/Dialog.hpp"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Reflection/ReflectedObject.hpp>
#include <Engine3DRadSpace/Reflection/ReflectedMemberFunction.hpp>
#include <Engine3DRadSpace/Projects/EventRepresentation.hpp>

class AddFunctionDialog : public Dialog
{
	HWND _listObjects;
	HWND _listFunctions;
	HWND _cancelBtn;
	HWND _okBtn;

	Engine3DRadSpace::Objects::ObjectList* _list;
	Engine3DRadSpace::Objects::IObject* _selectedObject;
	size_t _selectedObjectID;

	Engine3DRadSpace::Projects::EventInvocationRepresentation _value;

	void createForms();
	void resize();
	void selectObject(size_t itemID);
	void selectFunction(size_t itemID);
public:
	AddFunctionDialog(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Objects::ObjectList* list
	);

	std::optional<Engine3DRadSpace::Projects::EventInvocationRepresentation> ShowDialog();

	friend INT_PTR WINAPI AddFunctionDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};