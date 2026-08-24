#pragma once
#include "../Core/Libs.hpp"
#include "Vector4.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Point4
	{
		explicit constexpr Point4(int x = 0, int y = 0, int z = 0, int w = 0) : X(x), Y(y), Z(z), W(w) {};
		explicit constexpr Point4(std::initializer_list<int> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0),
			W(lst.size() > 3 ? *(lst.begin() + 3) : 0)
		{
		};

		int X;
		int Y;
		int Z;
		int W;

		Point4 operator +=(const Point4& p);
		Point4 operator +(const Point4& p) const;

		Point4 operator -=(const Point4& p);
		Point4 operator -(const Point4& p) const;
		Point4 operator -();

		Point4 operator *=(float s);
		Point4 operator *(float s) const;

		Point4 operator /=(float s);
		Point4 operator /(float s) const;

		auto operator <=>(const Point4&) const noexcept = default;

		operator Engine3DRadSpace::Math::Vector4() const;
	};
}

Engine3DRadSpace::Math::Point4 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point4& p);
