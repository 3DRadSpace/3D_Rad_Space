#include "Color.hpp"

Engine3DRadSpace::ColorShader Engine3DRadSpace::Color::Normalize()
{
    return { ((float)this->R) / 255, ((float)this->G) / 255,((float)this->B) / 255, ((float)this->A) / 255 };
}

bool Engine3DRadSpace::operator==(const ColorShader& a, const ColorShader& b)
{
    return a.R == b.R && a.G == b.G && a.B == b.B && a.A == b.A;
}

bool Engine3DRadSpace::operator==(const Color& a, const Color& b)
{
    return a.R == b.R && a.G == b.G && a.B == b.B && a.A == b.A;
}

bool Engine3DRadSpace::operator!=(const ColorShader& a, const ColorShader& b)
{
    return a.R != b.R && a.G != b.G && a.B != b.B && a.A != b.A;
}

bool Engine3DRadSpace::operator!=(const Color& a, const Color& b)
{
    return a.R != b.R && a.G != b.G && a.B != b.B && a.A != b.A;
}
