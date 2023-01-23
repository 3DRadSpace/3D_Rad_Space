#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct Rectangle
		{
			Rectangle(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) {};

			int X;
			int Y;
			int Width;
			int Height;
		};

		struct RectangleF
		{
			RectangleF(float x, float y, float w, float h) : X(x), Y(y), Width(w), Height(h) {};

			float X;
			float Y;
			float Width;
			float Height;
		};
	}
}

