#include "Quaternion.hpp"

using namespace Engine3DRadSpace::Math;

Quaternion Quaternion::FromYawPitchRoll(float yaw, float pitch, float roll)
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

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, float angle)
{
    float w = cos(angle / 2.0f);
    float x = axis.X * sin(angle / 2.0f);
    float y = axis.Y * sin(angle / 2.0f);
    float z = axis.Z * sin(angle / 2.0f);

    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::FromMatrix(const Matrix4x4& m)
{
    Quaternion q;

    float tr = m.Trace();

    float m00 = m.M11, m01 = m.M12, m02 = m.M13;
    float m10 = m.M21, m11 = m.M22, m12 = m.M23;
    float m20 = m.M31, m21 = m.M32, m22 = m.M33;

    if (tr > 0) {
        float S = sqrtf(tr + 1.0f) * 2; // S=4*qw 
        q.W = 0.25f * S;
        q.X = (m21 - m12) / S;
        q.Y = (m02 - m20) / S;
        q.Z = (m10 - m01) / S;
    }
    else if ((m00 > m11) && (m00 > m22)) {
        float S = sqrtf(1.0f + m00 - m11 - m22) * 2; // S=4*qx 
        q.W = (m21 - m12) / S;
        q.X = 0.25f * S;
        q.Y = (m01 + m10) / S;
        q.Z = (m02 + m20) / S;
    }
    else if (m11 > m22) {
        float S = sqrtf(1.0f + m11 - m00 - m22) * 2; // S=4*qy
        q.W = (m02 - m20) / S;
        q.X = (m01 + m10) / S;
        q.Y = 0.25f * S;
        q.Z = (m12 + m21) / S;
    }
    else {
        float S = sqrtf(1.0f + m22 - m00 - m11) * 2; // S=4*qz
        q.W = (m10 - m01) / S;
        q.X = (m02 + m20) / S;
        q.Y = (m12 + m21) / S;
        q.Z = 0.25f * S;
    }
    return q;
}

Quaternion Quaternion::FromVectorToVector(const Vector3& a, const Vector3& b)
{
    Quaternion q;
    Vector3 c = Vector3::Cross(a, b);

    q.X = c.X;
    q.Y = c.Y;
    q.Z = c.Z;
    q.W = 1 + Vector3::Dot(a, b);

    return q.Normalize();
}

float Quaternion::Length() const
{
    return sqrtf((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

Quaternion Quaternion::Normalize()
{
    return *this / Length();
}

constexpr Quaternion Quaternion::Conjugate()
{
    this->X *= -1;
    this->Y *= -1;
    this->Z *= -1;
    return *this;
}

constexpr Quaternion Quaternion::Inverse()
{
    float num2 = (((X * X) + (Y * Y)) + (Z * Z)) + (W * W);
    float num = 1.0f / num2;
    X = -X * num;
    Y = -Y * num;
    Z = -Z * num;
    W = W * num;
    return *this;
}

constexpr Vector3 Quaternion::Im() const
{
    return Vector3(X,Y,Z);
}

Vector3 Quaternion::ToYawPitchRoll() const
{
    //https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    Vector3 r;
    float sinr_cosp = 2 * (W * X + Y * Z);
    float cosr_cosp = 1 - 2 * (X * X + Y * Y);
    r.Z = std::atan2f(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float sinp = std::sqrtf(1 + 2 * (W * Y - X * Z));
    float cosp = std::sqrtf(1 - 2 * (W * Y - X * Z));
    r.Y = 2.0f * std::atan2f(sinp, cosp) - std::numbers::pi_v<float> / 2.0f;

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (W * Z + X * Y);
    float cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
    r.Z = std::atan2f(siny_cosp, cosy_cosp);

    return r;
}

constexpr Quaternion Quaternion::operator+(const Quaternion &q) const
{
    return Quaternion
    {
        X + q.X,
        Y + q.Y,
        Z + q.Z,
        W + q.W
    };
}

constexpr Quaternion Quaternion::operator+=(const Quaternion &q)
{
    X += q.X;
    Y += q.Y;
    Z += q.Z;
    W += q.W;

    return *this;
}

constexpr Quaternion Engine3DRadSpace::Math::Quaternion::operator-(const Quaternion& q) const
{
    return Quaternion{
        X - q.X,
        Y - q.Y,
        Z - q.Z,
        W - q.W,
    };
}

constexpr Quaternion& Engine3DRadSpace::Math::Quaternion::operator-(const Quaternion& q)
{
    X -= q.X;
    Y -= q.Y;
    Z -= q.Z;
    W -= q.W;

    return *this;
}

constexpr Quaternion Quaternion::operator*(const Quaternion& q) const
{
    //https://stackoverflow.com/questions/19956555/how-to-multiply-two-quaternions
    Quaternion r;
    r.X = W* q.W - X * q.X - Y * q.Y - Z * q.Z;
    r.Y = W* q.X + X * q.W + Y * q.Z - Z * q.Y;
    r.Z = W* q.Y - X * q.Z + Y * q.W + Z * q.X;
    r.W = W* q.Z + X * q.Y - Y * q.Z + Z * q.W;

    return r;
}

constexpr Quaternion Quaternion::operator*=(const Quaternion &q)
{
    X = W * q.W - X * q.X - Y * q.Y - Z * q.Z;
    Y = W * q.X + X * q.W + Y * q.Z - Z * q.Y;
    Z = W * q.Y - X * q.Z + Y * q.W + Z * q.X;
    W = W * q.Z + X * q.Y - Y * q.Z + Z * q.W;

    return *this;
}

constexpr Quaternion Quaternion::operator/(float s) const
{
    return Quaternion(
        this->X / s,
        this->Y / s,
        this->Z / s,
        this->W / s);
}

constexpr Quaternion Quaternion::operator/=(float s)
{
    X /= s;
    Y /= s;
    Z /= s;
    W /= s;

    return *this;
}

constexpr Quaternion Engine3DRadSpace::Math::operator/(float f, const Quaternion& q)
{
    return Quaternion
    {
        f / q.X,
        f / q.Y,
        f / q.Z,
        f / q.W
    };
}

constexpr Quaternion Engine3DRadSpace::Math::operator*(float s, const Quaternion& q)
{
    return Quaternion
    {
        q.X * s,
        q.Y * s,
        q.Z * s,
        q.W * s,
    };
}
