#include "Cylinder.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Math/Vector4.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Cylinder::Cylinder(IGraphicsDevice *device, float radius, float height, unsigned tessellation, Color color) :
	IPrimitive(device, nullptr),
	Light{ Colors::White, Color(color.R * 0.15f, color.G * 0.15f, color.B * 0.15f, 1.0f), Vector3(0,-1,0), 1.0f }
{
	tessellation = std::max(3u, tessellation);

	auto verts = CreateCylinderVertices(radius, height, tessellation, color);
	this->_vertices = device->CreateVertexBuffer<VertexPositionNormalColor>(verts, BufferUsage::ReadOnlyGPU);

	auto indices = CreateCylinderIndices(tessellation);
	_indices = device->CreateIndexBuffer(indices);

	// Set Lambertian shader with color
	constexpr const char* lambertShader = "Data\\Shaders\\Lambert_PositionNormal.hlsl";
	auto vsLambertShader = ShaderDescFile(
		lambertShader,
		"VS_Main",
		ShaderType::Vertex
	);
	auto psLambertShader = ShaderDescFile(
		lambertShader,
		"PS_Main",
		ShaderType::Fragment
	);
	std::array<ShaderDesc*, 2> lambertShaderDesc =
	{
		&vsLambertShader,
		&psLambertShader
	};
	auto [lambertEffect, result] = device->ShaderCompiler()->CompileEffect(lambertShaderDesc);
	if (result.Succeded)
	{
		_shader = lambertEffect;
	}
}

[[nodiscard]] std::vector<VertexPositionNormalColor> Cylinder::CreateCylinderVertices(float radius, float height, unsigned resolution, Color color)
{
	std::vector<VertexPositionNormalColor> r;
	r.reserve(2 + 2 * resolution);

	float top = height / 2;
	float bottom = -height / 2;

	//Top ring
	float dtheta = 2 * std::numbers::pi_v<float> / resolution;

	// Bottom center (normal pointing down)
	Vector3 bottomNormal(0, -1, 0);
	r.emplace_back(Vector3(0, bottom, 0), bottomNormal, color);

	// Top center (normal pointing up)
	Vector3 topNormal(0, 1, 0);
	r.emplace_back(Vector3(0, top, 0), topNormal, color);

	for(unsigned i = 0; i < resolution; i++)
	{
		auto theta = dtheta * i;
		auto cosTheta = cosf(theta);
		auto sinTheta = sinf(theta);
		auto x = radius * cosTheta;
		auto z = radius * sinTheta;

		// Normal for side vertices points radially outward (perpendicular to cylinder axis)
		Vector3 sideNormal(cosTheta, 0, sinTheta);
		sideNormal = Vector3::Normalize(sideNormal);

		r.emplace_back(Vector3(x, bottom, z), sideNormal, color);
		r.emplace_back(Vector3(x, top, z), sideNormal, color);
	}
	return r;
}

[[nodiscard]] std::vector<unsigned> Cylinder::CreateCylinderIndices(unsigned resolution)
{
	std::vector<unsigned> indices;
	indices.reserve(12 * resolution);

	for(unsigned i = 0; i < resolution; ++i)
	{
		unsigned next = (i + 1) % resolution;

		unsigned bottom_i = 2 + i * 2;
		unsigned top_i = bottom_i + 1;

		unsigned bottom_next = 2 + next * 2;
		unsigned top_next = bottom_next + 1;

		std::initializer_list<unsigned> faces =
		{
			//quad
			bottom_i, top_next, top_i, // side triangle 1
			bottom_i, bottom_next, top_next, //side triangle 2
			0, bottom_next, bottom_i, //bottom face
			1, top_i, top_next // top face
		};

		indices.insert(indices.end(), faces.begin(), faces.end());
	}

	return indices;
}

void Cylinder::Draw3D()
{
	struct alignas(16) AllDataBuffer
	{
		Matrix4x4 MatWorldViewProj;
		Matrix4x4 MatWorldInverseTranspose;
		Vector4   LightColor;
		Vector4   AmbientColor;
		Vector3   LightDirection;
		float     Intensity;
	};

	Matrix4x4 mvp = _mvp();
	Matrix4x4 worldInverseTranspose = Matrix4x4::Transpose(Matrix4x4::Invert(Transform));

	AllDataBuffer data =
	{
		mvp,
		worldInverseTranspose,
		Vector4(Light.LightColor.R,   Light.LightColor.G,   Light.LightColor.B,   Light.LightColor.A),
		Vector4(Light.AmbientColor.R, Light.AmbientColor.G, Light.AmbientColor.B, Light.AmbientColor.A),
		Light.LightDirection,
		Light.Intensity
	};

	// Upload to cbuffer slot 0 on every shader stage before binding
	_shader->SetData(&data, 0);

	_shader->SetAll();

	auto cmd = _device->ImmediateContext();
	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBufferWithIndices(_vertices.get(), _indices.get());
}