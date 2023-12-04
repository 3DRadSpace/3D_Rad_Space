#pragma once
#include "../Libs.hpp"
#include "Vector2.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct Vector2;
		struct DLLEXPORT Point
		{
			constexpr Point(int x = 0, int y = 0) : X(x), Y(y) {};

			int X;
			int Y;

			constexpr Point operator +=(const Point& p);
			constexpr Point operator +(const Point &p) const;

			constexpr Point operator -=(const Point& p);
			constexpr Point operator -(const Point &p) const;
			constexpr Point operator -();

			constexpr Point operator *=(float s);
			constexpr Point operator *(float s) const;

			constexpr Point operator /=(float s);
			constexpr Point operator /(float s) const;

			constexpr auto operator <=>(const Point&) const = default;

			constexpr operator Engine3DRadSpace::Math::Vector2() const;
		};
	}
}

constexpr Engine3DRadSpace::Math::Point DLLEXPORT operator * (float s, const Engine3DRadSpace::Math::Point& p);

