#include "Math.hpp"

float Engine3DRadSpace::Math::ToRadians(float degrees)
{
    return std::numbers::pi_v<float> * degrees / 180.f;
}

float Engine3DRadSpace::Math::ToDegrees(float radians)
{
    return radians * 180.f / std::numbers::pi_v<float>;
}