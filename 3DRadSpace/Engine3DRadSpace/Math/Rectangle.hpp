#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct DLLEXPORT Rectangle
		{
			constexpr Rectangle(int x = 0, int y = 0, int w = 0, int h = 0) : X(x), Y(y), Width(w), Height(h) {};

			int X;
			int Y;
			int Width;
			int Height;

			constexpr Point TopLeft() const;
			constexpr Point TopRight() const;
			constexpr Point BottomLeft() const;
			constexpr Point BottomRight() const;
			constexpr Point Center() const;

			constexpr bool operator ==(const Rectangle& r) const = default;
			constexpr bool operator !=(const Rectangle& r) const = default;
		};

		struct DLLEXPORT RectangleF
		{
			constexpr RectangleF(float x = 0, float y = 0, float w = 0, float h = 0) : X(x), Y(y), Width(w), Height(h) {};

			float X;
			float Y;
			float Width;
			float Height;

			constexpr Vector2 TopLeft() const;
			constexpr Vector2 TopRight() const;
			constexpr Vector2 BottomLeft() const;
			constexpr Vector2 BottomRight() const;
			constexpr Vector2 Center() const;

			constexpr bool operator ==(const RectangleF& r) const = default;
			constexpr bool operator !=(const RectangleF& r) const = default;
		};
	}
}

