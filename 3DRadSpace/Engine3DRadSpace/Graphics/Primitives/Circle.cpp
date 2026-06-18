#include "Circle.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

Circle::Circle(IGraphicsDevice* device, float radius, Color color, unsigned resolution) :
	LineStrip(device, CreateCircleVertices(radius, resolution, color)),
	_radius(radius)
{
}

[[nodiscard]] std::vector<VertexPositionColor> Circle::CreateCircleVertices(float radius, unsigned resolution, Color color)
{
	assert(resolution >= 2);

	resolution = std::max(resolution, 3u); //create a circle from a minimum of three points.

	std::vector<VertexPositionColor> vertices(resolution);

	float dp = 2 * std::numbers::pi_v<float> / resolution ; //delta phi
	unsigned i = 0;
	float phi = 0; //angle
	for(; i < resolution - 1; ++i, phi += dp)
	{
		vertices[i] = VertexPositionColor(
			Vector3(radius * cos(phi), 0, radius * sin(phi)),
			color
		);
	}
	vertices[resolution - 1] = vertices[0];

	return vertices;
}

float Circle::GetRadius() const noexcept
{
	return _radius;
}
