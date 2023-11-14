#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	struct DLLEXPORT Color
	{
		float R;
		float G;
		float B;
		float A;

		constexpr Color(float r = 0.00f, float g = 0.00f, float b = 0.00f, float a = 1.00f) : R(r), G(g), B(b), A(a) {};
		constexpr static Color FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		constexpr Color operator *(const Color& c) const;
		constexpr Color& operator *=(const Color& c);

		constexpr float operator[](int i) const;

		constexpr auto operator<=>(const Color& c) const = default;
	};
	namespace Colors
	{
		constexpr Color White = {1.0f,1.0f,1.0f,1.0f};
		constexpr Color Red = {1.0f,0.0f,0.0f,1.0f};
		constexpr Color Green = {0.0f,1.0f,0.0f,1.0f};
		constexpr Color Blue = {0.0f,0.0f,1.0f,1.0f};
		constexpr Color Black = {0.0f,0.0f,0.0f,1.0f};
		constexpr Color Gray = {0.5f, 0.5f, 0.5f, 1.0f};
		constexpr Color DarkGray = {0.25f, 0.25f, 0.25f, 1.0f};
	};
}
