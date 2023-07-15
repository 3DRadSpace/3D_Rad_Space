#include "AssetManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

AssetManager::AssetManager(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content) :
	Dialog(owner, instance, nullptr, "Asset Manager"),
	_assetList(nullptr),
	_searchBox(nullptr),
	_searchLabel(nullptr)
{
	HDC hdc = GetDC(owner);

	SIZE textSize{};
	GetTextExtentPoint32A(hdc, "Browse", 6, &textSize);

	_searchLabel = CreateWindowExA(
		0,
		"STATIC",
		"Browse",
		ES_LEFT | WS_VISIBLE | WS_CHILD,
		10,
		10,
		textSize.cx,
		textSize.cy,
		owner,
		nullptr,
		instance,
		nullptr
	);

	_searchBox = CreateWindowExA(
		0,
		"EDIT",
		"",
		ES_LEFT | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE,
		20 + textSize.cx,
		10,
		300,
		textSize.cy + 5,
		owner,
		nullptr,
		instance,
		nullptr
	);

	auto _assetListY = 20 + textSize.cy;

	_assetList = CreateWindowExA(
		0,
		"SysListView32",
		"",
		WS_VISIBLE | WS_CHILD,
		0,
		_assetListY,
		400,
		400 - _assetListY,
		owner,
		nullptr,
		instance,
		nullptr
	);

	_imageList = ImageList_Create(64, 64, ILC_HIGHQUALITYSCALE | ILC_COLOR, 50, 100);

	//iterate assets
	for(auto &asset : *content)
	{
		LVITEMA item{};
		item.lParam = asset->ID();
		item.pszText = const_cast<char *>(asset->Name.c_str());
		item.cchTextMax = asset->Name.length();
		item.iImage = asset->ID();
		item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

		std::thread image_loader(
			[](HIMAGELIST imageList, LVITEMA *item, HWND assetList, IAsset *asset)
		{
			if(imageList == nullptr) return;
			if(assetList == nullptr) return;

			std::string imagePath = std::string("AssetImages//") + asset->Path + ".png";

			if(!std::filesystem::exists(imagePath))
			{
				
			}

			unsigned w, h;
			HBITMAP image = loadImageFromFile(imagePath.c_str(), w, h);

			ImageList_Replace(imageList, asset->ID(), image, nullptr);
			DeleteObject(image);

			SendMessageA(assetList, LVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(item));
		}, 
		_imageList, &item, _assetList, asset.get());

		image_loader.detach();
	}
}

AssetManager::~AssetManager()
{
	if(_imageList != nullptr) ImageList_Destroy(_imageList);
}

INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
			return 1;
		case WM_CLOSE:
			EndDialog(hwnd, IDCANCEL);
			return 1;
		default: return 0;
	}
}
