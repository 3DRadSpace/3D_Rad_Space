#pragma once
#include "Globals.h"
#include "Point.h"
#include "Color.h"

enum class PrimitiveTopology
{
	Points,
	Lines,
	TriangleStrip,
	TriangleList,
};

#ifdef __DIRECTXVER
#include <d3d11.h>
#pragma comment (lib,"d3d11.lib")

#include "StencilState.h"

class DLLEXPORT StencilState;

typedef void (__cdecl *Game_LostDeviceEvent)();

class DLLEXPORT Game
{
	ID3D11Device* _gdev;
	ID3D11DeviceContext* _gcontext;
	IDXGISwapChain* _swapchain;
	ID3D11RenderTargetView* _backbuffer_rendertarget;
	bool _dc;
	Point _resolution;

	StencilState* _stencilstate;
	
	HWND hWindow;
public:
	Game(HWND window);
	Game(HWND window,const Point &resolution);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	IDXGISwapChain* GetSwapChain();

	Game_LostDeviceEvent LostDeviceEvent;

	bool IsDeviceCreated();
	ID3D11RenderTargetView* GetRenderTargetBackBuffer();

	Point GetResolution();

	void SetTopology(PrimitiveTopology topology);
	void SetStencilState(StencilState *stencil);
	void Clear(ColorShader clearcolor);

	void Present();

	HWND GetWindow();

	~Game();
};
#endif // __DIRECTXVER

