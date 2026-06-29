#include "LineList.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../IRasterizerState.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

void LineList::_swapRasterizer()
{
	_oldRasterizerState = _device->GetRasterizerState();
	_device->ImmediateContext()->SetRasterizerState(_lineRasterizer.get());
}

void LineList::_restoreRasterizer()
{
	_device->ImmediateContext()->SetRasterizerState(_oldRasterizerState.get());
}

LineList::LineList(IGraphicsDevice* device, const std::vector<VertexPositionColor> &points) :
	IPrimitive(device)
{
	_vertices = _device->CreateVertexBuffer<VertexPositionColor>(points, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
	_lineRasterizer = device->CreateRasterizerState(RasterizerFillMode::Solid, RasterizerCullMode::None);
}

IRasterizerState* LineList::GetLineRasterizer() const noexcept
{
	return _lineRasterizer.get();
}

void LineList::Draw3D()
{
	auto mvp = _mvp();

	_swapRasterizer();
	_shader->SetAll();
	_shader->operator[](0)->SetData(0, &mvp, sizeof(mvp));

	auto cmd = _device->ImmediateContext();
	cmd->SetRasterizerState(_lineRasterizer.get());
	cmd->SetTopology(VertexTopology::LineList);
	cmd->DrawVertexBuffer(_vertices.get());
	
	_restoreRasterizer();
}
