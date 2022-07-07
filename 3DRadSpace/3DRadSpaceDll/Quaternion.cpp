#include "Quaternion.hpp"

Engine3DRadSpace::Quaternion Engine3DRadSpace::Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{

    float halfRoll = roll * 0.5f;
    float halfPitch = pitch * 0.5f;
    float halfYaw = yaw * 0.5f;

    float sinRoll = sin(halfRoll);
    float cosRoll = cos(halfRoll);
    float sinPitch = sin(halfPitch);
    float cosPitch = cos(halfPitch);
    float sinYaw = sin(halfYaw);
    float cosYaw = cos(halfYaw);

    return Quaternion((cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
        (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll),
        (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
        (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll));
}

Engine3DRadSpace::Quaternion Engine3DRadSpace::operator*(const Quaternion& q1, const Quaternion& q2)
{
	float x = q1.X;
	float y = q1.Y;
	float z = q1.Z;
	float w = q1.W;
	float num4 = q2.X;
	float num3 = q2.Y;
	float num2 = q2.Z;
	float num = q2.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	return Quaternion( ((x * num) + (num4 * w)) + num12, ((y * num) + (num3 * w)) + num11,((z * num) + (num2 * w)) + num10, (w * num) - num9);
}

Engine3DRadSpace::Quaternion Engine3DRadSpace::operator*=( Quaternion& q1, const Quaternion& q2)
{
	float x = q1.X;
	float y = q1.Y;
	float z = q1.Z;
	float w = q1.W;
	float num4 = q2.X;
	float num3 = q2.Y;
	float num2 = q2.Z;
	float num = q2.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	q1.X = ((x * num) + (num4 * w)) + num12;
	q1.Y = ((y * num) + (num3 * w)) + num11;
	q1.Z = ((z * num) + (num2 * w)) + num10;
	q1.W = (w * num) - num9;
	return q1;
}

bool Engine3DRadSpace::operator==(const Quaternion& q1, const Quaternion &q2)
{
	return q1.X == q2.X && q1.Y == q2.Y && q1.Z == q2.Z && q1.W == q2.W;
}

bool Engine3DRadSpace::operator!=(const Quaternion& q1, const Quaternion &q2)
{
	return q1.X != q2.X && q1.Y != q2.Y && q1.Z != q2.Z && q1.W != q2.W;
}

