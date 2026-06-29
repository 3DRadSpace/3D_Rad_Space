#include "LineStrip.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

LineStrip::LineStrip(IGraphicsDevice* device, const std::vector<VertexPositionColor> &points) :
	LineList(device, points)
{
}

void LineStrip::Draw3D()
{
	auto mvp = _mvp();

	_swapRasterizer();
	_shader->SetAll();
	_shader->operator[](0)->SetData(0, &mvp, sizeof(mvp));

	auto cmd = _device->ImmediateContext();
	cmd->SetRasterizerState(_lineRasterizer.get());
	cmd->SetTopology(VertexTopology::LineStrip);
	cmd->DrawVertexBuffer(_vertices.get());
	_restoreRasterizer();
}
