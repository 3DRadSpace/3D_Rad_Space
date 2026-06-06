#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_CORE_EXPORT IDrawable2D
	{
	protected:
		IDrawable2D() = default;

		IDrawable2D(const IDrawable2D&) = default;
		IDrawable2D& operator=(const IDrawable2D&) = default;

		IDrawable2D(IDrawable2D&&) noexcept = default;
		IDrawable2D& operator=(IDrawable2D&&) noexcept = default;
	public:
		virtual void Draw2D() = 0;
		virtual ~IDrawable2D() = default;
	};
}