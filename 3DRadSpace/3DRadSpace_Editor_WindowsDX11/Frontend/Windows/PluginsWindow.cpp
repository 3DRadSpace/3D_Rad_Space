#include "PluginsWindow.hpp"
#include <Engine3DRadSpace/Plugins/PluginManager.hpp>

INT_PTR WINAPI PluginsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PluginsWindow* wndPlugins = nullptr;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			wndPlugins = reinterpret_cast<PluginsWindow*>(lParam);
			wndPlugins->window = hwnd;
			wndPlugins->createForms();
			return 1;
		}
		case WM_COMMAND:
			if(HIWORD(wParam) == LBN_SELCHANGE && reinterpret_cast<HWND>(lParam) == wndPlugins->pluginsListBox)
			{
				int sel = static_cast<int>(SendMessageA(wndPlugins->pluginsListBox, LB_GETCURSEL, 0, 0));
				if(sel != LB_ERR)
					wndPlugins->onPluginSelected(sel);
				return TRUE;
			}
			switch (LOWORD(wParam))
			{
			case IDOK:
				EndDialog(hwnd, IDOK);
				return TRUE;
			case IDCANCEL:
				EndDialog(hwnd, IDCANCEL);
				return TRUE;
			default:
				break;
			}
			if(HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == wndPlugins->btnOK)
			{
				EndDialog(hwnd, IDOK);
				return TRUE;
			}
			break;
		default:
			break;
	}
	return FALSE;
}

void PluginsWindow::createForms()
{
	pluginsListBox = CreateWindowExA(0,
		"ListBox",
		"",
		WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_BORDER,
		10, 10, 400, 400,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	auto pluginManager = _game->RequireService<Engine3DRadSpace::Plugins::PluginManager>({});
	for(const auto& plugin : *pluginManager)
	{
		SendMessageA(pluginsListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(plugin.Name));
	}

	pluginLabelName = CreateWindowExA(0,
		"Static",
		"Select a plugin from the list.",
		WS_VISIBLE | WS_CHILD,
		420, 10, 400, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginLabelVersion = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD,
		420, 40, 400, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginLabelAuthor = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD,
		420, 70, 400, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginLabelDescription = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD,
		420, 100, 400, 270,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginPictureBox = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP,
		420, 210, 200, 200,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	btnOK = CreateWindowExA(0,
		"Button",
		"OK",
		WS_VISIBLE | WS_CHILD,
		700, 380, 80, 30,
		window,
		nullptr,
		hInstance,
		nullptr
	);
}

void PluginsWindow::onPluginSelected(int index)
{
	auto pluginInfo = _game->RequireService<Engine3DRadSpace::Plugins::PluginManager>({})->GetPluginInfo(index);

	SetWindowTextA(pluginLabelName, std::format("Name: {}", pluginInfo.Name).c_str());
	SetWindowTextA(pluginLabelVersion, std::format("Version: {}", pluginInfo.Version).c_str());
	SetWindowTextA(pluginLabelAuthor, std::format("Author: {}", pluginInfo.Author).c_str());
	SetWindowTextA(pluginLabelDescription, std::format("Description: {}", pluginInfo.Description).c_str());
}

PluginsWindow::PluginsWindow(
	HWND owner,
	HINSTANCE hInstance,
	Engine3DRadSpace::IGame* game
) : Dialog(owner, hInstance, PluginsWindow_DlgProc, "Plugins", 400, 210), 
	_game(game)
{
}

void PluginsWindow::ShowDialog()
{
	Dialog::ShowDialog(static_cast<void*>(this));
}