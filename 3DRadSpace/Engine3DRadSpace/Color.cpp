#include "Color.hpp"

using namespace Engine3DRadSpace;

Color Engine3DRadSpace::Colors::White = { 1.0f,1.0f,1.0f,1.0f };
Color Engine3DRadSpace::Colors::Red = { 1.0f,0.0f,0.0f,1.0f };
Color Engine3DRadSpace::Colors::Green = { 0.0f,1.0f,0.0f,1.0f };
Color Engine3DRadSpace::Colors::Blue = { 0.0f,0.0f,1.0f,1.0f };
Color Engine3DRadSpace::Colors::Black = { 0.0f,0.0f,0.0f,1.0f };
Color Engine3DRadSpace::Colors::Gray = { 0.5f, 0.5f, 0.5f, 1.0f };

Color Engine3DRadSpace::Color::FromRGB(int r, int g, int b, int a)
{
	return Color( r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
