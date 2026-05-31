#pragma once
#include "IPrimitive.hpp"
#include "../Rendering/DirectionalLight.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a Cylinder shape formed by a triangle strip.
	/// </summary>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Cylinder: public IPrimitive
	{
	public:
		Cylinder(IGraphicsDevice* device, float radius = 1.0f, float height = 1.0f, unsigned tessellation = 64u, Math::Color color = Math::Colors::White);

		[[nodiscard]] static std::vector<VertexPositionNormalColor> CreateCylinderVertices(
			float radius,
			float height,
			unsigned resolution, 
			Math::Color color
		);

		[[nodiscard]] static std::vector<unsigned> CreateCylinderIndices(unsigned resolution);

		/// <summary>
		/// Draws the cylinder with default lighting parameters.
		/// </summary>
		void Draw3D() override;

		Rendering::DirectionalLight Light;

		~Cylinder() override = default;
	};
}