#pragma once
#include "../Controls/Dialog.hpp"
#include "../Controls/PropertyGrid.h"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Reflection/ReflectedObject.hpp>
#include <Engine3DRadSpace/Reflection/ReflectedMemberFunction.hpp>
#include <Engine3DRadSpace/Projects/EventInvocationRepresentation.hpp>

class AddFunctionDialog : public Dialog
{
	HWND _listObjects;
	HWND _listFunctions;
	HWND _argsPropertyGrid;
	HWND _cancelBtn;
	HWND _okBtn;

	Engine3DRadSpace::Objects::ObjectList* _list;
	Engine3DRadSpace::Objects::IObject* _selectedObject;
	size_t _selectedObjectID;
	Engine3DRadSpace::Reflection::IReflectedFunction* _selectedFunction;

	Engine3DRadSpace::Projects::EventInvocationRepresentation _value;
#ifdef UNICODE
	std::vector<std::wstring> _argNames;
#else
	std::vector<std::string> _argNames;
#endif

	void createForms();
	void resize();
	void selectObject(size_t itemID);
	void selectFunction(size_t itemID);
	void fillArgsGrid();
	void _setCtrl(PROPGRIDITEM& item, Engine3DRadSpace::Reflection::FieldRepresentationType type);
public:
	AddFunctionDialog(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Objects::ObjectList* list
	);

	std::optional<Engine3DRadSpace::Projects::EventInvocationRepresentation> ShowDialog();

	friend INT_PTR WINAPI AddFunctionDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};