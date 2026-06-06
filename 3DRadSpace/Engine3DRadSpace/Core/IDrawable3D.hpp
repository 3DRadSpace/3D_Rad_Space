#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_CORE_EXPORT IDrawable3D
	{
	protected:
		IDrawable3D() = default;

		IDrawable3D(const IDrawable3D&) = default;
		IDrawable3D& operator=(const IDrawable3D&) = default;

		IDrawable3D(IDrawable3D&&) noexcept = default;
		IDrawable3D& operator=(IDrawable3D&&) noexcept = default;
	public:
		virtual void Draw3D() = 0;
		virtual ~IDrawable3D() = default;
	};
}
