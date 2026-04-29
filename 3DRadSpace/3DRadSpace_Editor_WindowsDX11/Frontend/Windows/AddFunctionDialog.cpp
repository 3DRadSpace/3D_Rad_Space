#include "AddFunctionDialog.hpp"
#include "../Controls/PropertyGrid.h"
#include "EditorWindow.hpp"
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#include <tchar.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;

constexpr UINT_PTR AFND_LIST_OBJECTS = 2000;
constexpr UINT_PTR AFND_LIST_FUNCTIONS = 2001;
constexpr UINT_PTR AFND_PROPERTY_GRID = 2002;
constexpr UINT_PTR AFND_OK_BTN = 2100;
constexpr UINT_PTR AFND_CANCEL_BTN = 2101;

INT_PTR WINAPI AddFunctionDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AddFunctionDialog* fndlg = nullptr;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		fndlg = reinterpret_cast<AddFunctionDialog*>(lParam);
		fndlg->window = hwnd;
		fndlg->createForms();
		return 1;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		return 1;
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, IDCANCEL);
		return 1;
	}
	case WM_SIZE:
	{
		if(fndlg) fndlg->resize();
		return 1;
	}
	case WM_COMMAND:
	{
		return 1;
	}
	case WM_NOTIFY:
	{
		switch ((reinterpret_cast<LPNMHDR>(lParam))->code)
		{
		case NM_DBLCLK:
		{
			LPNMITEMACTIVATE item = reinterpret_cast<LPNMITEMACTIVATE>(lParam);

			if (item->iItem >= 0)
			{
				//EditObjectDialog dialog(hwnd, aod->hInstance, e3drsp_internal_objects_list[item->iItem], aod->_content);
				//EndDialog(hwnd, reinterpret_cast<INT_PTR>(dialog.ShowDialog()));
			}
			break;
		}
		default:
			break;
		}
		return 1;
	}
	default:
		return 0;
	}
}

AddFunctionDialog::AddFunctionDialog(
	HWND owner, 
	HINSTANCE hInstance,
	ObjectList* list
) : Dialog(owner, hInstance, nullptr, "Find object method"),
	_list(list)
{
}

std::optional<EventInvocationRepresentation> AddFunctionDialog::ShowDialog()
{
	return std::nullopt;
}

void AddFunctionDialog::createForms()
{
	_listObjects = CreateWindowExA(
		0,
		WC_LISTVIEWA,
		nullptr,
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
		10, 10, 200, 400,
		window,
		(HMENU)AFND_LIST_OBJECTS,
		hInstance,
		nullptr
	);

	EditorWindow::PopulateObjectList(_list, _listObjects);

	_listFunctions = CreateWindowExA(
		0,
		WC_LISTBOXA,
		nullptr,
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
		220, 10, 200, 400,
		window,
		(HMENU)AFND_LIST_FUNCTIONS,
		hInstance,
		nullptr
	);

	_argsPropertyGrid = New_PropertyGrid(window, static_cast<DWORD>(AFND_PROPERTY_GRID));

	RECT argsGridCoords{};
	argsGridCoords.left = 430;
	argsGridCoords.top = 10;
	argsGridCoords.right = 780;
	argsGridCoords.bottom = 400;

	GetWindowRect(_argsPropertyGrid, &argsGridCoords);
	ShowWindow(_argsPropertyGrid, SW_SHOW);

	_cancelBtn = CreateWindowExA(
		0,
		"Button",
		"Cancel",
		WS_CHILD | WS_VISIBLE,
		430, 420, 80, 30,
		window,
		(HMENU)AFND_CANCEL_BTN,
		hInstance,
		nullptr
	);

	_okBtn = CreateWindowExA(
		0,
		"Button",
		"OK",
		WS_CHILD | WS_VISIBLE,
		530, 420, 80, 30,
		window,
		(HMENU)AFND_OK_BTN,
		hInstance,
		nullptr
	);
}

void AddFunctionDialog::selectObject(size_t itemID)
{
	if (itemID >= _list->Count()) return;
	_selectedObjectID = itemID;

	auto obj = _list->operator[](itemID);
	if (obj == nullptr) return;

	_selectedObject = obj;

	auto reflObj = Internal::GetReflDataFromUUID(obj->GetUUID());
	if (reflObj == nullptr) return;

	SendMessageA(_listFunctions, LB_RESETCONTENT, 0, 0);

	for (auto& f : *reflObj)
	{
		auto fn = dynamic_cast<IReflectedFunction*>(f);
		if (fn == nullptr) continue;

		auto fnName = fn->FieldName();

		SendMessageA(_listFunctions, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(fnName.c_str()));
	}
}

void AddFunctionDialog::selectFunction(size_t itemID)
{
	if (_selectedObject == nullptr) return;
	
	_value.FunctionID = itemID;
	_value.OwnerObject = _selectedObjectID;

	auto reflObj = Internal::GetReflDataFromUUID(_selectedObject->GetUUID());

	for (size_t i = 0; auto& f : *reflObj)
	{
		auto fn = dynamic_cast<IReflectedFunction*>(f);
		if (fn == nullptr) continue;
		if (i == itemID)
		{
			_selectedFunction = fn;
			break;
		}

		++i;
	}

	fillArgsGrid();
}

void AddFunctionDialog::resize()
{
}

void AddFunctionDialog::fillArgsGrid()
{
	PropGrid_ResetContent(_argsPropertyGrid);

	for (auto& arg : _selectedFunction->ParametersInfo())
	{
		if (arg.Size() == 0) continue;
		if (arg.Size() == 1)
		{
			PROPGRIDITEM newCtrl{};
			PropGrid_ItemInit(newCtrl);
			newCtrl.lpszCatalog = const_cast<LPTSTR>(_T("Arguments"));

            if (arg[0].Name.empty())
			{
				newCtrl.lpszPropName = const_cast<LPTSTR>(_T("Arg0"));
			}
			else
			{
#ifdef UNICODE
				_argNames.emplace_back(arg[0].Name.begin(), arg[0].Name.end());
				newCtrl.lpszPropName = const_cast<LPTSTR>(_argNames.back().c_str());
#else
				_argNames.push_back(arg[0].Name);
				newCtrl.lpszPropName = const_cast<LPTSTR>(_argNames.back().c_str());
#endif
			}
			
			_setCtrl(newCtrl, arg[0].Type);
		}
		else
		{
			for (auto& subArg : arg)
			{
				PROPGRIDITEM newCtrl{};
				PropGrid_ItemInit(newCtrl);

				if (subArg.Name.empty())
				{
					newCtrl.lpszPropName = const_cast<LPTSTR>(_T("Subarg"));
				}
				else
				{
#ifdef UNICODE
					_argNames.emplace_back(subArg.Name.begin(), subArg.Name.end());
					newCtrl.lpszPropName = const_cast<LPTSTR>(_argNames.back().c_str());
#else
					_argNames.push_back(subArg].Name);
					newCtrl.lpszPropName = const_cast<LPTSTR>(_argNames.back().c_str());
#endif
				}

				_setCtrl(newCtrl, subArg.Type);
			}
		}
	}
}

void AddFunctionDialog::_setCtrl(PROPGRIDITEM& item, FieldRepresentationType type)
{
	switch (type)
	{
	case FieldRepresentationType::None:
	case FieldRepresentationType::Function:
	case FieldRepresentationType::Event:
		break;
	case FieldRepresentationType::Boolean:
		item.iItemType = PIT_CHECK;
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	case FieldRepresentationType::Integer:
	case FieldRepresentationType::Unsigned:
	case FieldRepresentationType::Float:
	case FieldRepresentationType::String:
		item.iItemType = PIT_EDIT;
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	case FieldRepresentationType::Quaternion:
		item.lpszPropName = const_cast<LPTSTR>(_T("X"));
		item.lpszCatalog = const_cast<LPTSTR>(_T("Quaternion (Euler Angles)"));
		item.iItemType = PIT_EDIT;
		PropGrid_AddItem(_argsPropertyGrid, &item);

		item.lpszPropName = const_cast<LPTSTR>(_T("Y"));
		PropGrid_AddItem(_argsPropertyGrid, &item);

		item.lpszPropName = const_cast<LPTSTR>(_T("Z"));
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	case FieldRepresentationType::Image:
	case FieldRepresentationType::Model:
	case FieldRepresentationType::Font:
	case FieldRepresentationType::Skybox:
	case FieldRepresentationType::Sound:
		item.iItemType = PIT_EDIT;
		item.lpszPropDesc = const_cast<LPTSTR>(_T("Asset ID"));
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	case FieldRepresentationType::Key:
		item.iItemType = PIT_EDIT;
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	case FieldRepresentationType::Enum:
		item.iItemType = PIT_COMBO;
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	case FieldRepresentationType::Color:
		item.iItemType = PIT_COLOR;
		PropGrid_AddItem(_argsPropertyGrid, &item);
		break;
	default:
		break;
	}
}