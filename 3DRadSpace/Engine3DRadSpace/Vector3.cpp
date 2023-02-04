#include "Vector3.hpp"

float Vector3::Length()
{
    return sqrtf(X * X + Y * Y + Z * Z);
}
