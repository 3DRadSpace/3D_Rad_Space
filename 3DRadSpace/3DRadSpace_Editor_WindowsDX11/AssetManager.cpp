#include "AssetManager.hpp"

AssetManager::AssetManager(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager &content) :
	Dialog(owner, instance, nullptr, "Asset Manager"),
	_treeView(nullptr),
	_browseAssetButton(nullptr),
	_searchBox(nullptr),
	_searchButton(nullptr)
{
	//iterate assets
	for(auto &asset : content)
	{

	}
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
