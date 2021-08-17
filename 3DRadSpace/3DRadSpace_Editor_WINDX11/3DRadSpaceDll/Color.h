#pragma once
#include "Globals.h"

struct ColorShader
{
	float R, G, B, A;
};

struct DLLEXPORT Color
{
	uint8_t R, G, B, A;
	Color() : R(0), G(0), B(0), A(255) {};
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R(r), G(g), B(b), A(a) {};
	Color(float r,float g,float b,float a): R((uint8_t)(r*255)), G((uint8_t)(r * 255)), B((uint8_t)(r * 255)), A((uint8_t)(r * 255)) {}
	ColorShader Normalize();
};



