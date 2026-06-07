#include "ShadowMapRenderer.hpp"
#include "../../Core/IGame.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../ShaderDesc.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Vector3.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

ShadowMapRenderer::ShadowMapRenderer(IGraphicsDevice* device, RenderingManager* owner) : IRenderer(device, owner)
{
	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	_shadowMap = _device->CreateDepthStencilBuffer(shadowMapWidth, shadowMapHeight);
	_createShadowStates();

	ShaderDescFile compositeDesc(
		"Data\\Shaders\\ShadowComposite.hlsl",
		"PS_Main",
		ShaderType::Fragment
	);
	_shadowCompositeEffect = std::make_unique<PostProcessEffect>(device, compositeDesc);
	_shadowCompositeEffect->NotDepthAware = false;
}

void ShadowMapRenderer::_createShadowStates()
{
	// Create rasterizer state with depth bias for shadow mapping
	_shadowRasterizerState = _device->CreateRasterizerState(
		RasterizerFillMode::Solid,
		RasterizerCullMode::CullBack,
		false, // frontCounterClockwise
		static_cast<int>(ShadowBias * 100000.0f), // depthBias (scaled)
		0.0f, // depthBiasClamp
		ShadowSlopeBias, // slopeScaledDepthBias
		true, // depthClip
		false, // scissor
		false, // multisample
		false  // antialiasedLine
	);

	// Create depth stencil state for shadow map rendering
	_shadowDepthState = _device->CreateDepthStencilState_DepthDefault();
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightViewMatrix(const Math::Vector3& lightDirection) const
{
	// Use the camera frustum center as the light look-at point
	// This requires access to the game's View matrix
	if (_owner == nullptr)
	{
		// Return identity if no owner
		return Math::Matrix4x4();
	}

	// For a directional light, position it far along the light direction
	// from the center of the camera frustum
	Math::Vector3 lightPos = lightDirection * -100.0f; // Position light far away
	Math::Vector3 target = Math::Vector3::Zero(); // Look at origin for now
	Math::Vector3 up = Math::Vector3(0.0f, 1.0f, 0.0f);

	// Adjust up vector if light direction is parallel to it
	if (std::abs(Vector3::Dot(lightDirection, up)) > 0.99f)
	{
		up = Math::Vector3(1.0f, 0.0f, 0.0f);
	}

	return Math::Matrix4x4::CreateLookAtView(lightPos, target, up);
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightProjectionMatrix() const
{
	// Use an orthographic projection for directional light shadows
	// The size should encompass the camera frustum
	if (_owner == nullptr)
	{
		// Return identity if no owner
		return Math::Matrix4x4();
	}

	// For now, use a fixed-size orthographic projection
	// In a full implementation, you would calculate this based on the camera frustum
	Math::Point size(_device->Resolution().X, _device->Resolution().Y);
	return Math::Matrix4x4::CreateOrthographicProjection(size, 1.0f, 1000.0f);
}

void ShadowMapRenderer::Begin()
{
	auto context = _device->ImmediateContext();

	// Calculate shadow map viewport on-demand
	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	Viewport shadowViewport(
		Math::RectangleF(0.0f, 0.0f, static_cast<float>(shadowMapWidth), static_cast<float>(shadowMapHeight)),
		0.0f,
		1.0f
	);

	// Clear and set the shadow map as the depth target
	context->UnbindRenderTargetAndDepth();
	context->SetDepthStencilBuffer(_shadowMap.get());
	context->ClearDepthBuffer(_shadowMap.get());

	// Set shadow viewport
	context->SetViewport(shadowViewport);

	// Set shadow states
	context->SetRasterizerState(_shadowRasterizerState.get());
	context->SetDepthStencilState(_shadowDepthState.get(), 0);
}

void ShadowMapRenderer::_applyShadows(const Math::Matrix4x4& lightViewProj, const Math::Vector3& lightDir)
{
	if (_shadowCompositeEffect == nullptr || _owner == nullptr)
		return;

	// Set up shader constants
	struct ShadowCompositeData
	{
		Math::Matrix4x4 LightViewProj;
		Math::Matrix4x4 InvViewProj;
		Math::Vector3 LightDirection;
		float ShadowBias;
		float ShadowIntensity;
		Math::Vector3 Padding;
	} data;

	auto game = static_cast<Game*>(_owner->GetOwner());
	if (game == nullptr) return;

	data.LightViewProj = lightViewProj;
	data.InvViewProj = Math::Matrix4x4::Invert(game->View * game->Projection);
	data.LightDirection = lightDir;
	data.ShadowBias = ShadowBias;
	data.ShadowIntensity = ShadowIntensity;

	_shadowCompositeEffect->SetData(0, &data, sizeof(data));

	// Bind shadow map as additional texture (slot 2, since 0 and 1 are backbuffer and depth)
	_shadowCompositeEffect->SetTexture(2, _shadowMap->GetDepthTexture());

	// Apply the post-process effect (automatically copies backbuffer and depth, binds textures)
	_shadowCompositeEffect->Apply();
	_shadowCompositeEffect->Draw();
}

void ShadowMapRenderer::End()
{
	auto context = _device->ImmediateContext();

	// Restore default viewport (screen resolution)
	auto resolution = _device->Resolution();
	Viewport defaultViewport(
		Math::RectangleF(0.0f, 0.0f, static_cast<float>(resolution.X), static_cast<float>(resolution.Y)),
		0.0f,
		1.0f
	);
	context->SetViewport(defaultViewport);

	// Unbind the shadow map depth buffer
	context->UnbindDepthBuffer();

	// Apply shadows as a screen-space composite
	// This requires the light view-projection matrix
	Math::Matrix4x4 lightViewProj = ComputeLightViewMatrix(LightDirection) * ComputeLightProjectionMatrix();
	_applyShadows(lightViewProj, LightDirection);
}

IDepthStencilBuffer* ShadowMapRenderer::GetShadowMap() const noexcept
{
	return _shadowMap.get();
}

void ShadowMapRenderer::Draw(ModelMeshPart* part, Effect* effect)
{
	_owner->Batcher.Draw(part, effect, RenderPassType::ShadowMap);
}