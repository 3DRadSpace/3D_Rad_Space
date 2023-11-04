#include "Color.hpp"

using namespace Engine3DRadSpace;

constexpr Color Color::FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return Color( r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

constexpr float Color::operator[](int i) const
{
	switch (i)
	{
	case 0: return R;
	case 1: return G;
	case 2: return B;
	case 3: return A;
	default: throw std::out_of_range(" 0 <= i <= 3");
	}
}
