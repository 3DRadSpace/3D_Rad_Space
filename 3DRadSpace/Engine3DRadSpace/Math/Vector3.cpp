#include "Vector3.hpp"

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

Vector3 Engine3DRadSpace::Math::Vector3::One()
{
    return Vector3(1,1,1);
}

float Vector3::Length() const
{
    return sqrtf((X * X) + (Y * Y) + (Z * Z));
}

float Vector3::LengthSquared() const
{
    return (X * X) + (Y * Y) + (Z * Z);
}

Vector3 Vector3::Normalize()
{
    float l = this->Length();

    this->X /= l;
    this->Y /= l;
    this->Z /= l;

    return *this;
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
    return Vector3(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    this->X -= v.X;
    this->Y -= v.Z;
    this->Z -= v.Z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
}

Vector3 Vector3::operator-()
{
    this->X *= -1;
    this->Y *= -1;
    this->Z *= -1;
    return *this;
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

Vector3 Engine3DRadSpace::Math::Vector3::Cross(const Vector3& v)
{
    X = Y * v.Z - Z * v.Y;
    Y = Z * v.X - X * v.Z;
    Z = X * v.Y - Y * v.X;

    return *this;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
    return Vector3(
        v1.Y * v2.Z - v1.Z * v2.Y,
        v1.Z * v2.X - v1.X * v2.Z,
        v1.X * v2.Y - v1.Y * v2.X
    );
}

float Vector3::Dot(const Vector3& v) const
{
    return (this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return (a.X * b.X) + (a.Y + b.Y) + (a.Z * b.Z);
}

Vector3& Vector3::Transform(const Quaternion& q)
{
    float x = 2 * (q.Y * Z - q.Z * Y);
    float y = 2 * (q.Z * X - q.X * Z);
    float z = 2 * (q.X * Y - q.Y * X);

    this->X = X + x * q.W + (q.Y * z - q.Z * y);
    this->Y = Y + y * q.W + (q.Z * x - q.X * z);
    this->Z = Z + z * q.W + (q.X * y - q.Y * x);

    return *this;
}

Vector3& Vector3::Transform(const Matrix& m)
{
    this->X = X * m.M11 + Y * m.M12 + Z * m.M13 + m.M14;
    this->Y = X * m.M21 + Y * m.M22 + Z * m.M23 + m.M24;
    this->Z = X * m.M31 + Y * m.M32 + Z * m.M33 + m.M34;

    return *this;
}

Vector3& Engine3DRadSpace::Math::operator*=(float s, Vector3& v)
{
    v.X *= s;
    v.Y *= s;
    v.Z *= s;
    return v;
}

Vector3 Engine3DRadSpace::Math::operator*(float s, const Vector3& v)
{
    return Vector3(s * v.X, s * v.Y, s * v.Z);
}

Vector3 &Engine3DRadSpace::Math::operator/=(float s, Vector3 &v)
{
    v.X = s / v.X;
    v.Y = s / v.Y;
    v.Z = s / v.Z;
    return v;
}

Vector3 Engine3DRadSpace::Math::operator/(float s, const Vector3 &v)
{
    return Vector3(s / v.X, s / v.Y, s / v.Z);
}
