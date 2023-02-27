#include "Quaternion.hpp"

using namespace Engine3DRadSpace::Math;

Quaternion Engine3DRadSpace::Math::Quaternion::FromYawPitchRoll(float yaw, float pitch, float roll)
{
    //https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);

    float w = cr * cp * cy + sr * sp * sy;
    float x = sr * cp * cy - cr * sp * sy;
    float y = cr * sp * cy + sr * cp * sy;
    float z = cr * cp * sy - sr * sp * cy;
    return Quaternion(x, y, z, w);
}

Quaternion Engine3DRadSpace::Math::Quaternion::FromAxisAngle(const Vector3& axis, float angle)
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
    r.Z = std::atan2f(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float sinp = std::sqrtf(1 + 2 * (W * Y - X * Z));
    float cosp = std::sqrtf(1 - 2 * (W * Y - X * Z));
    r.Y = 2.0f * std::atan2f(sinp, cosp) - std::numbers::pi / 2.0f;

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (W * Z + X * Y);
    float cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
    r.Y = std::atan2f(siny_cosp, cosy_cosp);

    return r;
}

Quaternion Engine3DRadSpace::Math::Quaternion::operator*(const Quaternion& q)
{
    Quaternion r;
    /*
    		    float x = quaternion1.X;
		    float y = quaternion1.Y;
		    float z = quaternion1.Z;
		    float w = quaternion1.W;
		    float num4 = quaternion2.X;
		    float num3 = quaternion2.Y;
		    float num2 = quaternion2.Z;
		    float num = quaternion2.W;
		    float num12 = (y * num2) - (z * num3);
		    float num11 = (z * num4) - (x * num2);
		    float num10 = (x * num3) - (y * num4);
		    float num9 = ((x * num4) + (y * num3)) + (z * num2);
		    quaternion.X = ((x * num) + (num4 * w)) + num12;
		    quaternion.Y = ((y * num) + (num3 * w)) + num11;
		    quaternion.Z = ((z * num) + (num2 * w)) + num10;
		    quaternion.W = (w * num) - num9;
		    return quaternion;
    */

    r.X = X * q.W + q.X * W + (Y * q.Z - Z * q.Y);
    r.Y = Y * q.W + q.Y * W + (Z * q.X - X * q.Z);
    r.Z = Z * q.W + q.Z * W + (X * q.Y - Y * q.X);
    r.W = W * q.W - (X * q.X + Y * q.Y + Z * q.Z);

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
