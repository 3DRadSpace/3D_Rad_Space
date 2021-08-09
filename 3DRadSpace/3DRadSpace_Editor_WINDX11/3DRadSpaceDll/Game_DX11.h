#pragma once
#include <d3d11.h>
#include <Windows.h>
#pragma comment (lib,"d3d11.lib")

namespace RS_DX11
{
	class Game
	{
		ID3D11Device* _gdev;
		ID3D11DeviceContext* _gcontext;
		IDXGISwapChain* _swapchain;
		bool _dc;
	public:
		Game(HWND window);
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		IDXGISwapChain* GetSwapChain();
		bool IsDeviceCreated();
	};
}

