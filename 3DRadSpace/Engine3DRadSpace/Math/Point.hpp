#pragma once
#include "../Core/Libs.hpp"
#include "Vector2.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct E3DRSP_MATH_EXPORT Point
		{
			explicit constexpr Point(int x = 0, int y = 0) : X(x), Y(y) {};
			explicit constexpr Point(std::initializer_list<int> lst) :
				X(lst.size() > 0 ? *(lst.begin()) : 0),
				Y(lst.size() > 1 ? *(lst.begin() + 1) : 0)
			{
			};

			int X;
			int Y;

			Point operator +=(const Point& p);
			Point operator +(const Point &p) const;

			Point operator -=(const Point& p);
			Point operator -(const Point &p) const;
			Point operator -();

			Point operator *=(float s);
			Point operator *(float s) const;

			Point operator /=(float s);
			Point operator /(float s) const;

			auto operator <=>(const Point&) const noexcept = default;

			operator Engine3DRadSpace::Math::Vector2() const;
		};
	}
}

Engine3DRadSpace::Math::Point E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point& p);

