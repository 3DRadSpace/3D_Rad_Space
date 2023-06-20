#pragma once
#include "GraphicsDevice.hpp"
#include "Math/Matrix.hpp"

namespace Engine3DRadSpace
{
	class IDrawable3D
	{
	public:
		virtual void Draw(
			Engine3DRadSpace::Math::Matrix& view,
			Engine3DRadSpace::Math::Matrix& projection,
			double dt) = 0;
		inline virtual ~IDrawable3D() = default;
	};
}