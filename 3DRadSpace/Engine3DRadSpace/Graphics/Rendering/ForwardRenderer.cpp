#include "ForwardRenderer.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Logging/Exception.hpp"
#include "ShadowMapRenderer.hpp"
#include "RenderingManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

void ForwardRenderer::_loadBasicShader()
{
	constexpr const char* basicEffectPath = "Data\\Shaders\\PositionNormalTangentUV.hlsl";

	auto vsBasicEffect = ShaderDescFile(
		basicEffectPath,
		"VS_Main",
		ShaderType::Vertex
	);

	auto psBasicEffect = ShaderDescFile(
		basicEffectPath,
		"PS_Main",
		ShaderType::Fragment
	);

	std::array<ShaderDesc*, 2> basicEffectDesc =
	{
		&vsBasicEffect,
		&psBasicEffect
	};

	auto result = _device->ShaderCompiler()->CompileEffect(basicEffectDesc);
	if (result.second.Succeded == false)
	{
		throw Logging::Exception("Failed to compile default shader for Model3D!" + result.second.Log);
	}
	_trivialEffect = result.first;
}

void ForwardRenderer::_loadShadowShader()
{
	constexpr const char* shadowEffectPath = "Data\\Shaders\\PositionNormalTangentUV_Shadow.hlsl";
	auto vsShadowEffect = ShaderDescFile(
		shadowEffectPath,
		"VS_Main",
		ShaderType::Vertex
	);

	auto psShadowEffect = ShaderDescFile(
		shadowEffectPath,
		"PS_Main",
		ShaderType::Fragment
	);

	std::array<ShaderDesc*, 2> shadowEffectDesc =
	{
		&vsShadowEffect,
		&psShadowEffect
	};

	auto result = _device->ShaderCompiler()->CompileEffect(shadowEffectDesc);
	if (result.second.Succeded == false)
	{
		throw Logging::Exception("Failed to compile shadow shader for Model3D!" + result.second.Log);
	}

	_shadowEffect = result.first;
}


ForwardRenderer::ForwardRenderer(RenderingManager* owner):
	IRenderer(owner)
{
	_loadBasicShader();
	_loadShadowShader();
}

void ForwardRenderer::Begin()
{
	if (_beginCalled) return;
	_beginCalled = true;

	_device->ImmediateContext()->SetRenderTargetAndDepth(nullptr, nullptr);
}

void ForwardRenderer::Draw(ModelMeshPart* part, const MaterialDescriptor* material)
{
	if (!_beginCalled)
	{
		throw Logging::Exception("Begin() must be called before Draw()!");
	}

	if (part == nullptr) return;

	bool hasShadows = material->HasShadows;
	Effect* effect = hasShadows ? _shadowEffect : _trivialEffect;

	auto shadowMapRenderer = _owner->Get<ShadowMapRenderer>();
	if (shadowMapRenderer == nullptr)
	{
		hasShadows = false;
	}

	effect->SetAll();
	if (hasShadows)
	{
		struct alignas(16) Shadow_ConstantBuffer0
		{
			Math::Matrix4x4 WorldViewProjection;
			Math::Matrix4x4 World;
		} cb0;

		cb0.WorldViewProjection = part->MVP();
		// Must match ImportOffset * World used by MVP(), since this is what gets multiplied
		// with vertex positions to produce WorldPos in the vertex shader (used for shadow testing).
		cb0.World = part->ImportOffset * part->World;

		effect->SetData<Shadow_ConstantBuffer0>(&cb0, 0);

		struct alignas(16) Shadow_ConstantBuffer1
		{
			Math::Matrix4x4 LightViewProj; // World-space to light clip-space transform
			Math::Matrix4x4 InvViewProj; //Camera Inv(VP)
			Math::Vector3 LightDirection;
			float ShadowBias;
			float ShadowIntensity;
			Math::Vector2 TexelSize;
		} cb1;

		// NOTE: the pixel shader's CalculateShadow() receives an already WORLD-SPACE position
		// (WorldPos = mul(vertex, matWorld)), so this matrix must only transform from world
		// space into light clip space. It must NOT re-apply World/ImportOffset, otherwise the
		// object's transform gets applied twice and the shadow test samples completely
		// outside the light's frustum (shadows silently never show up).
		cb1.LightViewProj =
			shadowMapRenderer->ComputeLightViewMatrix(_owner->MainLight.LightDirection) *
			shadowMapRenderer->ComputeLightProjectionMatrix();

		cb1.InvViewProj = Math::Matrix4x4::Invert(part->View * part->Projection);
		cb1.LightDirection = _owner->MainLight.LightDirection;

		cb1.ShadowBias = shadowMapRenderer->ShadowBias;
		cb1.ShadowIntensity = shadowMapRenderer->ShadowIntensity;
		cb1.TexelSize = Math::Vector2(
			1.0f / (_device->Resolution().X * shadowMapRenderer->ShadowMapSize),
			1.0f / (_device->Resolution().Y * shadowMapRenderer->ShadowMapSize)
		);

		effect->SetData<Shadow_ConstantBuffer1>(&cb1, 1);

		effect->SetTexture(shadowMapRenderer->GetShadowMap()->GetDepthTexture(), 1);
		effect->SetSampler(shadowMapRenderer->GetShadowSampler(), 1);
	}
	else
	{
		auto mvp = part->MVP();
		effect->SetData<Math::Matrix4x4>(&mvp, 0);
	}

	size_t idTexture = 0;
	for (auto& texture : part->Textures)
	{
		if (idTexture == 1) idTexture++;

		if (texture != nullptr)
			effect->SetTexture(texture.get(), idTexture++);
	}

	idTexture = 0;
	for (auto& samplerState : part->TextureSamplers)
	{
		if (samplerState != nullptr)
			effect->SetSampler(samplerState.get(), idTexture++);
	}

	_context->SetTopology(VertexTopology::TriangleList);
	_context->DrawVertexBufferWithindices(
		part->GetVertexBuffer(),
		part->GetIndexBuffer()
	);
}

void ForwardRenderer::End()
{
	// Unbind the shadow map depth texture from the pixel/vertex shader resource slots.
	// Otherwise it remains bound as a shader input while ShadowMapRenderer::Begin() tries
	// to bind the same resource as the depth-stencil render target on the next frame,
	// which triggers a D3D11 debug layer hazard warning (DEVICE_OMSETRENDERTARGETS_HAZARD).
	if(_shadowEffect)
		_shadowEffect->SetTexture(nullptr, 1);

	_beginCalled = false;
}

bool ForwardRenderer::IsRenderPassTypeSupported(RenderPassType passType) const noexcept
{
	switch (passType)
	{
	case RenderPassType::Opaque:
	case RenderPassType::OpaqueNoShadow:
		return true;
	default:
		return false;
	}
}