#include "Math.hpp"

float Engine3DRadSpace::Math::ToRadians(float degrees)
{
    return std::numbers::pi * degrees / 180;
}

float Engine3DRadSpace::Math::ToDegrees(float radians)
{
    return radians * 180 / std::numbers::pi;
}