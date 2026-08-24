#pragma once
#include "LineStrip.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Circle : public LineStrip
	{
		float _radius;
	public:
		explicit Circle(IGraphicsDevice* device, float radius = 1.0f, Math::Color color = Math::Colors::White, unsigned resolution = 100);

		[[nodiscard]] static std::vector<VertexPositionColor> CreateCircleVertices(float radius, unsigned resolution, Math::Color color);

		float GetRadius() const noexcept;

		~Circle() = default;
	};
}