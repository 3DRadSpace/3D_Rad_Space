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
	_beginCalled(false)
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

void MeshBatcher::End()
{
	_drawCalls.empty();
	_beginCalled = false;
}