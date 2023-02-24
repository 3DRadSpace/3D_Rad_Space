#include "Quaternion.hpp"

using namespace Engine3DRadSpace::Math;

constexpr Quaternion Engine3DRadSpace::Math::Quaternion::FromYawPitchRoll(float yaw, float pitch, float roll)
{
    //https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

    float cr = cos(roll * 0.5);
    float sr = sin(roll * 0.5);
    float cp = cos(pitch * 0.5);
    float sp = sin(pitch * 0.5);
    float cy = cos(yaw * 0.5);
    float sy = sin(yaw * 0.5);

    float w = cr * cp * cy + sr * sp * sy;
    float x = sr * cp * cy - cr * sp * sy;
    float y = cr * sp * cy + sr * cp * sy;
    float z = cr * cp * sy - sr * sp * cy;
    return Quaternion(x, y, z, w);
}

constexpr Quaternion Engine3DRadSpace::Math::Quaternion::FromAxisAngle(const Vector3& axis, float angle)
{
    float w = cos(angle / 2.0f);
    float x = axis.X * sin(angle / 2.0f);
    float y = axis.Y * sin(angle / 2.0f);
    float z = axis.Z * sin(angle / 2.0f);

    return Quaternion(x, y, z, w);
}

float Engine3DRadSpace::Math::Quaternion::Length() const
{
    return sqrt(X * X + Y * Y + Z * Z + W * W);
}

Quaternion Engine3DRadSpace::Math::Quaternion::Normalize()
{
    return *this / Length();
}

Vector3 Quaternion::Im() const
{
    return Vector3(X,Y,Z);
}

Vector3 Engine3DRadSpace::Math::Quaternion::ToYawPitchRoll()
{
    //https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    Vector3 r;
    float sinr_cosp = 2 * (W * X + Y * Z);
    float cosr_cosp = 1 - 2 * (X * X + Y * Y);
    r.Z = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float sinp = std::sqrt(1 + 2 * (W * Y - X * Z));
    float cosp = std::sqrt(1 - 2 * (W * Y - X * Z));
    r.Y = 2 * std::atan2(sinp, cosp) - std::numbers::pi / 2;

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (W * Z + X * Y);
    float cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
    r.Y = std::atan2(siny_cosp, cosy_cosp);

    return r;
}

Quaternion Engine3DRadSpace::Math::Quaternion::operator/(float s)
{
    return Quaternion(
        this->X / s,
        this->Y / s,
        this->Z / s,
        this->W / s);
}
