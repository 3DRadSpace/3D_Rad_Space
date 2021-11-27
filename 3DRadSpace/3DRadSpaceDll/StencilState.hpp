#pragma once
#include "Globals.hpp"
#include "Game.hpp"

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
	class DLLEXPORT Game; //:pain:

	/// <summary>
	/// Represents a stencil state
	/// </summary>
	class DLLEXPORT StencilState
	{
		ID3D11Texture2D* _stenciltexture;
		ID3D11DepthStencilState* _stencilstate;
		ID3D11DepthStencilView* _stencilview;
		//ID3D11RenderTargetView* _rendertarget;
	public:
		/// <summary>
		/// Constructs a stencil state from the device handles with default values.
		/// </summary>
		/// <param name="g">Device handles</param>
		StencilState(Game* g);

		/// <summary>
		/// Returns the stencil texture
		/// </summary>
		/// <returns></returns>
		ID3D11DepthStencilView* GetStencilView();
		/// <summary>
		/// Returns the stencil state
		/// </summary>
		/// <returns></returns>
		ID3D11DepthStencilState* GetStencilState();

		~StencilState();
	};
}
#endif // __DIRECTXVER