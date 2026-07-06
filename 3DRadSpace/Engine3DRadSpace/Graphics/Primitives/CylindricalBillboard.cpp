#include "CylindricalBillboard.hpp"
#include "Plane.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

CylindricalBillboard::CylindricalBillboard(IGraphicsDevice *device) :
	IPrimitive(device),
	Texture(nullptr)
{
	auto vertices = CreateVertices();
	_vertices = device->CreateVertexBuffer<VertexPositionUV>(vertices, BufferUsage::ReadOnlyGPU);

	auto indices = CreateIndices();
	_indices = device->CreateIndexBuffer(indices);

	ShaderDescFile vtx("Data\\Shaders\\PositionUV.hlsl", "VS_Main", ShaderType::Vertex);
	ShaderDescFile frg("Data\\Shaders\\PositionUV.hlsl", "PS_Main", ShaderType::Fragment);

	std::array<ShaderDesc*, 2> shaders = { &vtx, &frg };

	auto effect = device->ShaderCompiler()->CompileEffect(shaders);
	if (effect.first)
	{
		_shader = effect.first;
	}
	else
	{
		throw Logging::Exception(std::format("Failed to compile effect for CylindricalBillboard: {}", effect.second.Log));
	}

	_blendState = device->CreateBlendState_AlphaBlend();
}

Matrix4x4 CylindricalBillboard::_mvp() const noexcept
{
	auto v = View;
	auto v_inv = v;
	v_inv.Invert();

	Vector3 cam_pos(v_inv.M41, v_inv.M42, v_inv.M43);
	Vector3 x_axis(v.M11, v.M21, v.M31);
	Vector3 y_axis(v.M12, v.M22, v.M32);
	Vector3 z_axis(v.M13, v.M23, v.M33);

	Vector3 up = cam_pos + y_axis;
	Vector3 fwd = cam_pos + z_axis;

	// Use Position field if set, otherwise extract from Transform
	Vector3 objectPos = (Position != Vector3::Zero()) ? Position : Vector3(Transform.M41, Transform.M42, Transform.M43);
	auto model = Matrix4x4::CreateCylindricalBillboard(objectPos, cam_pos, up, fwd, Axis, std::nullopt);

	// Apply scale transformation
	auto scale = Matrix4x4::CreateScale(Vector3(Scale.X, Scale.Y, 1.0f));

	return scale * model * v * Projection;
}

std::array<VertexPositionUV, 4> CylindricalBillboard::CreateVertices()
{
	std::array<VertexPositionUV, 4> plane;

	Vector2 s(0.5f, 0.5f);

	//Billboard in XY plane, will be rotated by cylindrical billboard matrix
	plane[0] = VertexPositionUV(Vector3(-s.X, -s.Y, 0), Vector2(0, 1));
	plane[1] = VertexPositionUV(Vector3(-s.X, +s.Y, 0), Vector2(0, 0));
	plane[2] = VertexPositionUV(Vector3(+s.X, +s.Y, 0), Vector2(1, 0));
	plane[3] = VertexPositionUV(Vector3(+s.X, -s.Y, 0), Vector2(1, 1));

	return plane;
}

std::array<unsigned, 6> CylindricalBillboard::CreateIndices()
{
	//Counter-clockwise winding for camera-facing billboard (reversed from Plane for proper facing).
	return { 0, 2, 1, 0, 3, 2 };
}

void CylindricalBillboard::Draw3D()
{
	auto mat = _mvp();

	_shader->SetAll();
	_shader->operator[](0)->SetData(0, &mat, sizeof(mat));
	_shader->operator[](1)->SetTexture(0, Texture);
	auto cmdList = _device->ImmediateContext();
	cmdList->SetTopology(VertexTopology::TriangleList);
	cmdList->SetBlendState(_blendState.get());
	cmdList->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}

