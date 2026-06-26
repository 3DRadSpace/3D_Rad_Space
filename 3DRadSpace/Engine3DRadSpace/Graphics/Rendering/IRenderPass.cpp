#include "IRenderPass.hpp"
#include "../Effect.hpp"
#include "../ModelMeshPart.hpp"
#include "../../Core/IGame.hpp"
#include "../../Math/MVP.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

IRenderPass::IRenderPass(IGraphicsDevice* device):
	_device(device)
{
}

void IRenderPass::Draw(DrawCall* drawCall)
{
	auto meshPart = drawCall->MeshPart;
	auto material = meshPart->GetShaders();
	material->SetAll();

	for (size_t numTextures = 0; numTextures < meshPart->Textures.size(); numTextures++)
	{
		material->SetTexture(meshPart->Textures[numTextures].get(), static_cast<int>(numTextures));
		material->SetSampler(meshPart->TextureSamplers[numTextures].get(), static_cast<int>(numTextures));
	}

	for (int i = 0; i < drawCall->InstanceWorlds.size(); ++i)
	{
		auto mvp = Math::MVP
		{
			.World = drawCall->InstanceWorlds[i],
			.View = drawCall->View,
			.Projection = drawCall->Projection
		};

		auto& instanceWorld = drawCall->InstanceWorlds[i];
		material->SetData<Math::MVP>(&mvp, 0);

		if (drawCall->InstanceData.size() > i && drawCall->InstanceData[i])
		{
			material->SetData(drawCall->InstanceData[i].get(), sizeof(std::byte) * 256, 1, 0);
		}

		auto context = _device->ImmediateContext();
		context->SetTopology(drawCall->Topology);
		context->DrawVertexBufferWithindices(meshPart->GetVertexBuffer(), meshPart->GetIndexBuffer());
	}
}

IGraphicsDevice* IRenderPass::GetDevice() const noexcept
{
	return _device;
}

void IRenderPass::SetOwner(IGame* owner) noexcept
{
	_owner = owner;
}

IGame* IRenderPass::GetOwner() const noexcept
{
	return _owner;
}