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

		effect->SetData<Shadow_ConstantBuffer0>(&cb0, 0);

		cb0.WorldViewProjection = part->MVP();
		cb0.World = part->World;

		struct Shadow_ConstantBuffer1
		{
			Math::Matrix4x4 WorldViewProjLight; // MVP transformation for light
			Math::Matrix4x4 InvViewProj; //Camera Inv(VP)
			Math::Vector3 LightDirection;
			float ShadowBias;
			float ShadowIntensity;
			Math::Vector2 padding;
		} cb1;

		cb1.WorldViewProjLight =
			cb0.World *
			ShadowMapRenderer::ComputeLightViewMatrix(_owner->MainLight.LightDirection) *
			ShadowMapRenderer::ComputeLightProjectionMatrix(_device->Resolution());

		cb1.InvViewProj = Math::Matrix4x4::Invert(part->View * part->Projection);
		cb1.LightDirection = _owner->MainLight.LightDirection;

		cb1.ShadowBias = shadowMapRenderer->ShadowBias;
		cb1.ShadowIntensity = shadowMapRenderer->ShadowIntensity;
	}
	else
	{
		auto mvp = part->MVP();
		effect->SetData<Math::Matrix4x4>(&mvp, 0);
	}

	size_t idTexture = 0;
	for (auto& texture : part->Textures)
	{
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