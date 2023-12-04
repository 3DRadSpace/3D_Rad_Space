#include "Matrix3x3.hpp"
#include "Vector2.hpp"

using namespace Engine3DRadSpace::Math;

constexpr Matrix3x3::Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33):
	M11(m11), M12(m12), M13(m13),
	M21(m21), M22(m22), M23(m23),
	M31(m31), M32(m32), M33(m33)
{
}

constexpr Matrix3x3::Matrix3x3(float m[9]):
	M11(m[0]), M12(m[1]), M13(m[2]),
	M21(m[3]), M22(m[4]), M23(m[5]),
	M31(m[6]), M32(m[7]), M33(m[8])
{
}

Matrix3x3 Matrix3x3::CreateTranslation(const Vector2 &t)
{
	return Matrix3x3{
		1, 0, t.X,
		0, 1, t.Y,
		0, 0, 1
	};
}

Matrix3x3 Matrix3x3::CreateScale(const Vector2 &s)
{
	return Matrix3x3{
		s.X, 0, 0,
		0, s.Y, 0,
		0, 0, 1
	};
}

Matrix3x3 Matrix3x3::CreateRotation(float theta)
{
	return Matrix3x3{
		cosf(theta), -sinf(theta), 0,
		sinf(theta), cosf(theta), 0,
		0, 0, 1
	};
}

Matrix3x3 Matrix3x3::Create2DSkewing(const Vector2& skewing)
{
	return Matrix3x3(
		1, skewing.X, 0,
		skewing.Y, 1, 0,
		0, 0, 1
	);
}

constexpr float Matrix3x3::Trace() const
{
	return M11 + M22 + M33;
}

constexpr float Matrix3x3::Determinant() const
{
	//Using Rule of Sarrus
	return M11 * M22 * M33 + M12 * M23 * M31 + M21 * M32 * M13 - M13 * M22 * M31 - M21 * M12 * M33 - M11 * M23 * M32;
}

constexpr float& Matrix3x3::operator[](unsigned index)
{
	switch(index)
	{
	case 1: return M11;
	case 2: return M12;
	case 3: return M13;
	case 4: return M21;
	case 5: return M22;
	case 6: return M23;
	case 7: return M31;
	case 8: return M32;
	case 9: return M33;
	default: throw std::out_of_range("0 <= index <= 9");
	}
}

constexpr Matrix3x3& Matrix3x3::Hadamard(const Matrix3x3& m)
{
	M11 *= m.M11;
	M12 *= m.M12;
	M13 *= m.M13;

	M21 *= m.M21;
	M22 *= m.M22;
	M23 *= m.M23;

	M31 *= m.M31;
	M32 *= m.M32;
	M33 *= m.M33;

	return *this;
}

constexpr Matrix3x3 Matrix3x3::Hadamard(const Matrix3x3& a, const Matrix3x3& b)
{
	return Matrix3x3
	{
		a.M11 * b.M11,
		a.M12 * b.M12,
		a.M13 * b.M13,

		a.M21 * b.M21,
		a.M22 * b.M22,
		a.M23 * b.M23,

		a.M31 * b.M31,
		a.M32 * b.M32,
		a.M33 * b.M33,
	};
}

constexpr Matrix3x3 Matrix3x3::operator+(const Matrix3x3& m) const
{
	return Matrix3x3
	{
		M11 + m.M11, M12 + m.M12, M13 + m.M13,
		M21 + m.M21, M22 + m.M22, M23 + m.M13,
		M31 + m.M31, M32 + m.M32, M33 + m.M33
	};
}

constexpr Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m)
{
	M11 += m.M11;
	M12 += m.M12;
	M13 += m.M13;

	M21 += m.M21;
	M22 += m.M22;
	M23 += m.M23;

	M31 += m.M31;
	M32 += m.M32;
	M33 += m.M33;

	return *this;
}

constexpr Matrix3x3& Matrix3x3::operator-()
{
	M11 *= -1;
	M12 *= -1;
	M13 *= -1;

	M21 *= -1;
	M22 *= -1;
	M23 *= -1;

	M31 *= -1;
	M32 *= -1;
	M33 *= -1;

	return *this;
}

constexpr Matrix3x3 Matrix3x3::operator-(const Matrix3x3& m) const
{
	return Matrix3x3{
		M11 - m.M11, M12 - m.M12, M13 - m.M13,
		M21 - m.M21, M22 - m.M12, M23 - m.M23,
		M31 - m.M31, M32 - m.M32, M33 - m.M33
	};
}

constexpr Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& m)
{
	M11 -= m.M11;
	M12 -= m.M12;
	M13 -= m.M13;

	M21 -= m.M21;
	M22 -= m.M22;
	M23 -= m.M23;

	M31 -= m.M31;
	M32 -= m.M32;
	M33 -= m.M33;

	return *this;
}

constexpr Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m) const
{
	return Matrix3x3
	{
		M11 * m.M11 + M12 * m.M21 + M13 * m.M13,
		M11 * m.M12 + M12 * m.M22 + M13 + m.M23,
		M11 * m.M13 + M12 * m.M23 + M13 * m.M33,

		M21 * m.M11 + M22 + m.M21 + M23 * m.M11,
		M21 * m.M12 + M22 + m.M22 + M23 * m.M21,
		M21 * m.M13 + M22 + m.M23 + M23 * m.M31,

		M31 * m.M11 + M32 + m.M21 + M33 * m.M11,
		M31 * m.M12 + M32 + m.M22 + M33 * m.M21,
		M31 * m.M13 + M32 + m.M23 + M33 * m.M31,
	};
}

constexpr Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& m)
{
	M11 = M11 * m.M11 + M12 * m.M21 + M13 * m.M13;
	M12 = M11 * m.M12 + M12 * m.M22 + M13 + m.M23;
	M13 = M11 * m.M13 + M12 * m.M23 + M13 * m.M33;

	M21 = M21 * m.M11 + M22 + m.M21 + M23 * m.M11;
	M22 = M21 * m.M12 + M22 + m.M22 + M23 * m.M21;
	M23 = M21 * m.M13 + M22 + m.M23 + M23 * m.M31;

	M31 = M31 * m.M11 + M32 + m.M21 + M33 * m.M11;
	M32 = M31 * m.M12 + M32 + m.M22 + M33 * m.M21;
	M33 = M31 * m.M13 + M32 + m.M23 + M33 * m.M31;

	return *this;
}

constexpr Matrix3x3 Matrix3x3::operator*(float s) const
{
	return Matrix3x3
	{
		M11 * s, M12 * s, M13 * s,
		M21 * s, M22 * s, M23 * s,
		M31 * s, M32 * s, M33 * s,
	};
}

constexpr Matrix3x3& Matrix3x3::operator*=(float s)
{
	M11 *= s;
	M12 *= s;
	M13 *= s;

	M21 *= s;
	M22 *= s;
	M23 *= s;

	M31 *= s;
	M32 *= s;
	M33 *= s;

	return *this;
}

constexpr Matrix3x3 Matrix3x3::operator/(float s) const
{
	return Matrix3x3
	{
		M11 / s, M12 / s, M13 / s,
		M21 / s, M22 / s, M23 / s,
		M31 / s, M32 / s, M33 / s,
	};
}

constexpr Matrix3x3& Matrix3x3::operator/=(float s)
{
	M11 /= s;
	M12 /= s;
	M13 /= s;

	M21 /= s;
	M22 /= s;
	M23 /= s;

	M31 /= s;
	M32 /= s;
	M33 /= s;

	return *this;
}

constexpr Matrix3x3 Engine3DRadSpace::Math::operator*(float s, const Matrix3x3& m)
{
	return Matrix3x3
	{
		s * m.M11, s * m.M12, s * m.M13,
		s * m.M21, s * m.M22, s * m.M23,
		s * m.M31, s * m.M32, s * m.M33,
	};
}

constexpr Matrix3x3 Engine3DRadSpace::Math::operator/(float s, const Matrix3x3& m)
{
	return Matrix3x3
	{
		s / m.M11, s / m.M12, s / m.M13,
		s / m.M21, s / m.M22, s / m.M23,
		s / m.M31, s / m.M32, s / m.M33,
	};
}
