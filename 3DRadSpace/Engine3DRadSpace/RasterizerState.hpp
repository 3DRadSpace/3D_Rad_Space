#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	enum class RasterizerFillMode
	{
		/// <summary>
		/// Triangles will be drawn in wireframe.
		/// </summary>
		Wireframe = 2,
		/// <summary>
		/// Triangles will be fully drawn.
		/// </summary>
		Solid = 3
	};

	enum class RasterizerCullMode
	{
		/// <summary>
		/// Always draw all triangles.
		/// </summary>
		None = 0,
		/// <summary>
		/// Do not draw font-facing trangles.
		/// </summary>
		CullFront = 1,
		/// <summary>
		/// Do not draw backfaces.
		/// </summary>
		CullBack = 2,
	};

	class GraphicsDevice;
	class RasterizerState
	{
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	public:

		RasterizerState(
			GraphicsDevice* device,
			RasterizerFillMode filling = RasterizerFillMode::Solid,
			RasterizerCullMode culling = RasterizerCullMode::CullBack,
			bool switchFrontBack = false,
			int depthBias = 0,
			float depthBiasClamp = 0,
			float slopeScaleDepthBias = 0,
			bool depthClip = false,
			bool scissor = false,
			bool multisample = false,
			bool aaLine = false
		);

		friend class GraphicsDevice;
	};
}