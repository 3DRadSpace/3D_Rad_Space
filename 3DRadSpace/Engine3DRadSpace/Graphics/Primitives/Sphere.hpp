#pragma once
#include "IPrimitive.hpp"
#include "../IVertexBuffer.hpp"
#include "../IIndexBuffer.hpp"
#include "../Rendering/DirectionalLight.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a spherical shape.
	/// </summary>
	/// <remarks>
	/// Same remarks as the Box type.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Sphere : public IPrimitive
	{
		float _radius;
	public:
		/// <summary>
		/// Constructs a sphere shape, with specified radius, color and shape resolution.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="radius">Radius of the sphere.</param>
		/// <param name="color">Vertex color of the sphere.</param>
		/// <param name="resolution">Defines how accurate the sphere is.</param>
		Sphere(IGraphicsDevice *device, float radius, Math::Color color, unsigned resolution);

		Sphere(const Sphere &) = delete;
		Sphere(Sphere &&) noexcept = default;

		Sphere &operator=(const Sphere &) = delete;
		Sphere &operator=(Sphere &&) noexcept = default;

		[[nodiscard]] std::vector<VertexPositionNormalColor> CreateSphereVertices(
			float radius,
			unsigned resolution,
			const Math::Color& color
		);

		[[nodiscard]] std::vector<unsigned> CreateSphereIndices(unsigned resolution);

		float GetRadius() const noexcept;

		/// <summary>
		/// Draws the sphere with default lighting parameters.
		/// </summary>
		void Draw3D() override;

		Rendering::DirectionalLight Light;
	};
}