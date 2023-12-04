#include "Math.hpp"

constexpr float Engine3DRadSpace::Math::ToRadians(float degrees)
{
    return static_cast<float>(std::numbers::pi * degrees / 180);
}

constexpr float Engine3DRadSpace::Math::ToDegrees(float radians)
{
    return static_cast<float>(radians * 180 / std::numbers::pi_v<float>);
}

constexpr double Engine3DRadSpace::Math::ToRadians(double degrees)
{
    return std::numbers::pi * degrees / 180;
}

constexpr double Engine3DRadSpace::Math::ToDegrees(double radians)
{
    return radians * 180 / std::numbers::pi;
}

constexpr double Engine3DRadSpace::Math::CatmullRom(double value1, double value2, double value3, double value4, double amount)
{
    //http://www.mvps.org/directx/articles/catmull/
    const double sq = amount * amount; //pow(amount,2)
    const double cb = sq * amount; //pow(amount,3)
    return (0.5 * (2.0 * value2 +
        (value3 - value1) * amount +
        (2.0 * value1 - 5.0 * value2 + 4.0 * value3 - value4) * sq +
        (3.0 * value2 - value1 - 3.0 * value3 + value4) * cb));
}

constexpr double DLLEXPORT Engine3DRadSpace::Math::Hermite(double value1, double tangent1, double value2, double tangent2, double amount)
{
    double v1 = value1, v2 = value2, t1 = tangent1, t2 = tangent2, s = amount, result;
    double sCubed = s * s * s;
    double sSquared = s * s;

    if (amount == 0.0)
        result = value1;
    else if (amount == 1.0)
        result = value2;
    else
        result = (2 * v1 - 2 * v2 + t2 + t1) * sCubed +
        (3 * v2 - 3 * v1 - 2 * t1 - t2) * sSquared +
        t1 * s +
        v1;
    return result;
}

constexpr bool DLLEXPORT Engine3DRadSpace::Math::AABB(float p1, float w1, float p2, float w2)
{
    return p1 <= p2 + w2 && p1 + w1 >= p2;
}

constexpr bool DLLEXPORT Engine3DRadSpace::Math::AABB(double p1, double w1, double p2, double w2)
{
    return p1 <= p2 + w2 && p1 + w1 >= p2;
}

constexpr double DLLEXPORT Engine3DRadSpace::Math::SmoothStep(double value1, double value2, double amount)
{
    double result = std::clamp(amount, 0.0, 1.0);
    result = Hermite(value1, 0, value2, 0, result);

    return result;
}

constexpr double DLLEXPORT Engine3DRadSpace::Math::ReLU(double x)
{
    return std::max(0.0, x);
}

constexpr bool DLLEXPORT Engine3DRadSpace::Math::WithinEpsilon(float a, float b)
{
    float num = a - b;
    return ((-1.401298E-45f <= num) && (num <= std::numeric_limits<float>::epsilon()));
}
