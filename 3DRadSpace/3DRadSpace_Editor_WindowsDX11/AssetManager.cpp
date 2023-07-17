#include "AssetManager.hpp"
#include "AssetListRenderer.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

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
		owner,
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
		owner,
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
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_imageList = ImageList_Create(64, 64, ILC_HIGHQUALITYSCALE | ILC_COLOR, 50, 100);

	//iterate assets
	for(auto &asset : *_content)
	{
		LVITEMA item{};
		item.lParam = asset->ID();
		item.pszText = const_cast<char *>(asset->Name.c_str());
		item.cchTextMax = int(asset->Name.length());
		item.iImage = asset->ID();
		item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

		SendMessageA(_assetList, LVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&item)); //add item first, then load image next

		AssetListRenderer renderer(owner, hInstance, _content);

		std::thread image_loader(
			[&renderer, &asset, this]()
		{
			if(_imageList == nullptr) return;
			if(_assetList == nullptr) return;

			std::string imagePath = std::string("AssetImages//") + asset->Path + ".png";

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
						renderer.RenderAsset<Engine3DRadSpace::Graphics::Model3D>(imagePath, asset->Path);
						break;
					case 2:
						renderer.RenderAsset<Engine3DRadSpace::Graphics::Texture2D>(imagePath, asset->Path);
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
		});

		image_loader.detach();
	}
}

AssetManager::AssetManager(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content) :
	Dialog(owner, instance, nullptr, "Asset Manager"),
	_assetList(nullptr),
	_searchBox(nullptr),
	_searchLabel(nullptr),
	_content(content),
	_imageList(nullptr)
{
}

AssetManager::~AssetManager()
{
	if(_imageList != nullptr) ImageList_Destroy(_imageList);
}

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
		case WM_CLOSE:
			EndDialog(hwnd, IDCANCEL);
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
						EndDialog(hwnd, item->lParam);
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
