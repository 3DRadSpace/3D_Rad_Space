#pragma once

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct Point
		{
			Point() : X(0), Y(0) {};
			Point(int x, int y) : X(x), Y(y) {};
		public:
			int X;
			int Y;
		};
	}
}

