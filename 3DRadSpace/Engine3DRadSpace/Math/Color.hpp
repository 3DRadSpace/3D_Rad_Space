#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	/// <summary>
	/// Represents a Unit RGBA color.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Color
	{
		/// <summary>
		/// Red channel. Values are in the range [0, 1].
		/// </summary>
		float R;
		/// <summary>
		/// Green channel. Values are in the range [0, 1].
		/// </summary>
		float G;
		/// <summary>
		/// Blue channel. Values are in the range [0, 1].
		/// </summary>
		float B;
		/// <summary>
		/// Alpha(Transparency) channel. Values are in the range [0, 1].
		/// </summary>
		float A;

		/// <summary>
		/// Constructs a color from 4 components.
		/// </summary>
		/// <param name="r">Red component.</param>
		/// <param name="g">Green component.</param>
		/// <param name="b">Blue component.</param>
		/// <param name="a">Transparency component, called alpha.</param>
		constexpr Color(float r = 0.00f, float g = 0.00f, float b = 0.00f, float a = 1.00f) : R(r), G(g), B(b), A(a) {};
		/// <summary>
		/// Constructs a color from RBGA values made of unsigned 8-bytes numbers.
		/// </summary>
		/// <param name="r">Red component.</param>
		/// <param name="g">Green component.</param>
		/// <param name="b">Blue component.</param>
		/// <param name="a">Transparency component, called alpha.</param>
		/// <returns>Unit RGBA color.</returns>
		static Color FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		/// <summary>
		/// Comptes a Hadamard product between two colors.
		/// </summary>
		/// <param name="c">Color</param>
		/// <returns>*this * c</returns>
		constexpr Color operator *(const Color& c) const noexcept;
		/// <summary>
		/// Computes a Hadamard product between two colors.
		/// </summary>
		/// <param name="c">A color.</param>
		/// <returns>this multiplied by c</returns>
		constexpr Color& operator *=(const Color& c) noexcept;

		/// <summary>
		/// Gets the color component at the given index. 0 = R, 1 = G, 2 = B, 3 = A.
		/// </summary>
		/// <param name="i">The index of the color component.</param>
		/// <returns>The value of the color component at the given index.</returns>
		constexpr float operator[](int i) const;

		friend auto operator <=>(const Color& a, const Color& b) noexcept = default;
	};

	/// <summary>
	/// This namespace contains a set of predefined colors.
	/// </summary>
	namespace Colors
	{
		constexpr Color White = {1.0f, 1.0f, 1.0f, 1.0f};
		constexpr Color Red = {1.0f, 0.0f, 0.0f, 1.0f};
		constexpr Color Green = {0.0f, 1.0f, 0.0f, 1.0f};
		constexpr Color Blue = {0.0f, 0.0f, 1.0f, 1.0f};
		constexpr Color Black = {0.0f, 0.0f, 0.0f, 1.0f};
		constexpr Color Gray = {0.5f, 0.5f, 0.5f, 1.0f};
		constexpr Color DarkGray = {0.25f, 0.25f, 0.25f, 1.0f};
		constexpr Color Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		constexpr Color Mangenta = { 1.0f, 0.0f, 1.0f, 1.0f };
		constexpr Color Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
		constexpr Color CornflowerBlue = {0.392f, 0.584f, 0.929f, 1.0f};
		constexpr Color Orange = { 1.0f, 0.25f, 0.0f, 1.0f };
		constexpr Color Pink = { 1.0f, 0.75f, 0.8f, 1.0f };
		
		constexpr Color DarkRed = { 0.5f, 0.0f, 0.0f, 1.0f };
		constexpr Color DarkGreen = { 0.0f, 0.5f, 0.0f, 1.0f };
		constexpr Color DarkBlue = { 0.0f, 0.0f, 0.5f, 1.0f };
		constexpr Color DarkYellow = { 0.5f, 0.5f, 0.0f, 1.0f };
		constexpr Color DarkCyan = { 0.0f, 0.5f, 0.5f, 1.0f };
		constexpr Color DarkMagenta = { 0.5f, 0.0f, 0.5f, 1.0f };
		
		constexpr Color LightRed = { 1.0f, 0.5f, 0.5f, 1.0f };
		constexpr Color LightGreen = { 0.5f, 1.0f, 0.5f, 1.0f };
		constexpr Color LightBlue = { 0.5f, 0.5f, 1.0f, 1.0f };
		constexpr Color LightPink = { 1.0f, 0.5f, 1.0f, 1.0f };
		constexpr Color LightCyan = { 0.5f, 1.0f, 1.0f, 1.0f };
		constexpr Color LightMagenta = { 1.0f, 0.5f, 1.0f, 1.0f };
		constexpr Color LightYellow = { 1.0f, 1.0f, 0.5f, 1.0f };
		constexpr Color LightOrange = { 1.0f, 0.647f, 0.0f, 1.0f };
		constexpr Color LightGray = { 0.75f, 0.75f, 0.75f, 1.0f };

		//TODO: Add more colors.
	};
}

namespace std
{
	template<>
	struct formatter<Engine3DRadSpace::Math::Color>
	{
		constexpr auto parse(std::format_parse_context& ctx) {
			return ctx.begin();
		}

		auto format(const Engine3DRadSpace::Math::Color& c, std::format_context& ctx) const {
			return std::format_to(ctx.out(), "({}, {}, {}, {})", c.R, c.G, c.B, c.A);
		}

	};
}