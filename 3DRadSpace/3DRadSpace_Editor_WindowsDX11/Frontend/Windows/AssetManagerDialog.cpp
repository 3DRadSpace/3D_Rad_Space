#include "AssetManagerDialog.hpp"
#include <Engine3DRadSpace/Logging/Exception.hpp>
#include <Engine3DRadSpace/Tag.hpp>
#include <shlobj_core.h>
#include "../HelperFunctions.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;


INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AssetManagerDialog *assetManager = nullptr;
	switch(msg)
	{
		case WM_INITDIALOG:
		{
			assetManager = reinterpret_cast<AssetManagerDialog *>(lParam);
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
					auto item = reinterpret_cast<LPNMITEMACTIVATE>(lParam);

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
		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case BN_CLICKED:
				{
					if(lParam == reinterpret_cast<LPARAM>(assetManager->_browseButton))
					{
						char filename[_MAX_PATH] = {0};

						OPENFILENAMEA ofn{};
						ofn.lStructSize = sizeof(OPENFILENAMEA);
						ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
						ofn.hwndOwner = assetManager->window;
						ofn.hInstance = assetManager->hInstance;
						ofn.lpstrFile = filename;
						ofn.nMaxFile = _MAX_PATH;

						if(GetOpenFileNameA(&ofn))
						{
							auto path = std::filesystem::path(filename);
							auto relativePath = path.relative_path();

							auto tryLoadAsset = []<AssetType T>(Tag<T> dummy,ContentManager * content, const char *file, HWND current_window) -> std::optional<std::string>
							{
								try
								{
									AssetReference<T> ref;
									content->Load<T>(file, &ref);
									EndDialog(current_window, ref.ID);
									return std::nullopt;
								}
								catch(std::exception &e)
								{
									return std::string(e.what());
								}
								catch(Logging::Exception &e)
								{
									return e.What();
								}
							};

							std::string possibleErr;

							std::unordered_map<std::type_index, int> typemap =
							{
								{ typeid(Graphics::Texture2D), 1},
								{ typeid(Graphics::Model3D), 2}
							};

							std::optional<std::string> p;
							switch (typemap[assetManager->_assetType])
							{
							case 1:
								p = tryLoadAsset(Tag<Graphics::Texture2D>{}, assetManager->_content, filename, hwnd);
								break;
							case 2:
								p = tryLoadAsset(Tag<Graphics::Model3D>{}, assetManager->_content, filename, hwnd);
								break;
							default:
								break;
							}
							if(p.has_value()) possibleErr = p.value();
							else return 1;
						}
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

void AssetManagerDialog::_createForms()
{
	HDC hdc = GetDC(owner);

	SIZE textSize{};
	GetTextExtentPoint32A(hdc, "Find", 4, &textSize);

	//create controls
	_searchLabel = CreateWindowExA(
		0,
		"STATIC",
		"Find",
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

	SIZE browseTextSize;
	GetTextExtentPoint32A(hdc, "Browse...", 8, &browseTextSize);

	_browseButton = CreateWindowExA(
		0,
		"BUTTON",
		"Browse...",
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		350 + textSize.cx,
		10,
		browseTextSize.cx + 10,
		browseTextSize.cy + 5,
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

	_renderer = std::make_unique<AssetListRenderer>(owner, hInstance, _content);

	_loadAssetIcons();
}

void AssetManagerDialog::_loadAssetIcons()
{
	auto imageLoader = std::thread([this]()
	{
		for (auto& asset : *_content)
		{
			if (_imageList == nullptr) return;
			if (_assetList == nullptr) return;

			if (asset == nullptr) continue;
			if (asset->Type.hash_code() != _assetType.hash_code()) continue;

			std::string imagePath;
			//Find %appdata%
			char appdataPath[_MAX_PATH] = {};
			HRESULT r;

			if (SUCCEEDED(r = SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appdataPath)))
			{
				auto assetPath = std::filesystem::path(asset->Path);
				if (!std::filesystem::exists(asset->Path))
				{
					assetPath = std::filesystem::path(asset->Path).lexically_relative(GetExecutablePath());
					if (assetPath.empty())
					{
						throw std::exception("Asset is not located in the executable root directory!");
					}
				}

				imagePath = appdataPath + (R"(\3DRadSpace\AssetImages\)" + assetPath.string()) + ".png";

				auto dirPath = std::filesystem::path(imagePath).remove_filename().lexically_relative(GetExecutablePath());
				if (dirPath.empty()) dirPath = std::filesystem::path(imagePath).remove_filename();

				std::filesystem::create_directories(dirPath);
			}
			else throw std::filesystem::filesystem_error("Cannot find the AppData folder", std::error_code(r, std::system_category()));

			if (!std::filesystem::exists(imagePath))
			{
				std::unordered_map<size_t, int> type_map =
				{
					{typeid(Graphics::Model3D).hash_code(), 1},
					{typeid(Graphics::Texture2D).hash_code(), 2},
				};

				switch (type_map[asset->Type.hash_code()])
				{
				case 1:
					if (_renderer) _renderer->RenderAsset<Graphics::Model3D>(imagePath, asset->Path);
					break;
				case 2:
					if (_renderer) _renderer->RenderAsset<Graphics::Texture2D>(imagePath, asset->Path);
					break;
				default:
					break;
				}
			}

			unsigned w, h;
			HBITMAP image = loadImageFromFile(imagePath.c_str(), w, h);

			if (image == nullptr) //if failed to render and save an image, fall back to the default one.
				image = loadImageFromFile("Data//NoAsset.png", w, h);

			if (image == nullptr)
				throw std::exception("default image not found!");

			ImageList_Add(_imageList, image, nullptr);
			DeleteObject(image);

			LVITEMA item{};
			item.lParam = asset->ID();
			item.pszText = const_cast<char*>(asset->Name.c_str());
			item.cchTextMax = int(asset->Name.length());
			item.iImage = int(asset->ID() - 1);
			item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

			SendMessageA(_assetList, LVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&item)); //add item first, then load image next
		}
	});
	imageLoader.detach();
}

AssetManagerDialog::AssetManagerDialog(HWND owner, HINSTANCE instance, ContentManager *content) :
	Dialog(owner, instance, AssetManager_DlgProc, "Asset Manager"),
	_assetList(nullptr),
	_searchBox(nullptr),
	_searchLabel(nullptr),
	_content(content),
	_imageList(nullptr),
	_browseButton(nullptr),
	_assetType(typeid(void))
{
}

AssetManagerDialog::~AssetManagerDialog()
{
	if(_imageList != nullptr)
	{
		ImageList_Destroy(_imageList);
		_imageList = nullptr;
	}
}