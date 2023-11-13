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

double Engine3DRadSpace::Math::CatmullRom(float value1, float value2, float value3, float value4, float amount)
{
    //http://www.mvps.org/directx/articles/catmull/
    const double sq = amount * amount; //pow(amount,2)
    const double cb = sq * amount; //pow(amount,3)
    return (0.5 * (2.0 * value2 +
        (value3 - value1) * amount +
        (2.0 * value1 - 5.0 * value2 + 4.0 * value3 - value4) * sq +
        (3.0 * value2 - value1 - 3.0 * value3 + value4) * cb));
}

bool DLLEXPORT Engine3DRadSpace::Math::AABB(float p1, float w1, float p2, float w2)
{
    return p1 <= p2 + w2 && p1 + w1 >= p2;
}
