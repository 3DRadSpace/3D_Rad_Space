#pragma once
#include "../Controls/Dialog.hpp"
#include <Engine3DRadSpace/Plugins/PluginInfo.hpp>
#include <Engine3DRadSpace/Core/IGame.hpp>

class PluginsWindow : public Dialog
{
	HWND pluginsListBox;

	HWND pluginLabelName;
	HWND pluginLabelVersion;
	HWND pluginLabelAuthor;
	HWND pluginLabelDescription;
	HWND pluginPictureBox;

	HWND btnOK;

	Engine3DRadSpace::IGame* _game;

	void createForms();
	void onPluginSelected(int index);
public:
	PluginsWindow(HWND owner, HINSTANCE hInstance, Engine3DRadSpace::IGame* game);

	void ShowDialog();

	friend INT_PTR WINAPI PluginsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
