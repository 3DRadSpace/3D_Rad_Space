#include "Cone.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Math/Vector4.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Cone::Cone(IGraphicsDevice* device, float radius, float height, unsigned resolution, const Math::Color& color) : 
	IPrimitive(device, nullptr),
	Light{ Colors::White, Color(color.R * 0.15f, color.G * 0.15f, color.B * 0.15f, 1.0f), Vector3(0,-1,0), 1.0f }
{
	resolution = std::max(3u, resolution);

	auto cone_vertices = CreateConeVertices(radius, height, resolution, color);
	_vertices = device->CreateVertexBuffer<VertexPositionNormalColor>(cone_vertices, BufferUsage::ReadOnlyGPU);

	auto ind = CreateConeIndices(resolution);
	_indices = device->CreateIndexBuffer(ind);

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

[[nodiscard]] std::vector<VertexPositionNormalColor> Cone::CreateConeVertices(float radius, float height, unsigned resolution, const Math::Color& color)
{
	std::vector<VertexPositionNormalColor> triangles;
	triangles.reserve(resolution + 2);

	// Base center (normal pointing down)
	Vector3 baseNormal(0, -1, 0);
	triangles.emplace_back(Vector3(0, 0, 0), baseNormal, color);

	// Apex
	Vector3 apexNormal(0, 1, 0);
	triangles.emplace_back(Vector3(0, height, 0), apexNormal, color);

	float dtheta = 2 * std::numbers::pi_v<float> / resolution;

	// Calculate normals for cone sides
	// The normal at each vertex is the average of the normals of adjacent triangles
	float slantLength = sqrtf(radius * radius + height * height);
	float normalY = radius / slantLength;
	float normalXZ = height / slantLength;

	for(unsigned i = 0; i < resolution; i++)
	{
		float theta = dtheta * i;
		float cosTheta = cosf(theta);
		float sinTheta = sinf(theta);

		Vector3 position(radius * cosTheta, 0, radius * sinTheta);
		Vector3 normal(normalXZ * cosTheta, normalY, normalXZ * sinTheta);
		normal = Vector3::Normalize(normal);

		triangles.emplace_back(position, normal, color);
	}

	return triangles;
}

[[nodiscard]] std::vector<unsigned> Cone::CreateConeIndices(unsigned resolution)
{
	std::vector<unsigned> indices;
	indices.reserve(6 * resolution);

	//Generate cone
	for(unsigned i = 0; i < resolution; i++)
	{
		std::initializer_list<unsigned> tri = {1, (i + 2), 2 + ((i + 1) % resolution)};
		indices.insert(indices.end(), tri.begin(), tri.end());
	}

	//Generate base
	for(unsigned i = 0; i < resolution; i++)
	{
		std::initializer_list<unsigned> tri{0, 2 + ((i + 1) % resolution), (i + 2)};
		indices.insert(indices.end(), tri.begin(), tri.end());
	}

	return indices;
}

void Cone::Draw3D()
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
	cmd->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}