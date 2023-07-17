#pragma once
#include <Engine3DRadSpace/Reflection/ReflectedField.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "Dialog.hpp"
#include <map>

class AssetManager : public Dialog
{
	HWND _assetList;

	HWND _searchLabel;
	HWND _searchBox;

	HIMAGELIST _imageList;

	std::map<int, HBITMAP> _imageDict;

	Engine3DRadSpace::Content::ContentManager *_content;

	void _createForms();
public:
	AssetManager(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content);

	AssetManager(AssetManager &) = delete;
	AssetManager(AssetManager &&) = delete;

	AssetManager &operator=(AssetManager &) = delete;
	AssetManager &operator=(AssetManager &&) = delete;

	template<Engine3DRadSpace::Content::AssetType T>
	Engine3DRadSpace::Content::AssetReference<T> ShowDialog()
	{
		Dialog::ShowDialog(static_cast<void*>(this));
	}

	~AssetManager();

	friend INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

