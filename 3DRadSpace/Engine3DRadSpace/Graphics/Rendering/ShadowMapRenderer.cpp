#include "ShadowMapRenderer.hpp"
#include "../../Core/IGame.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../ShaderDesc.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/MVP.hpp"
#include "../../Games/Game.hpp"
#include "../../Objects/ObjectList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

ShadowMapRenderer::ShadowMapRenderer(IGraphicsDevice* device) : IRenderPass(device)
{
	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	_shadowMap = _device->CreateDepthStencilBuffer(shadowMapWidth, shadowMapHeight);
	_createShadowStates();
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

	// Get the camera from the ObjectList service
	auto objectList = _owner->RequireService<Objects::ObjectList>({});
	auto camera = objectList->GetRenderingCamera();

	if (camera == nullptr)
	{
		return Math::Matrix4x4();
	}

	Math::Matrix4x4 viewMatrix = camera->GetViewMatrix();

	// The camera position is the translation component of the inverse view matrix
	Math::Matrix4x4 invViewMatrix = Math::Matrix4x4::Invert(viewMatrix);
	Math::Vector3 cameraPos(invViewMatrix.M41, invViewMatrix.M42, invViewMatrix.M43);

	Math::Vector3 lightPos = cameraPos + (lightDirection * -100.0f); // Position light far away
	Math::Vector3 target = cameraPos; // Look at camera position
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

void ShadowMapRenderer::End()
{
	auto context = _device->ImmediateContext();

	context->SetViewport();
	context->UnbindDepthBuffer();
}

IDepthStencilBuffer* ShadowMapRenderer::GetShadowMap() const noexcept
{
	return _shadowMap.get();
}

void ShadowMapRenderer::Draw(DrawCall* drawCall)
{
	if (!drawCall || !drawCall->MeshPart)
		return;

	auto material = drawCall->MeshPart->GetShaders();

	if (!drawCall->MeshPart || !material)
		return;

	auto context = _device->ImmediateContext();
	material->SetAll();
	
	if (!drawCall->IsInstanced)
	{
		for (auto idxInstance = 0; idxInstance < drawCall->InstanceWorlds.size(); ++idxInstance)
		{
			Math::MVP lvp
			{
				.World = drawCall->InstanceWorlds[idxInstance],
				.View = ComputeLightViewMatrix(LightDirection),
				.Projection = ComputeLightProjectionMatrix()
			};
			material->SetData<Math::MVP>(&lvp, 0);
			context->DrawVertexBufferWithindices(drawCall->MeshPart->VertexBuffer.get(), drawCall->MeshPart->IndexBuffer.get());
		}
	}
}