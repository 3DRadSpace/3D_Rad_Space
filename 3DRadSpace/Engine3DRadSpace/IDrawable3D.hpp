#pragma once
#include "GraphicsDevice.hpp"
#include "Math\Matrix4x4.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IDrawable3D
	{
	public:
		virtual void Draw(
			Math::Matrix4x4& view,
			Math::Matrix4x4& projection,
			double dt) = 0;
		virtual ~IDrawable3D() = default;
	};
}
