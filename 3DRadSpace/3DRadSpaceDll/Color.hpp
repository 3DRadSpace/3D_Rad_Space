#pragma once
#include "Globals.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a normalized RGBA color. Used very often in shaders.
	/// </summary>
	struct ColorShader
	{
		ColorShader() = default;
		ColorShader(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {};
		float R, G, B, A;
	};
	/// <summary>
	/// Represents an unnormalized RGBA color. Each color value ranges from 0 to 255.
	/// </summary>
	struct DLLEXPORT Color
	{
		/// <summary>
		/// The red component of the color. Ranges from 0 to 255.
		/// </summary>
		uint8_t R;
		/// <summary>
		/// The green component of the color. Ranges from 0 to 255.
		/// </summary>
		uint8_t G;
		/// <summary>
		/// The blue component of the color. Ranges from 0 to 255.
		/// </summary>
		uint8_t B;
		/// <summary>
		/// The transparency of the color. Ranges from 0 (invisible) to 255 (not transparent at all).
		/// </summary>
		uint8_t A;
		/// <summary>
		/// Default constructor. Defines a non-transparent black color.
		/// </summary>
		Color() : R(0), G(0), B(0), A(255) {};
		/// <summary>
		/// Constructs a color from the given RGBA vlaues.
		/// </summary>
		/// <param name="r">The red component</param>
		/// <param name="g">The green component</param>
		/// <param name="b">The blue component</param>
		/// <param name="a">The alpha component</param>
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R(r), G(g), B(b), A(a) {};
		/// <summary>
		/// Constructs a color from a normalized RGBA color.
		/// </summary>
		/// <param name="r">Normalized red component</param>
		/// <param name="g">Normalized green component</param>
		/// <param name="b">Normalized blue component</param>
		/// <param name="a">Normalized alpha component</param>
		Color(float r, float g, float b, float a) : R((uint8_t)(r * 255)), G((uint8_t)(r * 255)), B((uint8_t)(r * 255)), A((uint8_t)(r * 255)) {}
		/// <summary>
		/// Creates a normalized color
		/// </summary>
		/// <returns>A normalized color</returns>
		ColorShader Normalize();
	};

	bool DLLEXPORT operator==(const ColorShader& a, const ColorShader& b);
	bool DLLEXPORT operator==(const Color& a, const Color& b);

	bool DLLEXPORT operator!=(const ColorShader& a, const ColorShader& b);
	bool DLLEXPORT operator!=(const Color& a, const Color& b);
}


