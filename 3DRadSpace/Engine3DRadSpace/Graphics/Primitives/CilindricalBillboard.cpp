#include "CilindricalBillboard.hpp"
#include "Plane.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../../Math/MVP.hpp"
#include "../IShaderCompiler.hpp"

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

	constexpr const char* effectPath = "Data\\Shaders\\PositionUV.hlsl";

	auto vsBasicEffect = ShaderDescFile(
		effectPath,
		"VS_Main",
		ShaderType::Vertex
	);

	auto psBasicEffect = ShaderDescFile(
		effectPath,
		"PS_Main",
		ShaderType::Fragment
	);

	std::array<ShaderDesc*, 2> positionUVShader =
	{
		&vsBasicEffect,
		&psBasicEffect
	};

	auto compiledEffect = device->ShaderCompiler()->CompileEffect(positionUVShader);
	if (compiledEffect.first != nullptr)
	{
		_shader = compiledEffect.first;
	}
	else
	{
		throw std::exception("Failed to compile PositionUV shader.");
	}
}

Matrix4x4 CilindricalBillboard::billboardMatrix() const noexcept
{
	auto v = View;

	Vector3 x_axis(v.M11, v.M21, v.M31);
	Vector3 y_axis(v.M12, v.M22, v.M32);
	Vector3 z_axis(v.M13, v.M23, v.M33);

	Vector3 cam_pos = -(x_axis * v.M41 + y_axis * v.M42 + z_axis * v.M43);

	auto model = Matrix4x4::CreateCylindricalBillboard(Position, cam_pos, y_axis, z_axis, Axis, std::nullopt);
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
	auto mat = billboardMatrix();

	MVP mvp{
		.World = mat,
		.View = Matrix4x4(),
		.Projection = Matrix4x4()
	};

	_shader->SetAll();
	_shader->operator[](0)->SetData(0, &mvp, sizeof(mvp));
	_shader->operator[](1)->SetTexture(0, Texture);

	auto context = _device->ImmediateContext();
	context->SetTopology(VertexTopology::TriangleList);
	context->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}

