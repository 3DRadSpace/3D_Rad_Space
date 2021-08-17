#pragma once
#include "Globals.h"
#include "Game.h"
#ifdef __DIRECTXVER
#include <d3d11.h>
#endif

#ifdef __DIRECTXVER
class DLLEXPORT StencilState
{
	ID3D11Texture2D* _stenciltexture;
	ID3D11DepthStencilState* _stencilstate;
	ID3D11DepthStencilView* _stencilview;
	ID3D11RenderTargetView* _rendertarget;
public:
	StencilState(Game* g, int width, int height);

	void SetStencilState(ID3D11DeviceContext* context);

	~StencilState();
};
#endif // __DIRECTXVER