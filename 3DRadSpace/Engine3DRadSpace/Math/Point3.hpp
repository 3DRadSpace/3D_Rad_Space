#pragma once
#include "Vector3.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT Point3
	{
		explicit constexpr Point3(int x = 0, int y = 0, int z = 0) : X(x), Y(y), Z(z) {};
		explicit constexpr Point3(std::initializer_list<int> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0), 
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0), 
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0) 
		{
		};

		int X;
		int Y;
		int Z;

		Point3 operator +=(const Point3& p);
		Point3 operator +(const Point3& p) const;

		Point3 operator -=(const Point3& p);
		Point3 operator -(const Point3& p) const;
		Point3 operator -();

		Point3 operator *=(float s);
		Point3 operator *(float s) const;

		Point3 operator /=(float s);
		Point3 operator /(float s) const;

		auto operator <=>(const Point3&) const noexcept = default;

		operator Engine3DRadSpace::Math::Vector3() const;
	};
}

Engine3DRadSpace::Math::Point3 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::Point3& p);
