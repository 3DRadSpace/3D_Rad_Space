#pragma once
#include "Globals.hpp"
#include "Game.hpp"

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents the rendering bounds
	/// </summary>
	class DLLEXPORT Viewport
	{
	public:
		/// <summary>
		/// Creates a viewport with default settings.
		/// </summary>
		Viewport() : TopLeftX(0), TopLeftY(0), Width(800), Height(600), MinDepth(0), MaxDepth(1) {};
		/// <summary>
		/// Creates a viewport with settings from the given rendering instance
		/// </summary>
		/// <param name="game"></param>
		Viewport(Game* game) : TopLeftX(0), TopLeftY(0), Width(game->GetResolution().X), Height(game->GetResolution().Y), MinDepth(0), MaxDepth(1.0f) {};
		/// <summary>
		/// Creates a viewport from the give coordinates
		/// </summary>
		/// <param name="tlx">Top left X coordinate</param>
		/// <param name="tly">Top left Y coordinate</param>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		/// <param name="mind">Clip space minimum depth. Usually 0</param>
		/// <param name="maxd">Clip space maximum depth. Usually 1</param>
		Viewport(int tlx, int tly, int w, int h, float mind, float maxd) : TopLeftX(tlx), TopLeftY(tly), Width(w), Height(h), MinDepth(mind), MaxDepth(maxd) {};
		int TopLeftX;
		int TopLeftY;
		int Width;
		int Height;
		float MinDepth;
		float MaxDepth;

		/// <summary>
		/// Sets the viewport to the graphics API
		/// </summary>
		/// <param name="context">Low level graphics device handle</param>
		void SetViewport(ID3D11DeviceContext* context);
	};
}
#endif

