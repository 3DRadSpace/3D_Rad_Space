#include "CilindricalBillboard.hpp"
#include "Plane.hpp"
#include "../IGraphicsCommandList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

CilindricalBillboard::CilindricalBillboard(IGraphicsDevice *device) :
	IPrimitive(device),
	Texture(nullptr)
{
	auto vertices = CreateVertices();
	_vertices = device->CreateVertexBuffer<VertexPositionUV>(vertices, BufferUsage::ReadOnlyGPU);
	
	auto indices = Plane::CreateIndices();
	_indices = device->CreateIndexBuffer(indices);
}

Matrix4x4 CilindricalBillboard::_mvp() const noexcept
{
	auto v = View;

	Vector3 cam_pos(v.M41, v.M42, v.M43);
	Vector3 x_axis(v.M11, v.M21, v.M31);
	Vector3 y_axis(v.M11, v.M21, v.M31);
	Vector3 z_axis(v.M11, v.M21, v.M31);
	
	Vector3 fwd = cam_pos + z_axis;
	Vector3 up = cam_pos + y_axis;
	Vector3 right = cam_pos + x_axis;

	auto model = Matrix4x4::CreateCylindricalBillboard(Position, cam_pos, up, fwd, Axis, std::nullopt);
	return model * View * Projection;
}

std::array<VertexPositionUV, 4> CilindricalBillboard::CreateVertices()
{
	std::array<VertexPositionUV, 4> plane;

	Vector2 s(0.5f);

	//See Plane.cpp
	plane[0] = VertexPositionUV(Vector3(-s.X, 0, -s.Y), Vector2(0,1));
	plane[1] = VertexPositionUV(Vector3(-s.X, 0, +s.Y), Vector2(0,0));
	plane[2] = VertexPositionUV(Vector3(+s.X, 0, +s.Y), Vector2(0,1));
	plane[3] = VertexPositionUV(Vector3(+s.X, 0, -s.Y), Vector2(1,1));

	return plane;
}

void CilindricalBillboard::Draw3D()
{
	auto mat = _mvp();

	_shader->SetAll();
	_shader->operator[](0)->SetData(0, &mat, sizeof(mat));
	_shader->operator[](1)->SetTexture(0, Texture);
	_device->ImmediateContext()->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}

