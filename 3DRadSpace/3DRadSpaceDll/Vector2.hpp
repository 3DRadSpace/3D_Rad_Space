#pragma once
#include "Globals.hpp"
#include "Matrix.hpp"
#include "ComplexNumber.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a 2D vector
	/// </summary>
	struct DLLEXPORT Vector2
	{
		/// <summary>
		/// The vector X component
		/// </summary>
		float X;
		/// <summary>
		/// The vector Y component
		/// </summary>
		float Y;
		/// <summary>
		/// Default constructor
		/// </summary>
		Vector2() = default;
		/// <summary>
		/// Constructs a vector from the given components
		/// </summary>
		/// <param name="x">X component</param>
		/// <param name="y">Y component</param>
		Vector2(float x, float y) : X(x), Y(y) {};

		/// <summary>
		/// Returns a null vector
		/// </summary>
		/// <returns></returns>
		static Vector2 Zero();
		/// <summary>
		/// Returns (1,0,0)
		/// </summary>
		/// <returns></returns>
		static Vector2 UnitX();
		/// <summary>
		/// Returns (0,1,0)
		/// </summary>
		/// <returns></returns>
		static Vector2 UnitY();
		/// <summary>
		/// Returns (0,0,1)
		/// </summary>
		/// <returns></returns>
		static Vector2 One();

		/// <summary>
		/// Returns the vector lenght
		/// </summary>
		/// <returns></returns>
		float Lenght() const;
		/// <summary>
		/// Returns the lenght of the given vector
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		static float Lenght(const Vector2& v);

		/// <summary>
		/// Returns the dot product of the given vector
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		float Dot(const Vector2& v) const;
		/// <summary>
		/// Returns the dot product between two vectors
		/// </summary>
		/// <param name="a">vector</param>
		/// <param name="b">vector</param>
		/// <returns></returns>
		static float Dot(const Vector2& a, const Vector2& b);

		/// <summary>
		/// Multiplies a vector by a scalar
		/// </summary>
		/// <param name="scalar">scalar</param>
		/// <returns></returns>
		Vector2 operator *=(float scalar);
		/// <summary>
		/// Multiplies a vector by a matrix
		/// </summary>
		/// <param name="m">matrix</param>
		/// <returns></returns>
		Vector2 operator *=(const Matrix& m);
		/// <summary>
		/// Multiplies a 2D vector by a complex number 
		/// </summary>
		/// <param name="z">complex number</param>
		/// <returns></returns>
		Vector2 operator *=(const ComplexNumber& z);

	};
	/// <summary>
	/// Sums two vectors
	/// </summary>
	/// <param name="v">vector</param>
	/// <returns></returns>
	Vector2 operator +(const Vector2& a,const Vector2 &b);
	/// <summary>
	/// Substracts two vectors
	/// </summary>
	/// <param name="v">vector</param>
	/// <returns></returns>
	Vector2 operator -(const Vector2& a, const Vector2& b);

	/// <summary>
	/// Multiplies a vector by a scalar
	/// </summary>
	/// <param name="scalar">scalar</param>
	/// <returns></returns>
	Vector2 operator *=(const Vector2& v, float scalar);
	/// <summary>
	/// Multiplies a vector by a matrix
	/// </summary>
	/// <param name="m">matrix</param>
	/// <returns></returns>
	Vector2 operator *=(const Vector2& v, const Matrix& m);
	/// <summary>
	/// Multiplies a 2D vector by a complex number 
	/// </summary>
	/// <param name="z">complex number</param>
	/// <returns></returns>
	Vector2 operator *=(const Vector2& v, const ComplexNumber& z);
}
