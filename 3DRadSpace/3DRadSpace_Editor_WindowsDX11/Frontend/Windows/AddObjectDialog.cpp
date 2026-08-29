#include "AddObjectDialog.hpp"
#include "..\..\resource.h"
#include <CommCtrl.h>
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#include <psapi.h>
#include <Engine3DRadSpace/Plugins/CustomObject.hpp>
#include "EditObject.hpp"
#include <Engine3DRadSpace/Logging/Exception.hpp>
#include <Engine3DRadSpace/Logging/Message.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

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

					if(item->iItem >= 0)
					{
						auto& list = Engine3DRadSpace::Internal::GetInternalObjectsList();
						Logging::PrintMessage(std::format("AddObj: e3drsp_internal_objects_list 0x{:x}", reinterpret_cast<uintptr_t>(list.data())));
						aod->Result = EditObject(hwnd, aod->hInstance, list[item->iItem], aod->_content);
						EndDialog(hwnd, IDOK);
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
	LVITEMA item{};

	item.pszText = const_cast<char*>(objectName.c_str());

	item.cchTextMax = int(objectName.length());
	item.iGroupId = groupIndex;
	item.iImage = imageIndex;
	item.iItem = itemIndex++;
	item.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_GROUPID;

	SendMessageA(listView, LVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&item));
}

AddObjectDialog::AddObjectDialog(HWND owner_window, HINSTANCE instance, Content::ContentManager* content):
	Dialog(owner_window, instance, AddObjectDialog_DlgProc, "Add a object..."),
	imageList(nullptr),
	listView(nullptr),
	_content(content)
{
}

IObject* AddObjectDialog::ShowDialog()
{
	auto r = Dialog::ShowDialog(static_cast<void *>(this));
	return r == IDOK ? static_cast<IObject*>(Result) : nullptr;
}

struct objectItem
{
	std::string image;
	int categoryID;
};

void AddObjectDialog::createForms()
{
	auto& Objects = Engine3DRadSpace::Internal::GetInternalObjectsList();

	//Create the list view control
	listView = CreateWindowExA(0, "SysListView32", "", WS_VISIBLE | WS_CHILD | LVS_ALIGNTOP, 0, 0, 800, 600, window, nullptr, hInstance, nullptr);
	if (listView == nullptr) throw Engine3DRadSpace::Logging::Exception("Failed to create a list view control!");
	SendMessageA(listView, LVM_ENABLEGROUPVIEW, true, 0);
	SendMessageA(listView, LVM_SETITEMCOUNT, Objects.size(), LVSICF_NOSCROLL);

	//Create the image list
	imageList = ImageList_Create(64, 64, ILC_COLOR32, 20, 5);
	if (imageList == nullptr) throw Engine3DRadSpace::Logging::Exception("Failed to create a image list!");

	//Assign the image list to the list view
	SendMessageA(listView, LVM_SETIMAGELIST, LVSIL_NORMAL, reinterpret_cast<LPARAM>(imageList));

	std::vector<std::pair<std::string, objectItem>> objects;
	std::unordered_map<std::string, int> categories;

	//populate the dictionaries
	int k = 1;
	for (size_t j = 0; j < Objects.size(); j++)
	{
		int categoryID = 0;

		if(categories.find(Objects[j]->Category) == categories.end())
		{
			categories[Objects[j]->Category] = k;
			categoryID = k;
			addCategory(Objects[j]->Category, categoryID);
			k++;
		}
		else
		{
			categoryID = categories[Objects[j]->Category];
		}

		std::string imagePath = "Data\\Editor\\OBJ_Empty.png";
		for (auto& field : *Objects[j])
		{
			if (auto attr = dynamic_cast<Attribute*>(field); attr != nullptr)
			{
				if (attr->FieldName() == "Icon")
				{
					imagePath = attr->FieldDesc();
					break;
				}
			}
		}

		objects.emplace_back(std::string(Objects[j]->Name), objectItem{imagePath, categoryID});
	}

	//Populate the image list with the object data (icons and names)
	for (auto& [name, obj] : objects)
	{
		unsigned w, h;
		HBITMAP img = loadImageFromFile(obj.image, w, h);
		int imgIndex = ImageList_Add(imageList, img, nullptr);
		DeleteObject(img);

		addObject(name, imgIndex, obj.categoryID);
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
}
