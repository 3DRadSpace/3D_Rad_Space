#include "AddObjectDialog.hpp"
#include <Engine3DRadSpace/Error.hpp>
#include "resource.h"
#include <CommCtrl.h>

#include <Engine3DRadSpace/Reflection.hpp>

//Forward declarations of object reflection data
__REFL_DEF(Camera)

INT_PTR WINAPI AddObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AddObjectDialog* aod = nullptr;
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			aod = reinterpret_cast<AddObjectDialog*>(lParam);
			aod->window = hwnd;
			aod->CreateForms();
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
			aod->Resize();
			return 1;
		}
		case WM_COMMAND:
		{
			return 1;
		}
		default:
			return 0;
	}
}

void AddObjectDialog::addCategory(const std::string& category,int index)
{
	LVGROUP group{};
	group.cbSize = sizeof(LVGROUP);
	group.mask = LVGF_HEADER | LVGF_GROUPID;

	std::wstring str = ConvertToWideString(category).c_str();
	group.pszHeader = const_cast<wchar_t*>(str.c_str());
	group.cchHeader = int(str.length());
	group.iGroupId = index;

	ListView_InsertGroup(listView, index, &group);
}

void AddObjectDialog::addObject(const std::string& objectName, int imageIndex, int groupIndex)
{
	LVITEMW item{};

	std::wstring itemName = ConvertToWideString(objectName);
	item.pszText = const_cast<wchar_t*>(itemName.c_str());

	item.cchTextMax = int(itemName.size());
	item.iGroupId = groupIndex;
	item.iImage = imageIndex;
	item.iItem = itemIndex++;
	item.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_GROUPID;

	ListView_InsertItem(listView, &item);
}

AddObjectDialog::AddObjectDialog(HWND owner_window, HINSTANCE instance):
	hInstance(instance),
	owner(owner_window),
	imageList(nullptr),
	listView(nullptr),
	window(nullptr)
{
	//Allocate memory for the dialog box
	hGlobal = GlobalAlloc(GMEM_ZEROINIT, 512);
	if (hGlobal == nullptr) throw std::bad_alloc();

	//Fill the dialog template data.
	dialogTemplate = static_cast<LPDLGTEMPLATE>(GlobalLock(hGlobal));
	if (dialogTemplate == nullptr) throw std::bad_alloc();

	dialogTemplate->style = WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_SIZEBOX | DS_MODALFRAME | WS_SYSMENU | DS_CENTER;
	dialogTemplate->dwExtendedStyle = 0;
	dialogTemplate->cdit = 0;
	
	dialogTemplate->x = 0;
	dialogTemplate->y = 0;

	dialogTemplate->cx = 400;
	dialogTemplate->cy = 300;

	//After the dialog template, a title is expected.
	LPWORD pWord = reinterpret_cast<LPWORD>(dialogTemplate + 1);
	*pWord++ = 0; // No menu
	*pWord++ = 0; // Predefined dialog box class (by default)

	LPWSTR title = reinterpret_cast<LPWSTR>(pWord);
	int numChars = 1 + MultiByteToWideChar(CP_ACP, 0, "Add a object...", -1, title, 50);
	
	pWord += numChars;

	*pWord++ = 0; //No more creation data. Only a window is created. Controls are manually created using CreateWindowA/W.

	GlobalUnlock(hGlobal);
}

Engine3DRadSpace::IObject* AddObjectDialog::ShowDialog()
{
	INT_PTR r = DialogBoxIndirectParamW(hInstance, dialogTemplate, owner, AddObjectDialog_DlgProc, reinterpret_cast<LPARAM>(this));
	if (r == IDOK)
	{
		return nullptr; //TODO: Create valid object.
	}
	else return nullptr;
}

void AddObjectDialog::CreateForms()
{
	//Create the list view control
	listView = CreateWindowExA(0, "SysListView32", "", WS_VISIBLE | WS_CHILD | LVS_ALIGNTOP, 0, 0, 600, 600, window, nullptr, hInstance, nullptr);
	if (listView == nullptr) throw std::exception("Failed to create a list view control!");
	ListView_EnableGroupView(listView, true);

	//Create the image list
	imageList = ImageList_Create(64, 64, ILC_COLOR32, 20, 5);
	if (imageList == nullptr) throw std::exception("Failed to create a image list!");

	ListView_SetImageList(listView, imageList, LVSIL_NORMAL); //Assign the image list to the list view

	//create image list for default objects.
	std::unordered_map<std::string, LPCWSTR> objects; //creates a object name <-> image dictionary.
	
	std::unordered_map<std::string, int> categories; //Category - category ID map.

	//hardcoded list of already implemented objects.
	std::array<std::string, 25> objectNames =
	{
		CameraReflInstance.Name
	};
	std::vector<Engine3DRadSpace::Reflection::ReflectedObject*> objectData =
	{
		&CameraReflInstance
	};

	//populate the dictionaries
	for (int i = IDB_PNG1, j = 0, k =0 ; i <= IDB_PNG24 && j < objectData.size(); i++, j++)
	{
		objects[objectNames[j]] = MAKEINTRESOURCEW(i);
		
		if (objectData[j] == nullptr) break;
		auto f = categories.find(objectData[j]->Category);
		if (f == categories.end())
		{
			categories[objectData[j]->Category] = k;
			k++;
		}
	}

	//Populate the image list categories:
	for (auto& category : categories)
	{
		addCategory(category.first, category.second);
	}

	//Populate the image list with the object data (icons and names)
	for (auto& o : objects)
	{
		HBITMAP img = loadImgResource(o.second,L"PNG", static_cast<HMODULE>(hInstance));
		int imgIndex = ImageList_Add(imageList, img, nullptr);
		DeleteObject(img);

		addObject(o.first, imgIndex, categories[o.first]);
	}

	Resize();
}

void AddObjectDialog::Resize()
{
	RECT r;
	GetClientRect(window, &r);
	int cx = r.right - r.left;
	int cy = r.bottom - r.top;
	SetWindowPos(listView, nullptr, 0, 0, cx, cy, SW_NORMAL);
}

AddObjectDialog::~AddObjectDialog()
{
	if (hGlobal != nullptr) GlobalFree(hGlobal);
	hGlobal = nullptr;
	
	if (window != nullptr) DestroyWindow(window);
	window = nullptr;
}