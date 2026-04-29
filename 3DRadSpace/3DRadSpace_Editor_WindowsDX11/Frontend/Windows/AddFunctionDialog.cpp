#include "AddFunctionDialog.hpp"
#include "EditorWindow.hpp"
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;

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
		nullptr,
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
		nullptr,
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
}

void AddFunctionDialog::resize()
{
}