#include "Sphere.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

Sphere::Sphere(GraphicsDevice *device, float radius, Color color, unsigned resolution):
	_device(device)
{
	if(resolution <= 1) resolution += 1;

	std::vector<VertexPositionColor> sphere_points =
	{
		VertexPositionColor{Vector3::UnitY() * -radius, color }
	};

	double dr = 2 * std::numbers::pi / resolution;
	double dh = 2 * radius / resolution;

	unsigned it_h = 0;
	unsigned it_t = 0;

	for(double h = -radius + dh; h <= radius - dh; h += dh, it_h++)
	{
		for(double theta = 0, local_radius = sqrt(pow(radius,2) - pow(h,2)); theta <= 2 * std::numbers::pi; theta += dh)
		{
			sphere_points.push_back(VertexPositionColor{
				Vector3(
					float(local_radius * cos(theta)),
					float(h),
					float(local_radius * sin(theta))
				), color }
			);
		}
	}

	sphere_points.push_back(VertexPositionColor(Vector3::UnitY() * radius, color));

	_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, sphere_points);

	std::vector<unsigned> sphere_indices;

	_indices = std::make_unique<IndexBuffer>(device, sphere_indices);
	_shader = ShaderManager::LoadShader<BlankShader>(device);
}

void Sphere::Draw(Matrix&view, Matrix&projection, double dt)
{
	_shader->SetBasic();
	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}
