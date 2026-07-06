#pragma once
#include "CylindricalBillboard.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT SphericalBillboard : public CylindricalBillboard
	{
		Math::Matrix4x4 _mvp() const noexcept override;
	public:
		SphericalBillboard(IGraphicsDevice *device);

		~SphericalBillboard() = default;
	};
}