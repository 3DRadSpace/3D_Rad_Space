#pragma once
#include <Engine3DRadSpace/Reflection/ReflectedField.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "Dialog.hpp"
#include <map>
#include "AssetListRenderer.hpp"

class AssetManager : public Dialog
{
	HWND _assetList;

	HWND _searchLabel;
	HWND _searchBox;
	HWND _browseButton;

	HIMAGELIST _imageList;

	std::map<int, HBITMAP> _imageDict;

	Engine3DRadSpace::Content::ContentManager *_content;
	std::unique_ptr<AssetListRenderer> _renderer;

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
		auto v = Dialog::ShowDialog(static_cast<void*>(this));
		return Engine3DRadSpace::Content::AssetReference<T>(static_cast<unsigned>(v));
	}

	~AssetManager();

	friend INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

