#pragma once
#include "Globals.hpp"
#include "Point.hpp"
#include "Color.hpp"


/// <summary>
/// Defines the topology of the drawn vertex buffer
/// </summary>
enum class PrimitiveTopology
{
	/// <summary>
	/// A list of points
	/// </summary>
	Points,
	/// <summary>
	/// A list of lines
	/// </summary>
	Lines,
	/// <summary>
	/// A series of connected triangles from the triangle mesh
	/// </summary>
	TriangleStrip,
	/// <summary>
	/// A list of triangles.
	/// </summary>
	TriangleList,
};

#ifdef __DIRECTXVER
#include <d3d11.h>
#pragma comment (lib,"d3d11.lib")

#include "StencilState.hpp"

namespace Engine3DRadSpace
{

	class DLLEXPORT StencilState;

	/// <summary>
	/// Represents an event when the device handle is lost.
	/// </summary>
	typedef void(__cdecl* Game_LostDeviceEvent)();

	/// <summary>
	/// Represents the graphics handles. Allows interaction with the GPU by giving a list of commands like drawing buffers, swapping backbuffers, etc.
	/// </summary>
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
		/// <summary>
		/// Constructs a Game from the given window.
		/// </summary>
		/// <param name="window">Windows HWND window handle.</param>
		explicit Game(HWND window);
		/// <summary>
		/// Constructs a Game from the given window and resolution.
		/// </summary>
		/// <param name="window">Windows HWND window handle</param>
		/// <param name="resolution">The resolution of the back buffer.</param>
		Game(HWND window, const Point& resolution);

		/// <summary>
		/// Gets the graphics device. Used to initialize GPU resources like buffers, shaders, etc.
		/// </summary>
		/// <returns></returns>
		ID3D11Device* GetDevice();
		/// <summary>
		/// Gets the device context. Used for GPU commands/
		/// </summary>
		/// <returns></returns>
		ID3D11DeviceContext* GetDeviceContext();
		/// <summary>
		/// Gets the swap chain.
		/// </summary>
		/// <returns></returns>
		IDXGISwapChain* GetSwapChain();

		/// <summary>
		/// Gets called when the graphics device handle is lost.
		/// This happends when the GPU is physically disconnected or removed, when a rendering error occurs, when the graphics driver is being updated, 
		/// or when the computer switched from a high performance GPU to a integrated GPU.
		/// </summary>
		Game_LostDeviceEvent LostDeviceEvent;

		/// <summary>
		/// Returns true if the graphics device handles are successfully created.
		/// </summary>
		/// <returns></returns>
		bool IsDeviceCreated();
		/// <summary>
		/// Gets the render target back buffer.
		/// </summary>
		/// <returns></returns>
		ID3D11RenderTargetView* GetRenderTargetBackBuffer();

		/// <summary>
		/// Gets the resolution of the swap chain.
		/// </summary>
		/// <returns></returns>
		Point GetResolution();

		/// <summary>
		/// Sets the topology of the verticies that are going to be drawn.
		/// </summary>
		/// <param name="topology">The toplogy</param>
		void SetTopology(PrimitiveTopology topology);
		/// <summary>
		/// Sets the stencil state.
		/// </summary>
		/// <param name="stencil">stencil state</param>
		void SetStencilState(StencilState* stencil);
		/// <summary>
		/// Clears the backbuffer with a specified colour.
		/// </summary>
		/// <param name="clearcolor">Clear colour.</param>
		void Clear(Engine3DRadSpace::ColorShader clearcolor);

		/// <summary>
		/// Swaps the backbuffers, and makes the scene visible to the screen.
		/// </summary>
		void Present();

		/// <summary>
		/// Gets the handle to the window as a HWND.
		/// </summary>
		/// <returns></returns>
		HWND GetWindow();

		~Game();
	};
}
#endif // __DIRECTXVER

