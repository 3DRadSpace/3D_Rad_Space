#include "Vector4.hpp"

using namespace Engine3DRadSpace::Math;

Vector4 Vector4::UnitX()
{
    return { 1,0,0,0 };
}

Vector4 Vector4::UnitY()
{
	return { 0, 1, 0, 0 };
}

Vector4 Vector4::UnitZ()
{
	return { 0, 0, 1, 0 };
}

Vector4 Vector4::UnitW()
{
	return { 0, 0, 0, 1 };
}

Vector4 Vector4::One()
{
	return { 1,1,1,1 };
}

float Vector4::Length() const
{
	return sqrtf(X * X + Y * Y + Z * Z + W * W);
}

float Vector4::LengthSquared() const
{
	return X * X + Y * Y + Z * Z + W * W;
}

float Vector4::Dot(const Vector4& a, const Vector4& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
}

float Vector4::Dot(const Vector4& v) const
{
	return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
}

Vector4 Vector4::Hadamard(const Vector4 &a, const Vector4& b)
{
	return Vector4
	{
		a.X * b.X,
		a.Y * b.Y,
		a.Z * b.Z,
		a.W * a.W
	};
}

Vector4& Vector4::Hadamard(const Vector4& v)
{
	X *= v.X;
	Y += v.Y;
	Z *= v.Z;
	W *= v.W;

	return *this;
}

Vector4 Vector4::operator+(const Vector4& v) const
{
	return
	{
		X + v.X,
		Y + v.Y,
		Z + v.Z,
		W + v.W
	};
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;
	W += v.W;
	return *this;
}

Vector4& Engine3DRadSpace::Math::Vector4::operator-()
{
	X *= -1;
	Y *= -1;
	Z *= -1;
	W *= -1;

	return *this;
}

Vector4 Vector4::operator-() const
{
	return { -X, -Y, -Z, -W };
}

Vector4 Vector4::operator-(const Vector4& v) const
{
	return
	{
		X - v.X,
		Y - v.Y,
		Z - v.Z,
		W - v.W
	};
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
	W -= v.W;

	return *this;
}

Vector4 Vector4::operator*(float scalar) const
{
	return { X * scalar, Y * scalar, Z * scalar, W * scalar };
}

Vector4& Vector4::operator*=(float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	W *= scalar;

	return *this;
}

Vector4 Vector4::operator/(float f) const
{
	return { X / f, Y / f, Z / f, W / f };
}

Vector4& Vector4::operator/=(float f)
{
	X = 1 / X;
	Y = 1 / Y;
	Z = 1 / Z;
	W = 1 / W;
	return *this;
}

Vector4& Vector4::Transform(const Matrix4x4& m)
{
	X = m.M11 * X + m.M12 * Y + m.M13 * Z + m.M14 * W;
	Y = m.M21 * X + m.M22 * Y + m.M23 * Z + m.M24 * W;
	Z = m.M31 * X + m.M32 * Y + m.M33 * Z + m.M34 * W;
	W = m.M41 * X + m.M42 * Y + m.M43 * Z + m.M44 * W;
	return *this;
}

Vector4 Vector4::Transform(const Vector4& v, const Matrix4x4 &m)
{
	Vector4 r;
	r.X = m.M11 * r.X + m.M12 * r.Y + m.M13 * v.Z + m.M14 * v.W;
	r.Y = m.M21 * r.X + m.M22 * r.Y + m.M23 * v.Z + m.M24 * v.W;
	r.Z = m.M31 * r.X + m.M32 * r.Y + m.M33 * v.Z + m.M34 * v.W;
	r.W = m.M41 * r.X + m.M42 * r.Y + m.M43 * v.Z + m.M44 * v.W;

	return r;
}

Vector4 Engine3DRadSpace::Math::operator*(float scalar, const Vector4& v)
{
	return Vector4(
		scalar * v.X,
		scalar * v.Y,
		scalar * v.Z,
		scalar * v.W
	);
}

Vector4 Engine3DRadSpace::Math::operator/(float scalar, const Vector4& v)
{
	return Vector4(
		scalar / v.X,
		scalar / v.Y,
		scalar / v.Z,
		scalar / v.W
	);
}
