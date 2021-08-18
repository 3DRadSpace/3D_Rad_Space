#pragma once
#include "Globals.h"

#ifdef __DIRECTXVER
#include <d3d11.h>
#include <Windows.h>
#pragma comment (lib,"d3d11.lib")

class __declspec(dllexport) Game
{
	ID3D11Device* _gdev;
	ID3D11DeviceContext* _gcontext;
	IDXGISwapChain* _swapchain;
	ID3D11RenderTargetView* _backbuffer_rendertarget;
	bool _dc;
public:
	Game(HWND window);
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	IDXGISwapChain* GetSwapChain();
	bool IsDeviceCreated();
	ID3D11RenderTargetView* GetRenderTargetBackBuffer();
	~Game();
};
#endif // __DIRECTXVER

