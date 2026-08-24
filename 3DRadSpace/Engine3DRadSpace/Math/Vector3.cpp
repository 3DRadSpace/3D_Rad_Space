#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix4x4.hpp"
#include "Vector2.hpp"

using namespace Engine3DRadSpace::Math;

Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::UnitX()
{
	return Vector3(1, 0, 0);
}

Vector3 Vector3::UnitY()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::UnitZ()
{
	return Vector3(0, 0, 1);
}

Vector3 Vector3::One()
{
	return Vector3(1,1,1);
}

Vector3 Vector3::Up()
{
	return Vector3{ 0, 1, 0 };
}

Vector3 Vector3::Down()
{
	return Vector3{ 0, -1, 0 };
}

Vector3 Vector3::Forward()
{
	return Vector3{ 0, 0, -1 };
}

Vector3 Vector3::Backward()
{
	return Vector3{ 0, 0, 1 };
}

Vector3 Vector3::Left()
{
	return Vector3{ -1, 0, 0 };
}

Vector3 Vector3::Right()
{
	return Vector3{ 1, 0,0 };
}

float Vector3::Length() const
{
	return sqrtf((X * X) + (Y * Y) + (Z * Z));
}

float Vector3::LengthSquared() const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

Vector3& Vector3::Normalize()
{
	float l = this->Length();

	this->X /= l;
	this->Y /= l;
	this->Z /= l;

	return *this;
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	float l = v.Length();
	return Vector3{ v.X / l, v.Y / l, v.Z / l };
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3{ X + v.X, Y + v.Y, Z + v.Z };
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	this->X -= v.X;
	this->Y -= v.Y;
	this->Z -= v.Z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

Vector3& Vector3::operator-()
{
	this->X *= -1;
	this->Y *= -1;
	this->Z *= -1;
	return *this;
}

Vector3 Vector3::operator-() const
{
	Vector3 c(*this);
	c.X *= 1;
	c.Y *= 1;
	c.Z *= 1;

	return c;
}

Vector3& Vector3::operator*=(float s)
{
	this->X *= s;
	this->Y *= s;
	this->Z *= s;
	return *this;
}

Vector3 Vector3::operator*(float s) const
{
	return Vector3(s * this->X, s * this->Y, s * this->Z);
}

Vector3& Vector3::operator/=(float s)
{
	X /= s;
	Y /= s;
	Z /= s;
	return *this;
}

Vector3 Vector3::operator/(float s) const
{
	return Vector3(
		X / s,
		Y / s,
		Z / s
	);
}

Vector3& Vector3::Cross(const Vector3& v)
{
	Vector3 cpy(*this);
	cpy.X = Y * v.Z - Z * v.Y;
	cpy.Y = -(X * v.Z - Z * v.X);
	cpy.Z = X * v.Y - Y * v.X;

	return *this = cpy;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(
		v1.Y * v2.Z - v1.Z * v2.Y,
		-(v1.X * v2.Z - v1.Z * v2.X),
		v1.X * v2.Y - v1.Y * v2.X
	);
}

float Vector3::Dot(const Vector3& v) const
{
	return (X * v.X) + (Y * v.Y) + (Z * v.Z);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

Vector3& Vector3::Transform(const Quaternion& q)
{
	Vector3 v(*this);
	
	//Extract the vector part of the quaternion
	Vector3 u(q.Im());

	// Extract the scalar part of the quaternion
	float s = q.W;

	// Do the math
	auto vprime = 2.0f * Dot(u, v) * u
		   + (s*s - Dot(u, u)) * v
		   + 2.0f * s * Cross(u, v);

	return *this = vprime;
}

Vector3& Vector3::Transform(const Matrix4x4& m)
{
	Vector3 cpy(*this);

	X = cpy.X * m.M11 + cpy.Y * m.M21 + cpy.Z * m.M31 + m.M41;
	Y = cpy.X * m.M12 + cpy.Y * m.M22 + cpy.Z * m.M32 + m.M42;
	Z = cpy.X * m.M13 + cpy.Y * m.M23 + cpy.Z * m.M33 + m.M43;

	return *this;
}

Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
	return Vector3(v).Transform(q);
}

Vector3 Vector3::Transform(const Vector3& v, const Matrix4x4& m)
{
	return Vector3{
		v.X * m.M11 + v.Y * m.M21 + v.Z * m.M31 + m.M41,
		v.X * m.M12 + v.Y * m.M22 + v.Z * m.M32 + m.M42,
		v.X * m.M13 + v.Y * m.M23 + v.Z * m.M33 + m.M43,
	};
}

Vector3& Vector3::Hadamard(const Vector3& v)
{
	X *= v.X;
	Y *= v.Y;
	Z *= v.Z;
	return *this;
}

Vector3 Vector3::Hadamard(const Vector3& a, const Vector3& b)
{
	return Vector3
	{
		a.X * b.X,
		a.Y * b.Y,
		a.Z * b.Z
	};
}

Vector3 Engine3DRadSpace::Math::operator*(float s, const Vector3& v)
{
	return Vector3{ s * v.X, s * v.Y, s * v.Z };
}

Vector3 Engine3DRadSpace::Math::operator/(float s, const Vector3 &v)
{
	return Vector3{ s / v.X, s / v.Y, s / v.Z };
}

Vector2 Vector3::XX() const noexcept
{
	return Vector2(X, X);
}

Vector2 Vector3::XY() const noexcept
{
	return Vector2(X, Y);
}

Vector2 Vector3::XZ() const noexcept
{
	return Vector2(X, Z);
}

Vector2 Vector3::YX() const noexcept
{
	return Vector2(Y, X);
}

Vector2 Vector3::YY() const noexcept
{
	return Vector2(Y, Y);
}

Vector2 Vector3::YZ() const noexcept
{
	return Vector2(Y, Z);
}

Vector2 Vector3::ZX() const noexcept
{
	return Vector2(Z, X);
}

Vector2 Vector3::ZY() const noexcept
{
	return Vector2(Z, Y);
}

Vector2 Vector3::ZZ() const noexcept
{
	return Vector2(Z, Z);
}
