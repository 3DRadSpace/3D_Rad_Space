#pragma once
#include "GraphicsDevice.hpp"
#include "Math/Matrix.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IDrawable3D
	{
	public:
		virtual void Draw(
			Math::Matrix& view,
			Math::Matrix& projection,
			double dt) = 0;
		virtual ~IDrawable3D() = default;
	};
}
