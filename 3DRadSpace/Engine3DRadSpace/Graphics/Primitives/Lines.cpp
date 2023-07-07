#include "Lines.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

Lines::Lines(GraphicsDevice *device, std::span<VertexPositionColor> points):
	_device(device)
{
	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, points);
	_lineRasterizer = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid, RasterizerCullMode::None);

	simpleShader = std::make_unique<BlankShader>(device);
}

void Engine3DRadSpace::Graphics::Primitives::Lines::Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt)
{
#ifdef _DX11
	_device->_context->RSGetState(_oldRasterizerState.GetAddressOf());
#endif

	simpleShader->SetAll();
	simpleShader->SetTransformation(Transform * view * projection);

	_device->SetRasterizerState(_lineRasterizer.get());
	_device->SetTopology(VertexTopology::LineList);
	_vertices->Draw();
#ifdef _DX11
	_device->_context->RSSetState(_oldRasterizerState.Get());
#endif
}
