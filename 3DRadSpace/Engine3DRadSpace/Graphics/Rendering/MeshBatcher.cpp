#include "MeshBatcher.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

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

void MeshBatcher::Draw(ModelMeshPart* meshPart, RenderPassType passType)
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

void MeshBatcher::End()
{
	if (!_beginCalled)
		throw std::logic_error("Begin() must be called before End().");
	for (const auto& drawCall : _drawCalls)
	{
		// For simplicity, we are not implementing instancing here. Just draw each mesh part separately.
		for (const auto& transform : drawCall.Transforms)
		{
			drawCall.MeshPart->Draw();
		}
	}
	_beginCalled = false;
}