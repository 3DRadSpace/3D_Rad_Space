#include "MeshBatcher.hpp"
#include "../Effect.hpp"
#include "../ModelMesh.hpp"
#include "../Model3D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

MeshBatcher::DrawCall::DrawCall() :
	MeshPart(nullptr),
	PassType(RenderPassType::Opaque),
	BoundEffect(nullptr)
{
}

void MeshBatcher::DrawCall::Draw(IGraphicsCommandList* context, size_t idxTransform)
{
	auto effect = BoundEffect ? BoundEffect : MeshPart->GetShaders();
	Draw(context, effect, idxTransform);
}

void MeshBatcher::DrawCall::Draw(IGraphicsCommandList* context, Effect* effect, size_t idxTransform)
{
	if (!context) return;
	if (!MeshPart) return;

	effect = effect ? effect : MeshPart->GetShaders();
	if (!effect) return;

	effect->SetAll();

	// Set the world transform matrix
	if (Transforms.size() > 0 && idxTransform < Transforms.size())
	{
		effect->SetData<Math::Matrix4x4>(&Transforms[idxTransform], 0, 0);
	}

	for (auto& instance : InstanceData)
	{
		effect->SetData(
			static_cast<void*>(instance.Data.get()),
			instance.SizeInBytes,
			instance.BufferID
		);
	}

	for (int i = 0; i < MeshPart->Textures.size(); i++)
	{
		effect->SetTexture(MeshPart->Textures[i].get(), i);
		effect->SetSampler(MeshPart->TextureSamplers[i].get(), i);
	}

	context->SetTopology(VertexTopology::TriangleList);
	context->DrawVertexBufferWithIndices(MeshPart->VertexBuffer.get(), MeshPart->IndexBuffer.get());
}

MeshBatcher::MeshBatcher(IGraphicsDevice* device) :
	_device(device),
	_beginCalled(false),
	_shadowDepthEffect(nullptr)
{
}

void MeshBatcher::Begin()
{
	_drawCalls.clear();
	_beginCalled = true;
}

void MeshBatcher::Draw(ModelMeshPart* meshPart, Effect* effect, RenderPassType passType)
{
	if (!_beginCalled)
		throw std::logic_error("Begin() must be called before Draw().");

	// For opaque objects, also submit to shadow map pass
	// This ensures shadow-casting geometry is rendered in both passes
	if (passType == RenderPassType::Opaque)
	{
		// Add to shadow map pass
		auto shadowIt = std::find_if(_drawCalls.begin(), _drawCalls.end(),
			[meshPart](const DrawCall& dc) {
				return dc.MeshPart == meshPart && dc.PassType == RenderPassType::ShadowMap;
			});
		if (shadowIt != _drawCalls.end())
		{
			shadowIt->Transforms.push_back(meshPart->Transform);
		}
		else
		{
			DrawCall shadowCall;
			shadowCall.MeshPart = meshPart;
			shadowCall.PassType = RenderPassType::ShadowMap;
			shadowCall.BoundEffect = effect;
			shadowCall.Transforms.push_back(meshPart->Transform);
			_drawCalls.push_back(std::move(shadowCall));
		}
	}

	// Add to requested pass type
	auto it = std::find_if(_drawCalls.begin(), _drawCalls.end(),
		[meshPart, passType](const DrawCall& dc) {
			return dc.MeshPart == meshPart && dc.PassType == passType;
		});
	if (it != _drawCalls.end())
	{
		it->Transforms.push_back(meshPart->Transform);
	}
	else
	{
		DrawCall newCall;
		newCall.MeshPart = meshPart;
		newCall.PassType = passType;
		newCall.BoundEffect = effect;
		newCall.Transforms.push_back(meshPart->Transform);
		_drawCalls.push_back(std::move(newCall));
	}
}

void MeshBatcher::Draw(ModelMesh* mesh, Effect* effect, RenderPassType passType)
{
	if (!_beginCalled) throw std::logic_error("Begin() must be called before Draw().");

	for (auto& meshPart : *mesh)
	{
		Draw(meshPart.get(), effect, passType);
	}
}

void MeshBatcher::Draw(Model3D* model, Effect* effect, RenderPassType passType)
{
	if (!_beginCalled) throw std::logic_error("Begin() must be called before Draw().");

	for (auto& mesh : *model)
	{
		Draw(mesh.get(), effect, passType);
	}
}

void MeshBatcher::DrawAll()
{
	for (auto& drawCall : _drawCalls)
	{
		for (size_t i = 0; i < drawCall.Transforms.size(); i++)
		{
			drawCall.Draw(_device->ImmediateContext(), i);
		}
	}
	_beginCalled = false;
}

void MeshBatcher::DrawAll(RenderPassType passType)
{
	for (auto& drawCall : _drawCalls)
	{
		if (drawCall.PassType == passType)
		{
			// Use shadow depth shader for shadow map pass
			Effect* effectOverride = (passType == RenderPassType::ShadowMap && _shadowDepthEffect) 
				? _shadowDepthEffect 
				: nullptr;

			for (size_t i = 0; i < drawCall.Transforms.size(); i++)
			{
				if (effectOverride)
				{
					// For shadow pass, set both world and light matrices
					struct ShadowMatrices
					{
						Math::Matrix4x4 World;
						Math::Matrix4x4 LightViewProj;
					} matrices;
					matrices.World = drawCall.Transforms[i];
					matrices.LightViewProj = _lightViewProj;
					effectOverride->SetData(&matrices, 0);

					drawCall.Draw(_device->ImmediateContext(), effectOverride, i);
				}
				else
				{
					drawCall.Draw(_device->ImmediateContext(), i);
				}
			}
		}
	}
}

void MeshBatcher::SetShadowDepthEffect(Effect* effect, const Math::Matrix4x4& lightViewProj)
{
	_shadowDepthEffect = effect;
	_lightViewProj = lightViewProj;
}

void MeshBatcher::End()
{
	_drawCalls.empty();
	_beginCalled = false;
}