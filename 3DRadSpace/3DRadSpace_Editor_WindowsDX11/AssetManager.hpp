#pragma once
#include <Engine3DRadSpace/Reflection/ReflectedField.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "Dialog.hpp"

class AssetManager : public Dialog
{
	HWND _assetList;

	HWND _searchLabel;
	HWND _searchBox;

	HIMAGELIST _imageList;
public:
	AssetManager(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content);

	AssetManager(AssetManager &) = delete;
	AssetManager(AssetManager &&) = delete;

	AssetManager &operator=(AssetManager &) = delete;
	AssetManager &operator=(AssetManager &&) = delete;

	friend INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	~AssetManager();
};

