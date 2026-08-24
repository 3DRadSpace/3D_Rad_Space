#pragma once
#include "../Core/Libs.hpp"
#include "Vector4.hpp"

namespace Engine3DRadSpace::Math
{
	struct E3DRSP_MATH_EXPORT UPoint4
	{
		explicit constexpr UPoint4(
			unsigned x = 0,
			unsigned y = 0,
			unsigned z = 0,
			unsigned w = 0
		) : X(x), Y(y), Z(z), W(w) 
		{
		}

		explicit constexpr UPoint4(std::initializer_list<unsigned> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0),
			W(lst.size() > 3 ? *(lst.begin() + 3) : 0)
		{
		}
		
		unsigned X;
		unsigned Y;
		unsigned Z;
		unsigned W;

		UPoint4 operator +=(const UPoint4& p);
		UPoint4 operator +(const UPoint4& p) const;

		UPoint4 operator -=(const UPoint4& p);
		UPoint4 operator -(const UPoint4& p) const;

		UPoint4 operator *=(float s);
		UPoint4 operator *(float s) const;

		UPoint4 operator /=(float s);
		UPoint4 operator /(float s) const;

		auto operator <=>(const UPoint4&) const noexcept = default;
	};
}

Engine3DRadSpace::Math::UPoint4 E3DRSP_MATH_EXPORT operator * (float s, const Engine3DRadSpace::Math::UPoint4& p);
