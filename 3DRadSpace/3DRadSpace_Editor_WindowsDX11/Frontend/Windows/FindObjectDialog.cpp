#include "FindObjectDialog.hpp"
#include "EditorWindow.hpp"
#undef max

INT_PTR WINAPI FindObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static FindObjectDialog* fod = nullptr;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		fod = reinterpret_cast<FindObjectDialog*>(lParam);
		fod->window = hwnd;
		fod->_createForms();
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
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
		{
			if (lParam == reinterpret_cast<LPARAM>(fod->_cancelButton))
			{
				EndDialog(hwnd, IDCANCEL);
				return 1;
			}
			if (lParam == reinterpret_cast<LPARAM>(fod->_okButton))
			{
				EndDialog(hwnd, IDOK);
				return 1;
			}
			break;
		}
		default:
			break;
		}
		return 1;
	}
	case WM_NOTIFY:
	{
		switch ((reinterpret_cast<LPNMHDR>(lParam))->code)
		{
		case NM_DBLCLK:
		{
			LPNMHDR lpnmh = (LPNMHDR)lParam;

			if (lpnmh->code == NM_DBLCLK)
			{
				HTREEITEM hItem = TreeView_GetSelection(lpnmh->hwndFrom);

				if (hItem != NULL)
				{
					TVITEM tvi{};
					tvi.hItem = hItem;
					tvi.mask = TVIF_PARAM;
					TreeView_GetItem(lpnmh->hwndFrom, &tvi);

					fod->_selectedObjectID = tvi.lParam;
				}
				break;
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

FindObjectDialog::FindObjectDialog(HWND owner, HINSTANCE hInstance, Engine3DRadSpace::Objects::ObjectList* list) :
	Dialog(owner, hInstance, FindObjectDialog_DlgProc, "Find object", 210, 180),
	_listBox(nullptr),
	_okButton(nullptr),
	_cancelButton(nullptr),
	_list(list),
	_selectedObjectID(std::numeric_limits<size_t>::max())
{
}

std::optional<size_t> FindObjectDialog::ShowDialog()
{
	INT_PTR r = Dialog::ShowDialog(this);
	if (r == IDOK) return _selectedObjectID;
	else return std::nullopt;
}

void FindObjectDialog::_createForms()
{
	_listBox = CreateWindowExA(
		0,
		WC_TREEVIEWA,
		"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS,
		5, 5, 390, 295,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	_okButton = CreateWindowExA(
		0,
		"Button",
		"OK",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		225, 305, 80, 30,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	_cancelButton = CreateWindowExA(
		0,
		"Button",
		"Cancel",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		310, 305, 80, 30,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	EditorWindow::PopulateObjectList(_list, _listBox);
}