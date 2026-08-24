#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		/// <summary>
		/// Represents an axis-aligned rectangle in 2D space, defined by its top-left corner (X, Y) and its dimensions (Width, Height).
		/// </summary>
		struct E3DRSP_MATH_EXPORT Rectangle
		{
			/// <summary>
			/// Constructs an rectangle with the specified top-left corner and dimensions. If no values are provided, it creates a rectangle at the origin with zero width and height.
			/// </summary>
			/// <param name="x">The X coordinate of the top-left corner.</param>
			/// <param name="y">The Y coordinate of the top-left corner.</param>
			/// <param name="w">The width of the rectangle.</param>
			/// <param name="h">The height of the rectangle.</param>
			explicit constexpr Rectangle(int x = 0, int y = 0, int w = 0, int h = 0) :
				X(x),
				Y(y),
				Width(w),
				Height(h)
			{
			}
			/// <summary>
			/// Creates a rectangle from two points, where 'min' is the top-left corner and 'max' is the bottom-right corner. The width and height are calculated based on these points.
			/// </summary>
			/// <param name="min">Minimal point (top-left corner)</param>
			/// <param name="max">Maximum point (bottom-right corner)</param>
			explicit Rectangle(Point min, Point max) :
				X(min.X),
				Y(min.Y),
				Width(max.X - min.X),
				Height(max.Y - min.Y)
			{
			}

			/// <summary>
			/// The X coordinate of the top-left corner of the rectangle.
			/// </summary>
			int X;
			/// <summary>
			///	The Y coordinate of the top-left corner of the rectangle.
			/// </summary>
			int Y;
			/// <summary>
			/// The width of this rectangle.
			/// </summary>
			int Width;
			/// <summary>
			///	The height of this rectangle.
			/// </summary>
			int Height;

			/// <summary>
			/// Returns the coordinates of the top-left corner of the rectangle.
			/// </summary>
			/// <returns>The top-left corner as a Point.</returns>
			Point TopLeft() const;
			/// <summary>
			///	Returns the top-right corner of the rectangle as a Point. The X coordinate is calculated as X + Width, and the Y coordinate remains the same as Y.
			/// </summary>
			/// <returns>The top-right corner as a Point.</returns>
			Point TopRight() const;
			/// <summary>
			/// Returns the bottom-left corner of the rectangle as a Point. The X coordinate remains the same as X, and the Y coordinate is calculated as Y + Height.
			/// </summary>
			/// <returns>The bottom-left corner as a Point.</returns>
			Point BottomLeft() const;
			/// <summary>
			/// Returns the bottom-right corner of the rectangle as a Point. The X coordinate is calculated as X + Width, and the Y coordinate is calculated as Y + Height.
			/// </summary>
			/// <returns>The bottom-right corner as a Point.</returns>
			Point BottomRight() const;
			/// <summary>
			/// Returns the center point of the rectangle.
			/// </summary>
			/// <returns>The center point as a Point.</returns>
			Point Center() const;

			/// <summary>
			/// Determines whether the specified point is contained within the rectangle.
			/// </summary>
			/// <param name="p">The point to test.</param>
			/// <returns>True if the point is within the rectangle; otherwise, false.</returns>
			bool Contains(Point p) const noexcept;

			/// <summary>
			/// Calculates the area of the rectangle.
			/// </summary>
			/// <returns>The area of the rectangle.</returns>
			int Area() const noexcept;

			/// <summary>
			/// Checks if this rectangle is equal to another rectangle. Two rectangles are considered equal if they have the same top-left corner and dimensions.
			/// </summary>
			/// <param name="r">The rectangle to compare with.</param>
			/// <returns>True if the rectangles are equal; otherwise, false.</returns>
			bool operator ==(const Rectangle& r) const = default;
			/// <summary>
			/// Checks if this rectangle is not equal to another rectangle. Two rectangles are considered not equal if they differ in either their top-left corner or dimensions.
			/// </summary>
			/// <param name="r">The rectangle to compare with.</param>
			/// <returns>True if the rectangles are not equal; otherwise, false.</returns>
			bool operator !=(const Rectangle& r) const = default;
		};

		/// <summary>
		/// Floating point version of the Rectangle structure, representing an axis-aligned rectangle in 2D space with floating-point precision. It is defined by its top-left corner (X, Y) and its dimensions (Width, Height).
		/// </summary>
		struct E3DRSP_MATH_EXPORT RectangleF
		{
			/// <summary>
			/// Constructs an axis-aligned rectangle with the specified top-left corner and dimensions. If no values are provided, it creates a rectangle at the origin with zero width and height.
			/// </summary>
			/// <param name="x">The X coordinate of the top-left corner of the rectangle.</param>
			/// <param name="y">The Y coordinate of the top-left corner of the rectangle.</param>
			/// <param name="w">The width of the rectangle.</param>
			/// <param name="h">The height of the rectangle.</param>
			explicit constexpr RectangleF(float x = 0, float y = 0, float w = 0, float h = 0) :
				X(x),
				Y(y),
				Width(w),
				Height(h)
			{
			}
			/// <summary>
			/// Creates a rectangle from two points, where 'min' is the top-left corner and 'max' is the bottom-right corner. The width and height are calculated based on these points.
			/// </summary>
			/// <param name="min">Minimal point (top-left corner)</param>
			/// <param name="max">Maximum point (bottom-right corner)</param>
			explicit RectangleF(Vector2 min, Vector2 max) :
				X(min.X),
				Y(min.Y),
				Width(max.X - min.X),
				Height(max.Y - min.Y)
			{
			}

			/// <summary>
			///	The X coordinate of the top-left corner of the rectangle.
			/// </summary>
			float X;
			/// <summary>
			///	The Y coordinate of the top-left corner of the rectangle.
			/// </summary>
			float Y;
			/// <summary>
			///	The width of the rectangle.
			/// </summary>
			float Width;
			/// <summary>
			///	The height of the rectangle.
			/// </summary>
			float Height;

			/// <summary>
			/// The top left corner of the rectangle.
			/// </summary>
			/// <returns>The top left corner.</returns>
			Vector2 TopLeft() const;
			/// <summary>
			/// The top right corner of the rectangle.
			/// </summary>
			/// <returns>The top right corner.</returns>
			Vector2 TopRight() const;
			/// <summary>
			/// The bottom left corner of the rectangle.
			/// </summary>
			/// <returns>The bottom left corner.</returns>
			Vector2 BottomLeft() const;
			/// <summary>
			/// The bottom right corner of the rectangle.
			/// </summary>
			/// <returns>The bottom right corner.</returns>
			Vector2 BottomRight() const;
			/// <summary>
			/// The center point of the rectangle.
			/// </summary>
			/// <returns>The center point.</returns>
			Vector2 Center() const;
			/// <summary>
			///	Does this rectangle contain the specified point p?
			/// </summary>
			/// <param name="p">Point in floating point precision.</param>
			/// <returns>True if the rectangle contains the point; otherwise, false.</returns>
			bool Contains(Vector2 p) const noexcept;
			/// <summary>
			///	Returns the area of the rectangle as a floating-point value.
			/// </summary>
			/// <returns>Width*Height</returns>
			float Area() const noexcept;
			/// <summary>
			/// Compares this rectangle with another rectangle for equality. Two rectangles are considered equal if they have the same top-left corner and dimensions.
			/// </summary>
			/// <param name="r">The rectangle to compare with.</param>
			/// <returns>True if the rectangles are equal; otherwise, false.</returns>
			bool operator ==(const RectangleF& r) const = default;
			/// <summary>
			/// Compares this rectangle with another rectangle for inequality. Two rectangles are considered not equal if they differ in either their top-left corner or dimensions.
			/// </summary>
			/// <param name="r">The rectangle to compare with.</param>
			/// <returns>True if the rectangles are not equal; otherwise, false.</returns>
			bool operator !=(const RectangleF& r) const = default;
		};
	}
}

