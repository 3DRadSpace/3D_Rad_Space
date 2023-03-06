#pragma once
#include "Libs.hpp"
#include "Vector2.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct Vector2;
		struct Point
		{
			Point(int x = 0, int y = 0) : X(x), Y(y) {};

			int X;
			int Y;

			Point operator+= (const Point& p);
			Point operator +(const Point& p);

			Point operator -=(const Point& p);
			Point operator -(const Point& p);
			Point operator -();

			Point operator *=(float s);
			Point operator *(float s);

			Point operator /=(float s);
			Point operator /(float s);

			auto operator <=>(const Point&) const = default;

			operator Engine3DRadSpace::Math::Vector2();
		};
	}
}

Engine3DRadSpace::Math::Point operator * (float s, const Engine3DRadSpace::Math::Point& p);

