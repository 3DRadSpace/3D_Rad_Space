#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct Rectangle
		{
			Rectangle(int x = 0, int y = 0, int w = 0, int h = 0) : X(x), Y(y), Width(w), Height(h) {};

			int X;
			int Y;
			int Width;
			int Height;

			Point TopLeft() const;
			Point TopRight() const;
			Point BottomLeft() const;
			Point BottomRight() const;

			bool operator ==(const Rectangle& r) const = default;
			bool operator !=(const Rectangle& r) const = default;
		};

		struct RectangleF
		{
			RectangleF(float x = 0, float y = 0, float w = 0, float h = 0) : X(x), Y(y), Width(w), Height(h) {};

			float X;
			float Y;
			float Width;
			float Height;

			Vector2 TopLeft() const;
			Vector2 TopRight() const;
			Vector2 BottomLeft() const;
			Vector2 BottomRight() const;

			bool operator ==(const RectangleF& r) const = default;
			bool operator !=(const RectangleF& r) const = default;
		};
	}
}

