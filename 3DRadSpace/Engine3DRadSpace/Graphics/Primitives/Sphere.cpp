#include "Sphere.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Math/Vector4.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Sphere::Sphere(IGraphicsDevice *device, float radius, Color color, unsigned resolution):
	IPrimitive(device, nullptr),
	_radius(radius),
	Light{ Colors::White, Color(color.R * 0.15f, color.G * 0.15f, color.B * 0.15f, 1.0f), Vector3(0,-1,0), 1.0f }
{
	auto sphere_points = CreateSphereVertices(radius, resolution, color);
	_vertices = device->CreateVertexBuffer<VertexPositionNormalColor>(sphere_points, BufferUsage::ReadOnlyGPU);

	auto sphere_indices = CreateSphereIndices(resolution);
	_indices = device->CreateIndexBuffer(sphere_indices);

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

float Sphere::GetRadius() const noexcept
{
	return _radius;
}

[[nodiscard]] std::vector<VertexPositionNormalColor> Sphere::CreateSphereVertices(float radius, unsigned resolution, const Math::Color& color)
{
	auto slices = resolution;
	auto stacks = resolution;

	std::vector<VertexPositionNormalColor> v;
	v.reserve(2 + slices * (stacks - 1));

	// top pole
	Vector3 topPos(0, radius, 0);
	Vector3 topNormal = Vector3::Normalize(topPos);
	v.emplace_back(topPos, topNormal, color);

	float dphi = std::numbers::pi_v<float> / stacks;
	float dtheta = 2 * std::numbers::pi_v<float> / slices;

	// rings
	for(unsigned stack = 1; stack < stacks; ++stack)
	{
		float phi = dphi * stack;

		float y = radius * cosf(phi);
		float r = radius * sinf(phi);

		for(unsigned slice = 0; slice < slices; ++slice)
		{
			float theta = dtheta * slice;

			float x = r * cosf(theta);
			float z = r * sinf(theta);

			Vector3 position(x, y, z);
			// For a sphere centered at origin, the normal is the normalized position vector
			Vector3 normal = Vector3::Normalize(position);

			v.emplace_back(position, normal, color);
		}
	}

	// bottom pole
	Vector3 bottomPos(0, -radius, 0);
	Vector3 bottomNormal = Vector3::Normalize(bottomPos);
	v.emplace_back(bottomPos, bottomNormal, color);

	return v;
}

[[nodiscard]] std::vector<unsigned> Sphere::CreateSphereIndices(unsigned resolution)
{
	//https://github.com/caosdoar/spheres/blob/master/src/spheres.cpp

	auto slices = resolution;
	auto stacks = resolution;

	std::vector<unsigned> indices;
	indices.reserve(6 * slices * stacks);

	unsigned top = 0;
	unsigned bottom = 1 + slices * (stacks - 1);

	// top cap
	for(unsigned i = 0; i < slices; ++i)
	{
		unsigned next = (i + 1) % slices;

		std::initializer_list<unsigned> tr = {top, i + 1, next + 1};
		indices.insert(indices.end(), tr);
	}

	// middle
	for(unsigned stack = 0; stack < stacks - 2; ++stack)
	{
		unsigned ringStart = 1 + stack * slices;
		unsigned nextRingStart = ringStart + slices;

		for(unsigned slice = 0; slice < slices; ++slice)
		{
			unsigned next = (slice + 1) % slices;

			unsigned a = ringStart + slice;
			unsigned b = ringStart + next;
			unsigned c = nextRingStart + slice;
			unsigned d = nextRingStart + next;

			std::initializer_list<unsigned> quad =
			{
				a, c, d,
				a, d, b
			};

			indices.insert(indices.end(), quad);
		}
	}

	// bottom cap
	unsigned lastRing = bottom - slices;

	for(unsigned i = 0; i < slices; ++i)
	{
		unsigned next = (i + 1) % slices;

		std::initializer_list<unsigned> tr{bottom, lastRing + next, lastRing + i};
		indices.insert(indices.end(), tr);
	}

	return indices;
}

void Sphere::Draw3D()
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