#pragma once
#include "IRenderer.hpp"
#include "../IDepthStencilBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ShadowMapRenderer : public IRenderer
	{
		std::unique_ptr<IDepthStencilBuffer> _shadowMap;
	public:
		ShadowMapRenderer(IGraphicsDevice* device);

		/// <summary>
		/// Defines the size of the shadow map as a multiplier of the screen resolution.
		/// </summary>
		float ShadowMapSize = 1.0f;

		float ShadowBias = 0.005f;
		float ShadowSlopeBias = 0.01f;

		Math::Matrix4x4 _lightViewMatrix;
		Math::Matrix4x4 _lightProjectionMatrix;

		void Begin() override;
		void End() override;

		~ShadowMapRenderer() override = default;
	};
}