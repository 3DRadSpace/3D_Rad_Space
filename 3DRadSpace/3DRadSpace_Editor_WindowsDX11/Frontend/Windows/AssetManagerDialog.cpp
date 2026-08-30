#include "AssetManagerDialog.hpp"
#include <Engine3DRadSpace/Logging/Exception.hpp>
#include <Engine3DRadSpace/Core/Tag.hpp>
#include <shlobj_core.h>
#include "../HelperFunctions.hpp"
#include <thread>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;

void SetWorkingDirectory();

INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AssetManagerDialog *assetManager = nullptr;
	switch(msg)
	{
		case WM_INITDIALOG:
		{
			assetManager = reinterpret_cast<AssetManagerDialog*>(lParam);
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
			switch(reinterpret_cast<LPNMHDR>(lParam)->code)
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
						ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
						ofn.hwndOwner = assetManager->window;
						ofn.hInstance = assetManager->hInstance;
						ofn.lpstrFilter = assetManager->_fileFilter;
						ofn.lpstrFile = filename;
						ofn.nMaxFile = _MAX_PATH;

						if (GetOpenFileNameA(&ofn))
						{
							SetWorkingDirectory();

							auto path = std::filesystem::path(filename);

							unsigned int ref = 0;
							IAsset* asset = nullptr;
							try
							{
								asset = assetManager->_content->Load(assetManager->_assetType, path, &ref);
							}
							catch (const Logging::Exception& ex)
							{
								MessageBoxA(assetManager->window, ex.what(), "Error loading asset", MB_ICONERROR | MB_OK);
							}

							if (asset && ref)
							{
								EndDialog(assetManager->window, ref);
							}
						}
						SetWorkingDirectory();
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

	RECT wndSize{};
	GetClientRect(window, &wndSize);

	_assetList = CreateWindowExA(
		0,
		"SysListView32",
		"",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		10,
		_assetListY,
		wndSize.right - wndSize.left - 20,
		wndSize.bottom - wndSize.top - _assetListY - 10,
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

			if (asset.Entry == nullptr) continue;
			//if (asset.RTTI.hash_code() != _assetType.hash_code()) continue;
			if (asset.Type != _assetType) continue;

			std::string imagePath;
			//Find %appdata%
			char appdataPath[_MAX_PATH] = {};
			
			HRESULT r;
			if (SUCCEEDED(r = SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appdataPath)))
			{
				if (!std::filesystem::exists(asset.Path))
				{
					throw Logging::Exception("Asset is not located in the executable root directory!");
				}

				auto exeDir = std::filesystem::path(GetExecutablePath());
				auto dataDir = exeDir / "Data";
				auto absAssetPath = std::filesystem::absolute(asset.Path);

				std::filesystem::path assetPath;
				auto relativeToData = absAssetPath.lexically_relative(dataDir);
				if (!relativeToData.empty() && relativeToData.native()[0] != '.')
					assetPath = relativeToData;
				else
					assetPath = absAssetPath.lexically_relative(exeDir);

				imagePath = appdataPath + (R"(\3DRadSpace\AssetImages\)" + assetPath.string()) + ".png";

				auto dirPath = std::filesystem::path(imagePath).remove_filename();

				create_directories(dirPath);
			}
			else return;

			if (!std::filesystem::exists(imagePath))
			{
				//TODO: Find a way to use UUIDs instead of RTTI.
				std::unordered_map<size_t, int> type_map =
				{
					{typeid(ModelAsset).hash_code(), 1},
					{typeid(TextureAsset).hash_code(), 2},
					{typeid(FontAsset).hash_code(), 3},
					{typeid(SkyboxAsset).hash_code(), 4}
				};

				switch (type_map[asset.RTTI.hash_code()])
				{
				case 1:
					if (_renderer) _renderer->RenderAsset<ModelAsset>(imagePath, asset.Path);
					break;
				case 2:
					if (_renderer) _renderer->RenderAsset<TextureAsset>(imagePath, asset.Path);
					break;
				case 3:
					if (_renderer) _renderer->RenderAsset<FontAsset>(imagePath, asset.Path);
					break;
				case 4:
					if (_renderer) _renderer->RenderAsset<SkyboxAsset>(imagePath, asset.Path);
					break;
				default:
					break;
				}
			}

			unsigned w, h;
			HBITMAP image = loadImageFromFile(imagePath, w, h);

			if (image == nullptr) //if failed to render and save an image, fall back to the default one.
				image = loadImageFromFile("Data//NoAsset.png", w, h);

			if (image == nullptr)
				throw Logging::Exception("default image not found!");

			//resize image to 64x64 using GDI
			HDC screenDC = GetDC(nullptr);
			HDC srcDC = CreateCompatibleDC(screenDC);
			HDC dstDC = CreateCompatibleDC(screenDC);
			HBITMAP resized = CreateCompatibleBitmap(screenDC, 64, 64);

			HGDIOBJ oldSrc = SelectObject(srcDC, image);
			HGDIOBJ oldDst = SelectObject(dstDC, resized);
			SetStretchBltMode(dstDC, HALFTONE);
			StretchBlt(dstDC, 0, 0, 64, 64, srcDC, 0, 0, w, h, SRCCOPY);

			SelectObject(srcDC, oldSrc);
			SelectObject(dstDC, oldDst);
			DeleteDC(srcDC);
			DeleteDC(dstDC);
			ReleaseDC(nullptr, screenDC);
			DeleteObject(image);

			int imgIdx = ImageList_AddMasked(_imageList, resized, RGB(255, 255, 255));
			DeleteObject(resized);

			LVITEMA item{};
			item.lParam = asset.ID;
			item.pszText = const_cast<char*>(asset.Name.c_str());
			item.cchTextMax = int(asset.Name.length());
			item.iImage = imgIdx;
			item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

			SendMessageA(_assetList, LVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&item)); //add item first, then load image next
		}
	});
	imageLoader.detach();
}

AssetManagerDialog::AssetManagerDialog(HWND owner, HINSTANCE instance, ContentManager *content) :
	Dialog(owner, instance, AssetManager_DlgProc, "Asset Manager"),
	_assetList(nullptr),
	_searchLabel(nullptr),
	_searchBox(nullptr),
	_browseButton(nullptr),
	_imageList(nullptr),
	_content(content),
	_assetType()
{
}

AssetManagerDialog::~AssetManagerDialog()
{
}