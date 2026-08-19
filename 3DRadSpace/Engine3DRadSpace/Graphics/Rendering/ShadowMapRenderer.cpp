#include "ShadowMapRenderer.hpp"
#include "../../Core/IGame.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../ShaderDesc.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Vector3.hpp"
#include "../../Games/Game.hpp"
#include "../IShaderCompiler.hpp"
#include "RenderingManager.hpp"
#include "../../Objects/ObjectList.hpp"

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
		RasterizerCullMode::None,
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

void ShadowMapRenderer::_determineExtent()
{
	auto objList = _owner->GetOwner()->RequireService<Objects::ObjectList>({});
	auto sceneBBox = objList->GetBoundingBox();

	auto sceneExtend = BoundingSphere(sceneBBox).Radius * 2.0f;
	_extent = std::max(1.0f, std::min(sceneExtend, FarPlane));
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightViewMatrix(const Math::Vector3& lightDirection) const
{
	Vector3 dir = lightDirection;
	float len = std::sqrt(Vector3::Dot(dir, dir));
	if (len > 0.0001f) dir = dir * (1.0f / len);
	else dir = Vector3(0.0f, -1.0f, 0.0f);

	auto cam = dynamic_cast<Objects::IObject3D*>(_owner->GetOwner()->RequireService<Objects::CameraProvider>({})->GetActiveCamera());

	Vector3 target = cam != nullptr ? cam->Position : Vector3::Zero();

	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	// Avoid a degenerate basis when the light points straight up/down.
	if (std::abs(Vector3::Dot(dir, up)) > 0.99f)
		up = Vector3(1.0f, 0.0f, 0.0f);

	// Build a stable light-space basis: right/up are perpendicular to the light direction, so the
	// shadow map's texel grid is aligned with the light's own view axes rather than world axes.
	Vector3 right = Vector3::Cross(up, dir);
	float rightLen = std::sqrt(Vector3::Dot(right, right));
	right = right * (1.0f / rightLen);
	Vector3 actualUp = Vector3::Cross(dir, right);

	// Snap the camera-follow target to whole-texel increments along the light's right/up axes.
	// Snapping must happen in this basis (not world X/Y/Z), otherwise the shadow map's texel grid
	// slides relative to the light as the camera moves, causing shimmering shadow acne.
	auto shadowMapResolution = GetShadowMapResolution();
	float shadowMapWidth = shadowMapResolution.X;
	float shadowMapHeight = shadowMapResolution.Y;
	float texelSizeX = _extent / std::max(shadowMapWidth, 1.0f);
	float texelSizeY = _extent / std::max(shadowMapHeight, 1.0f);

	float distRight = Vector3::Dot(target, right);
	float distUp = Vector3::Dot(target, actualUp);
	float distForward = Vector3::Dot(target, dir);

	distRight = std::floor(distRight / texelSizeX) * texelSizeX;
	distUp = std::floor(distUp / texelSizeY) * texelSizeY;

	Vector3 snappedTarget = right * distRight + actualUp * distUp + dir * distForward;
	Vector3 lightPos = snappedTarget + dir * -100.0f;

	return Math::Matrix4x4::CreateLookAtView(lightPos, snappedTarget, actualUp);
}

Math::Matrix4x4 ShadowMapRenderer::ComputeLightProjectionMatrix() const
{
	// Orthographic projection sized in world units (square) covering the scene focus area.
	// NOTE: the engine's CreateLookAtView yields NEGATIVE view-space Z for points in front of the
	// camera (matching CreatePerspectiveProjection). The stock CreateOrthographicProjection instead
	// assumes positive Z, which would push clip.z below 0 and get the geometry clipped (empty shadow
	// map). We therefore build the matrix with a negated Z scale so clip.z lands in [0,1] for
	// view-space Z in [-NearPlane, -FarPlane].

	float w = 2.0f / _extent;
	float h = 2.0f / _extent;
	float invRange = 1.0f / (FarPlane - NearPlane);

	return Math::Matrix4x4(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, -invRange, 0.0f,
		0.0f, 0.0f, -NearPlane * invRange, 1.0f
	);
}

void ShadowMapRenderer::Begin()
{
	_determineExtent();

	auto shadowMapResolution = GetShadowMapResolution();
	Viewport shadowViewport(
		Math::RectangleF(0.0f, 0.0f, static_cast<float>(shadowMapResolution.X), static_cast<float>(shadowMapResolution.Y)),
		0.0f,
		1.0f
	);

	_oldRasterizerState = _device->GetRasterizerState();
	_oldDepthStencilState = _device->GetDepthStencilState();

	_context->UnbindRenderTargetAndDepth();
	_context->SetDepthStencilBuffer(_shadowMap.get());
	_context->ClearDepthBuffer(_shadowMap.get());

	_context->SetViewport(shadowViewport);

	_context->SetRasterizerState(_shadowRasterizerState.get());
	_context->SetDepthStencilState(_shadowDepthState.get(), 0);
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

	_context->SetRasterizerState(_oldRasterizerState.get());
	_context->SetDepthStencilState(_oldDepthStencilState.get(), 0);
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

	auto lvp = ComputeLightViewMatrix(_owner->MainLight.LightDirection) * ComputeLightProjectionMatrix();

	// The depth pass must transform vertices from object space into light clip space,
	// so the part's own World (and ImportOffset) transform has to be folded in here.
	// Without this, every mesh is rasterized using raw object-space positions, ignoring
	// where it actually is in the scene.
	auto worldLightViewProj = part->ImportOffset * part->World * lvp;

	_shadowMapEffect->SetData<Math::Matrix4x4>(&worldLightViewProj, 0);

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

Math::Vector2 ShadowMapRenderer::GetShadowMapResolution() const noexcept
{
	auto resolution = _device->Resolution();
	return Math::Vector2(resolution.X * ShadowMapSize, resolution.Y * ShadowMapSize);
}