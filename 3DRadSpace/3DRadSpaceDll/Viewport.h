#pragma once
#include "Globals.h"
#include "Game.h"

#ifdef __DIRECTXVER

#include <d3d11.h>

class DLLEXPORT Viewport
{
public:
	Viewport() : TopLeftX(0), TopLeftY(0), Width(800), Height(600), MinDepth(0), MaxDepth(1) {};
	Viewport(Game* game) : TopLeftX(0), TopLeftY(0), Width(game->GetResolution().X), Height(game->GetResolution().Y), MinDepth(0), MaxDepth(1.0f) {};
	int TopLeftX;
	int TopLeftY;
	int Width;
	int Height;
	float MinDepth;
	float MaxDepth;

	void SetViewport(ID3D11DeviceContext* context);
};

#endif

