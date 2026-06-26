#pragma once
#include "CilindricalBillboard.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT SphericalBillboard : public CilindricalBillboard
	{
	protected:
		Math::Matrix4x4 billboardMatrix() const noexcept override;
	public:
		SphericalBillboard(IGraphicsDevice *device);

		~SphericalBillboard() = default;
	};
}