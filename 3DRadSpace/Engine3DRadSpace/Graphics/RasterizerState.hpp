#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace
{
	class GraphicsDevice;
	namespace Graphics
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
			None = 1,
			/// <summary>
			/// Do not draw font-facing trangles.
			/// </summary>
			CullFront = 2,
			/// <summary>
			/// Do not draw backfaces.
			/// </summary>
			CullBack = 3,
		};


		class DLLEXPORT RasterizerState
		{
			Microsoft::WRL::ComPtr<ID3D11RasterizerState> _rasterizerState;
		public:

			explicit RasterizerState(
				GraphicsDevice *device,
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

			RasterizerState(RasterizerState &) = delete;
			RasterizerState(RasterizerState &&state) noexcept = default;

			RasterizerState &operator =(RasterizerState &) = delete;
			RasterizerState &operator =(RasterizerState &&state) noexcept = default;

			static RasterizerState CullNone(GraphicsDevice *device);
			static RasterizerState CullClockwise(GraphicsDevice *device);
			static RasterizerState CullCounterClockwise(GraphicsDevice *device);
			static RasterizerState Wireframe(GraphicsDevice *device);

			~RasterizerState() = default;

			friend class GraphicsDevice;
		};
	}
}