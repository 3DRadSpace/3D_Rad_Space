#include "ShadowMapRenderer.hpp"
#include "../../Core/IGame.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../ShaderDesc.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Vector3.hpp"
#include "../../Games/Game.hpp"
#include "../IShaderCompiler.hpp"
#include "RenderingManager.hpp"
#include "../../Objects/CameraProvider.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

ShadowMapRenderer::ShadowMapRenderer(RenderingManager* owner) : IRenderer(owner)
{
	auto resolution = _device->Resolution();
	unsigned int shadowMapWidth = static_cast<unsigned int>(resolution.X * ShadowMapSize);
	unsigned int shadowMapHeight = static_cast<unsigned int>(resolution.Y * ShadowMapSize);

	_shadowMap = _device->CreateDepthStencilBuffer(shadowMapWidth, shadowMapHeight);
	_createShadowStates();
	_loadEffect();
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

	_shadowDepthState = _device->CreateDepthStencilState_DepthDefault();
	_shadowSampler = _device->CreateSamplerState_LinearClamp();
}

void ShadowMapRenderer::_loadEffect()
{
	auto compiler = _device->ShaderCompiler();

	ShaderDescFile vsShadowEffect(
		"Data\\Shaders\\ShadowMapDepth.hlsl",
		"VS_Main",
		ShaderType::Vertex
	);

	ShaderDescFile psShadowEffect(
		"Data\\Shaders\\ShadowMapDepth.hlsl",
		"PS_Main",
		ShaderType::Fragment
	);

	ShaderDesc* descs[2] = {&vsShadowEffect, &psShadowEffect};
	auto result = compiler->CompileEffect(descs);

	if (result.second.Succeded)
	{
		_shadowMapEffect = result.first;
	}
	else
	{
		throw Logging::Exception("Failed to compile shadow map effect: " + result.second.Log);
	}
}

namespace
{
	// Distance the light is offset from the camera frustum center along the light direction.
	constexpr float LightOffsetDistance = 100.0f;
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightViewMatrix(const Math::Vector3& lightDirection)
{
	// For a directional light, position it far along the light direction
	// from the center of the camera's viewing frustum
	Math::Vector3 target = Math::Vector3::Zero();

	auto camera = _owner->GetOwner()->RequireService<Objects::CameraProvider>({})->GetActiveCamera();
	if (camera)
	{
		auto corners = camera->GetViewingFrustum().Corners();
		Math::Vector3 center = Math::Vector3::Zero();
		for (auto& corner : corners)
		{
			center += corner;
		}
		target = center / static_cast<float>(corners.size());
	}

	Math::Vector3 lightPos = target - lightDirection * LightOffsetDistance; // Position light far away
	Math::Vector3 up = Math::Vector3(0.0f, 1.0f, 0.0f);

	// Adjust up vector if light direction is parallel to it
	if (std::abs(Vector3::Dot(lightDirection, up)) > 0.99f)
	{
		up = Math::Vector3(1.0f, 0.0f, 0.0f);
	}

	return Math::Matrix4x4::CreateLookAtView(lightPos, target, up);
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightProjectionMatrix(const Math::Point& screenSize)
{
	// Size the orthographic projection to encompass the camera's viewing frustum
	float radius = 500.0f;

	auto camera = _owner->GetOwner()->RequireService<Objects::CameraProvider>({})->GetActiveCamera();
	if (camera)
	{
		auto corners = camera->GetViewingFrustum().Corners();
		Math::Vector3 center = Math::Vector3::Zero();
		for (auto& corner : corners)
		{
			center += corner;
		}
		center = center / static_cast<float>(corners.size());

		radius = 0.0f;
		for (auto& corner : corners)
		{
			float distance = (corner - center).Length();
			if (distance > radius)
			{
				radius = distance;
			}
		}
	}

	Math::Point size(screenSize.X, screenSize.Y);
	if (radius > 0.0f)
	{
		int diameter = static_cast<int>(radius * 2.0f);
		size = Math::Point(diameter, diameter);
	}

	// Near/far planes must bracket the bounding sphere of the camera frustum as seen from the
	// light's position (offset from the frustum center by LightOffsetDistance). Without this,
	// geometry closer to the light than the near plane gets clipped.
	float nearPlane = radius > 0.0f ? std::max(0.1f, LightOffsetDistance - radius) : 1.0f;
	float farPlane = radius > 0.0f ? LightOffsetDistance + radius : 1000.0f;

	return Math::Matrix4x4::CreateOrthographicProjection(size, nearPlane, farPlane);
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
	// Restore default viewport (screen resolution)
	auto resolution = _device->Resolution();
	Viewport defaultViewport(
		Math::RectangleF(0.0f, 0.0f, static_cast<float>(resolution.X), static_cast<float>(resolution.Y)),
		0.0f,
		1.0f
	);
	_context->SetViewport(defaultViewport);

	// Unbind the shadow map depth buffer
	_context->UnbindDepthBuffer();
}

IDepthStencilBuffer* ShadowMapRenderer::GetShadowMap() const noexcept
{
	return _shadowMap.get();
}

ISamplerState* ShadowMapRenderer::GetShadowSampler() const noexcept
{
	return _shadowSampler.get();
}

void ShadowMapRenderer::Draw(ModelMeshPart* part, const MaterialDescriptor* materialDescriptor)
{
	if (!part) return;
	if (materialDescriptor && !materialDescriptor->HasShadows) return;

	_shadowMapEffect->SetAll();
	
	auto lvp = ComputeLightViewMatrix(_owner->MainLight.LightDirection) * ComputeLightProjectionMatrix(_device->Resolution());

	_shadowMapEffect->SetData<Math::Matrix4x4>(&lvp, 0);

	_context->SetTopology(VertexTopology::TriangleList);
	_context->DrawVertexBufferWithindices(
		part->GetVertexBuffer(),
		part->GetIndexBuffer()
	);
}

bool ShadowMapRenderer::IsRenderPassTypeSupported(RenderPassType passType) const noexcept
{
	switch (passType)
	{
	case RenderPassType::Opaque:
	case RenderPassType::Transparent:
	case RenderPassType::ShadowMap:
	case RenderPassType::DepthPrePass:
		return true;
	default:
		return false;
	}
}