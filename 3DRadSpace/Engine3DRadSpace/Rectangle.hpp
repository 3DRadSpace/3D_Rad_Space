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

			auto operator <=>(const Rectangle& r) const = default;
		};

		struct RectangleF
		{
			RectangleF(float x = 0, float y = 0, float w = 0, float h = 0) : X(x), Y(y), Width(w), Height(h) {};

			float X;
			float Y;
			float Width;
			float Height;

			auto operator <=>(const RectangleF& r) const = default;
		};
	}
}

