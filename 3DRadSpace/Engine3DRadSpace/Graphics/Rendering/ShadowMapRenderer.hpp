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
	class RenderingManager;
	class E3DRSP_GRAPHICS_RENDERING_EXPORT ShadowMapRenderer : public IRenderer
	{
		std::unique_ptr<IDepthStencilBuffer> _shadowMap;
		std::unique_ptr<ISamplerState> _shadowSampler;
		std::unique_ptr<IRasterizerState> _oldRasterizerState;
		std::unique_ptr<IRasterizerState> _shadowRasterizerState;
		std::unique_ptr<IDepthStencilState> _oldDepthStencilState;
		std::unique_ptr<IDepthStencilState> _shadowDepthState;
		Effect* _shadowMapEffect = nullptr;

		float _extent;

		void _determineExtent();
		void _createShadowStates();
		void _loadEffect();
	public:
		explicit ShadowMapRenderer(RenderingManager* owner);

		/// <summary>
		/// Defines the size of the shadow map as a multiplier of the screen resolution.
		/// </summary>
		float ShadowMapSize = 4.0f;

		float ShadowBias = 0.002f;
		float ShadowSlopeBias = 0.01f;

		/// <summary>
		/// Shadow intensity (0.0 = fully dark, 1.0 = no shadow)
		/// </summary>
		float ShadowIntensity = 0.3f;

		float NearPlane = 1.0f;
		float FarPlane = 1000.0f;

		/// <summary>
		/// Gets the shadow map depth texture.
		/// </summary>
		IDepthStencilBuffer* GetShadowMap() const noexcept;

		/// <summary>
		/// Gets the shadow texture sampler state.
		/// </summary>
		/// <returns>Shadow depth map sampler state</returns>
		ISamplerState* GetShadowSampler() const noexcept;

		/// <summary>
		/// Computes the light view matrix for shadow mapping. The light always looks at the world
		/// origin from a fixed distance along its direction, avoiding any camera-dependent state
		/// that would otherwise cause shadow shimmering/swimming.
		/// </summary>
		/// <param name="lightDirection">Direction of the light</param>
		/// <returns>Light view matrix</returns>
		Math::Matrix4x4 ComputeLightViewMatrix(const Math::Vector3& lightDirection) const;

		/// <summary>
		/// Computes the light projection matrix for shadow mapping. Uses a fixed world-space
		/// orthographic extent rather than fitting to the camera frustum.
		/// </summary>
		/// <returns>Light projection matrix</returns>
		Math::Matrix4x4 ComputeLightProjectionMatrix() const;

		void Begin() override;
		void Draw(ModelMeshPart* part, const MaterialDescriptor* materialDescriptor = nullptr) override;
		void End() override;
		bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept override;

		~ShadowMapRenderer() override = default;
	};
}