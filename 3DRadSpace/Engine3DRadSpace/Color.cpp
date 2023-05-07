#include "Color.hpp"
#include <stdexcept>

using namespace Engine3DRadSpace;

Color Engine3DRadSpace::Colors::White = { 1.0f,1.0f,1.0f,1.0f };
Color Engine3DRadSpace::Colors::Red = { 1.0f,0.0f,0.0f,1.0f };
Color Engine3DRadSpace::Colors::Green = { 0.0f,1.0f,0.0f,1.0f };
Color Engine3DRadSpace::Colors::Blue = { 0.0f,0.0f,1.0f,1.0f };
Color Engine3DRadSpace::Colors::Black = { 0.0f,0.0f,0.0f,1.0f };
Color Engine3DRadSpace::Colors::Gray = { 0.5f, 0.5f, 0.5f, 1.0f };
Color Engine3DRadSpace::Colors::DarkGray = { 0.5f, 0.5f, 0.5f, 1.0f };

Color Engine3DRadSpace::Color::FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return Color( r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

float Engine3DRadSpace::Color::operator[](int i)
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
