#include "Math.hpp"

float Engine3DRadSpace::Math::ToRadians(float degrees)
{
    return static_cast<float>(std::numbers::pi * degrees / 180);
}

float Engine3DRadSpace::Math::ToDegrees(float radians)
{
    return static_cast<float>(radians * 180 / std::numbers::pi);
}

double Engine3DRadSpace::Math::ToRadians(double degrees)
{
    return std::numbers::pi * degrees / 180;
}

double Engine3DRadSpace::Math::ToDegrees(double radians)
{
    return radians * 180 / std::numbers::pi;
}