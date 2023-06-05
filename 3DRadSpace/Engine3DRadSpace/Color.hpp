#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	struct Color
	{
		float R;
		float G;
		float B;
		float A;

		Color(float r = 0.00f, float g = 0.00f, float b = 0.00f, float a = 1.00f) : R(r), G(g), B(b), A(a) {};

		static Color FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		auto operator <=>(const Color& c) const = default;

		float operator[](int i);
	};
	namespace Colors
	{
		extern Color White;
		extern Color Red;
		extern Color Green;
		extern Color Blue;
		extern Color Black;
		extern Color Gray;
		extern Color DarkGray;
	};
}
