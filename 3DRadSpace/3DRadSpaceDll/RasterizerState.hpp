#pragma once
#include "Globals.hpp"

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents the fill mode of the rasterizer
	/// </summary>
	enum class RasterizerFillMode
	{
		FillWireframe = 2,
		FillSolid = 3
	};

	/// <summary>
	/// Represents the culling mode
	/// </summary>
	enum class RasterizerCullMode
	{
		None = 1,
		FrontFaces = 2,
		BackFaces = 3
	};

	/// <summary>
	/// Represents a description of the rasterizer.
	/// </summary>
	struct RasterizerStateDesc
	{
		/// <summary>
		/// Represents the fill mode.
		/// </summary>
		RasterizerFillMode FillMode;
		/// <summary>
		/// Represent the culling.
		/// </summary>
		RasterizerCullMode CullMode;
		int FrontCounterClockwise;
		int DepthBias;
		float DepthBiasClamp;
		float SlopeScaledDepthBias;
		int DepthClipEnable;
		int ScissorEnable;
		int MultisampleEnable;
		int AntialiasedLineEnable;
	};

	/// <summary>
	/// Represents a rasterizer state used by the graphics APIs.
	/// </summary>
	class DLLEXPORT RasterizerState
	{
		ID3D11RasterizerState* _rasterizerState;
	public:
		/// <summary>
		/// Creates an rasterizer state from the given handle with default values
		/// </summary>
		/// <param name="device">Graphics device handle</param>
		RasterizerState(ID3D11Device* device);

		/// <summary>
		/// Constructs a rasterizer state from the give graphics device handle and with custom values.
		/// </summary>
		/// <param name="device">Graphics device handle</param>
		/// <param name="desc">Rasterizer state description</param>
		RasterizerState(ID3D11Device* device, const RasterizerStateDesc& desc);

		/// <summary>
		/// Sets the rasterizer state
		/// </summary>
		/// <param name="context"></param>
		void SetRasterizerState(ID3D11DeviceContext* context);

		~RasterizerState();
	};
}
#endif

