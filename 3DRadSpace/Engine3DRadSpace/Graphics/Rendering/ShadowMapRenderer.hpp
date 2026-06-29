#pragma once
#include "IRenderer.hpp"
#include "PostProcessEffect.hpp"
#include "../IDepthStencilBuffer.hpp"
#include "../IRasterizerState.hpp"
#include "../IDepthStencilState.hpp"
#include "../Viewport.hpp"
#include "../../Math/Matrix4x4.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ShadowMapRenderer : public IRenderer
	{
		std::unique_ptr<IDepthStencilBuffer> _shadowMap;
		std::unique_ptr<IRasterizerState> _shadowRasterizerState;
		std::unique_ptr<IDepthStencilState> _shadowDepthState;

		void _createShadowStates();
	public:
		ShadowMapRenderer(IGraphicsDevice* device);

		/// <summary>
		/// Defines the size of the shadow map as a multiplier of the screen resolution.
		/// </summary>
		float ShadowMapSize = 1.0f;

		float ShadowBias = 0.005f;
		float ShadowSlopeBias = 0.01f;

		/// <summary>
		/// Shadow intensity (0.0 = fully dark, 1.0 = no shadow)
		/// </summary>
		float ShadowIntensity = 0.3f;

		/// <summary>
		/// Light direction for shadow calculation (set before End())
		/// </summary>
		Math::Vector3 LightDirection = Math::Vector3(0.0f, -1.0f, 0.0f);

		/// <summary>
		/// Gets the shadow map depth texture.
		/// </summary>
		IDepthStencilBuffer* GetShadowMap() const noexcept;

		/// <summary>
		/// Computes the light view matrix for shadow mapping based on light direction and camera frustum.
		/// </summary>
		/// <param name="lightDirection">Direction of the light</param>
		/// <returns>Light view matrix</returns>
		Math::Matrix4x4 ComputeLightViewMatrix(const Math::Vector3& lightDirection) const;

		/// <summary>
		/// Computes the light projection matrix for shadow mapping based on camera frustum.
		/// </summary>
		/// <returns>Light projection matrix</returns>
		Math::Matrix4x4 ComputeLightProjectionMatrix() const;

		void Begin() override;
		void End() override;

		~ShadowMapRenderer() override = default;
	};
}