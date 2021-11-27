#pragma once
#include "Globals.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a 2D point. Used to represent 2D screen and sprite coordinates.
	/// </summary>
	struct DLLEXPORT Point
	{
		/// <summary>
		/// The X component of the point
		/// </summary>
		int X;
		/// <summary>
		/// The Y component of the point
		/// </summary>
		int Y;
		/// <summary>
		/// Default constructor.
		/// </summary>
		Point() = default;
		/// <summary>
		/// Constructs a point from the given X and Y values.
		/// </summary>
		/// <param name="x">X component</param>
		/// <param name="y">Y component</param>
		Point(int x, int y) : X(x), Y(y) {};

		/// <summary>
		/// Returns a null point
		/// </summary>
		/// <returns></returns>
		static Point Zero();
		/// <summary>
		/// Returns a point with coordinates (1,1).
		/// </summary>
		/// <returns></returns>
		static Point One();

		/// <summary>
		/// Sums two points
		/// </summary>
		/// <param name="p"> point</param>
		/// <returns></returns>
		Point operator +=(const Point& p);
		/// <summary>
		/// Substracts two points
		/// </summary>
		/// <param name="p">point</param>
		/// <returns></returns>
		Point operator -=(const Point& p);
		/// <summary>
		/// Multiplies two points
		/// </summary>
		/// <param name="p">point</param>
		/// <returns></returns>
		Point operator *=(const Point& p);
		/// <summary>
		/// Divides two points
		/// </summary>
		/// <param name="p">point</param>
		/// <returns></returns>
		Point operator /=(const Point& p);

		/// <summary>
		/// Sums two points
		/// </summary>
		/// <param name="a">point</param>
		/// <param name="b">point</param>
		/// <returns></returns>
		friend DLLEXPORT Point operator +(const Point& a, const Point& b);
		/// <summary>
		/// Substracts two points
		/// </summary>
		/// <param name="a">point</param>
		/// <param name="b">point</param>
		/// <returns></returns>
		friend DLLEXPORT Point operator -(const Point& a, const Point& b);
		/// <summary>
		/// Multiplies two points
		/// </summary>
		/// <param name="a">point</param>
		/// <param name="b">point</param>
		/// <returns></returns>
		friend DLLEXPORT Point operator *(const Point& a, const Point& b);
		/// <summary>
		/// Divides two points
		/// </summary>
		/// <param name="a">point</param>
		/// <param name="b">point</param>
		/// <returns></returns>
		friend DLLEXPORT Point operator /(const Point& a, const Point& b);
		/// <summary>
		/// Multiplies a point by a scalar.
		/// </summary>
		/// <param name="s">scalar value</param>
		/// <param name="p">point</param>
		/// <returns></returns>
		friend DLLEXPORT Point operator *(float s, const Point& p);
	};
}
