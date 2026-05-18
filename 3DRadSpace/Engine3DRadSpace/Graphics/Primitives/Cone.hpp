#pragma once
#include "IPrimitive.hpp"
#include "../Rendering/DirectionalLight.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a Cone shape constructed from an indexed triangle list.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT Cone : public IPrimitive
	{
	public:
		Cone(IGraphicsDevice* device, float radius, float height, unsigned resolution, const Math::Color& color);

		[[nodiscard]] static std::vector<VertexPositionNormalColor> CreateConeVertices(float radius, float height, unsigned resolution, const Math::Color& color);
		[[nodiscard]] static std::vector<unsigned> CreateConeIndices(unsigned resolution);

		/// <summary>
		/// Draws the cone with default lighting parameters.
		/// </summary>
		void Draw3D() override;

		Rendering::DirectionalLight Light;

		~Cone() override = default;
	};
}