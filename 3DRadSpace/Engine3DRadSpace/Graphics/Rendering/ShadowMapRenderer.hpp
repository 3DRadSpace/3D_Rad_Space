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
		std::unique_ptr<IRasterizerState> _shadowRasterizerState;
		std::unique_ptr<IDepthStencilState> _shadowDepthState;
		Effect* _shadowMapEffect = nullptr;

		void _createShadowStates();
		void _loadEffect();
	public:
		explicit ShadowMapRenderer(RenderingManager* owner);

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
		/// Gets the shadow map depth texture.
		/// </summary>
		IDepthStencilBuffer* GetShadowMap() const noexcept;

		/// <summary>
		/// Computes the light view matrix for shadow mapping based on light direction and camera frustum.
		/// </summary>
		/// <param name="lightDirection">Direction of the light</param>
		/// <returns>Light view matrix</returns>
		static Math::Matrix4x4 ComputeLightViewMatrix(const Math::Vector3& lightDirection);

		/// <summary>
		/// Computes the light projection matrix for shadow mapping based on camera frustum.
		/// </summary>
		/// <returns>Light projection matrix</returns>
		static Math::Matrix4x4 ComputeLightProjectionMatrix(const Math::Point& screenSize);

		void Begin() override;
		void Draw(ModelMeshPart* part, const MaterialDescriptor* materialDescriptor = nullptr) override;
		void End() override;
		bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept override;

		~ShadowMapRenderer() override = default;
	};
}