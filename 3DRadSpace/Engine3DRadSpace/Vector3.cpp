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
    return Vector3(0, 0, 01);
}

float Vector3::Length()
{
    return sqrtf(X * X + Y * Y + Z * Z);
}
