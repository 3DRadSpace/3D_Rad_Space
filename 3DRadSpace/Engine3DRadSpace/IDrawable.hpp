#pragma once
#include "GraphicsDevice.hpp"
#include "Matrix.hpp"

namespace Engine3DRadSpace
{
	class IDrawable
	{
	public:
		virtual void Draw(
			Engine3DRadSpace::Math::Matrix& view,
			Engine3DRadSpace::Math::Matrix& projection,
			double dt) = 0;
		inline virtual ~IDrawable() = default;
	};
}
