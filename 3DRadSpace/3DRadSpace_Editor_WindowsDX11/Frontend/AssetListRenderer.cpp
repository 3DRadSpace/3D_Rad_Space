#include "AssetListRenderer.hpp"

using namespace Engine3DRadSpace;

INT_PTR WINAPI AssetListRenderer_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

AssetListRenderer::AssetListRenderer(HWND owner, HINSTANCE instance, Content::ContentManager *content):
	_hInstance(instance)
{
	WNDCLASSA wndClass{};
	wndClass.lpfnWndProc = AssetListRenderer_WndProc;
	wndClass.lpszClassName = "AssetRendererWindow";
	wndClass.hInstance = instance;

	RegisterClassA(&wndClass);

	_renderWindow = CreateWindowExA(
		0,
		wndClass.lpszClassName,
		"Rendering assets...",
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		512,
		512,
		nullptr,
		nullptr,
		instance,
		nullptr
	);
	_device = std::make_unique<GraphicsDevice>(static_cast<void *>(_renderWindow), 512, 512);

	_device->Clear();
}

AssetListRenderer::~AssetListRenderer()
{
	DestroyWindow(_renderWindow);
	UnregisterClassA("AssetRendererWindow", _hInstance);
}
