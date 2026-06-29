#include "MeshBatcher.hpp"
#include "../Effect.hpp"
#include "../../Math/MVP.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

MeshBatcher::MeshBatcher(IGraphicsDevice* device) :
	_device(device)
{
}

void MeshBatcher::Clear()
{
	_drawCalls.clear();

	OutputDebugStringA("[MeshBatcher] Cleared draw calls.\n");
}

void MeshBatcher::Submit(ModelMeshPart* meshPart, RenderPassType passType, std::vector<std::unique_ptr<std::byte[]>> &&instanceData)
{
	OutputDebugStringA("[MeshBatcher] Recieved draw call.\n");

	//Find existing drawcall from the list that matches the meshPart pointer+passType.
	auto it = std::find_if(_drawCalls.begin(), _drawCalls.end(),
		[meshPart, passType](const DrawCall& dc) {
			return dc.MeshPart == meshPart && dc.PassType == passType;
		});
	if (it != _drawCalls.end())
	{
		it->InstanceWorlds.push_back(meshPart->ParentTransform * meshPart->World);
		it->View = meshPart->View;
		it->Projection = meshPart->Projection;
	}
	else
	{
		//Add new draw call into the list:
		DrawCall newCall;
		newCall.MeshPart = meshPart;
		newCall.PassType = passType;
		newCall.InstanceWorlds.push_back(meshPart->ParentTransform * meshPart->World);
		newCall.View = meshPart->View;
		newCall.Projection = meshPart->Projection;
		newCall.InstanceData = std::move(instanceData);
		newCall.IsInstanced = !newCall.InstanceData.empty();
		_drawCalls.push_back(std::move(newCall));
	}
}

std::pair<DrawCall*, size_t> MeshBatcher::GetDrawCalls()
{
	OutputDebugStringA("[MeshBatcher] Num draw call.\n");
	return {_drawCalls.data(), _drawCalls.size()};
}

std::vector<DrawCall*> MeshBatcher::GetDrawCalls(RenderPassType passType)
{
	OutputDebugStringA("[MeshBatcher] Num draw call.\n");
	std::vector<DrawCall*> result;

	for (auto& drawCall : _drawCalls)
	{
		if (drawCall.PassType == passType)
		{
			result.push_back(&drawCall);
		}	
	}

	return result;
}