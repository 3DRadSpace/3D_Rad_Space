#include "AddObjectDialog.hpp"
#include <Engine3DRadSpace/Error.hpp>
#include "resource.h"
#include <CommCtrl.h>
#include "EditObjectDialog.hpp"


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
			aod->createForms();
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
			aod->resize();
			return 1;
		}
		case WM_COMMAND:
		{
			return 1;
		}
		case WM_NOTIFY:
		{
			switch((reinterpret_cast<LPNMHDR>(lParam))->code)
			{
				case NM_DBLCLK:
				{
					LPNMITEMACTIVATE item = reinterpret_cast<LPNMITEMACTIVATE>(lParam);
					int nItems = (int)SendMessageA(aod->listView, LVM_GETITEMCOUNT, 0, 0);

					EditObjectDialog dialog(hwnd, aod->hInstance, &CameraReflInstance, nullptr);
					dialog.ShowDialog();
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
	Dialog(owner_window, instance, AddObjectDialog_DlgProc, "Add a object..."),
	imageList(nullptr),
	listView(nullptr)
{
}

Engine3DRadSpace::IObject* AddObjectDialog::ShowDialog()
{
	INT_PTR r = Dialog::ShowDialog(static_cast<void*>(this));
	if (r == IDOK)
	{
		return nullptr; //TODO: Create valid object.
	}
	else return nullptr;
}

void AddObjectDialog::createForms()
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
	std::vector<std::string> objectNames =
	{
		CameraReflInstance.Name
	};
	objectData =
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

	resize();
}

void AddObjectDialog::resize()
{
	RECT r;
	GetClientRect(window, &r);
	int cx = r.right - r.left;
	int cy = r.bottom - r.top;
	SetWindowPos(listView, nullptr, 0, 0, cx, cy, SW_NORMAL);
}

AddObjectDialog::~AddObjectDialog()
{
	if (imageList != nullptr)
	{
		ImageList_Destroy(imageList);
		imageList = nullptr;
	}
}
