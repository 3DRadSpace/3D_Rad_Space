#include "PlaneQuad.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Content;

PlaneQuad::PlaneQuad(GraphicsDevice* device, std::array<Math::Vector3, 4> points, Color planeColor):
	_device(device)
{
	std::array vertices{
		VertexPositionColor{points[0], planeColor},
		VertexPositionColor{points[1], planeColor},
		VertexPositionColor{points[2], planeColor},
		VertexPositionColor{points[3], planeColor}
	};

	std::array<unsigned,6> indices = { 0,1,2, 2,0,3 };

	this->_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, vertices);
	this->_indices = std::make_unique<IndexBuffer>(device, indices);

	_shader = ShaderManager::LoadShader<BlankShader>(device);

	_rasterState = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid, RasterizerCullMode::None);
}

void PlaneQuad::Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt)
{
#ifdef USING_DX11
	_device->_context->RSGetState(&_oldRasterState);
#endif

	[[maybe_unused]] auto _ = _shader->SetAll();
	_shader->SetTransformation(Transform * view * projection);

	_device->SetRasterizerState(_rasterState.get());
	_device->DrawVertexBufferWithindices(_vertices.get(), _indices.get());

#ifdef USING_DX11
	_device->_context->RSSetState(_oldRasterState.Get());
#endif
}
