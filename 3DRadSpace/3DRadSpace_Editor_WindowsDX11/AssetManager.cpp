#include "AssetManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;


INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AssetManager *assetManager = nullptr;
	switch(msg)
	{
		case WM_INITDIALOG:
		{
			assetManager = reinterpret_cast<AssetManager *>(lParam);
			assetManager->window = hwnd;
			assetManager->_createForms();
			return 1;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
			EndPaint(hwnd, &ps);
			return 1;
		}
		case WM_CLOSE:
			EndDialog(hwnd, 0);
			return 1;
		case WM_NOTIFY:
		{
			switch((reinterpret_cast<LPNMHDR>(lParam))->code)
			{
				case NM_DBLCLK:
				{
					LPNMITEMACTIVATE item = reinterpret_cast<LPNMITEMACTIVATE>(lParam);

					if(item->iItem >= 0)
					{
						LVITEMA lvitem{};
						lvitem.iItem = item->iItem;
						lvitem.mask = LVIF_PARAM;
						SendMessageA(assetManager->_assetList, LVM_GETITEMA, 0, reinterpret_cast<LPARAM>(&lvitem));

						EndDialog(hwnd, lvitem.lParam);
						return 0;
					}
					break;
				}
				default:
					break;
			}
			return 1;
		}
		default: return 0;
	}
}

void AssetManager::_createForms()
{
	HDC hdc = GetDC(owner);

	SIZE textSize{};
	GetTextExtentPoint32A(hdc, "Browse", 6, &textSize);

	//create controls
	_searchLabel = CreateWindowExA(
		0,
		"STATIC",
		"Browse",
		ES_LEFT | WS_VISIBLE | WS_CHILD,
		10,
		10,
		textSize.cx,
		textSize.cy,
		window,
		nullptr,
		hInstance,
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
		window,
		nullptr,
		hInstance,
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
		window,
		nullptr,
		hInstance,
		nullptr
	);

	_imageList = ImageList_Create(64, 64, ILC_COLOR32 | ILC_MASK | ILC_ORIGINALSIZE, 50, 100);
	SendMessageA(_assetList, LVM_SETIMAGELIST, LVSIL_NORMAL, reinterpret_cast<LPARAM>(_imageList));

	//_renderer = std::make_unique<AssetListRenderer>(owner, hInstance, _content);

	//iterate assets
	for(auto &asset : *_content)
	{
		if(asset == nullptr) break;

		LVITEMA item{};
		item.lParam = asset->ID();
		item.pszText = const_cast<char *>(asset->Name.c_str());
		item.cchTextMax = int(asset->Name.length());
		item.iImage = asset->ID() - 1;
		item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

		SendMessageA(_assetList, LVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&item)); //add item first, then load image next
	}

	std::thread image_loader = std::thread([this]()
	{
		for(auto &asset : *_content)
		{
			if(_imageList == nullptr) return;
			if(_assetList == nullptr) return;

			std::string imagePath = std::string("Data//AssetImages//") + asset->Path + ".png";

			if(!std::filesystem::exists(imagePath))
			{
				std::unordered_map<size_t, int> type_map =
				{
					{typeid(Engine3DRadSpace::Graphics::Model3D).hash_code(), 1},
					{typeid(Engine3DRadSpace::Graphics::Texture2D).hash_code(), 2},
				};

				switch(type_map[asset->Type.hash_code()])
				{
					case 1:
						if(_renderer) _renderer->RenderAsset<Engine3DRadSpace::Graphics::Model3D>(imagePath, asset->Path);
						break;
					case 2:
						if(_renderer) _renderer->RenderAsset<Engine3DRadSpace::Graphics::Texture2D>(imagePath, asset->Path);
						break;
					default:
						break;
				}
			}

			unsigned w, h;
			HBITMAP image = loadImageFromFile(imagePath.c_str(), w, h);

			if(image == nullptr) //if failed to render and save an image, fall back to the default one.
				image = loadImageFromFile("Data//NoAsset.png", w, h);

			if(image == nullptr)
				throw std::exception("default image not found!");

			ImageList_Add(_imageList, image, nullptr);
			DeleteObject(image);
		}
	});
	image_loader.detach();
}

AssetManager::AssetManager(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content) :
	Dialog(owner, instance, AssetManager_DlgProc, "Asset Manager"),
	_assetList(nullptr),
	_searchBox(nullptr),
	_searchLabel(nullptr),
	_content(content),
	_imageList(nullptr)
{
}

AssetManager::~AssetManager()
{
	if(_imageList != nullptr)
	{
		ImageList_Destroy(_imageList);
		_imageList = nullptr;
	}
}