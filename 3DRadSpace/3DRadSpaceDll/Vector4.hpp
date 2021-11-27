#pragma once
#include <cmath>
#include "Globals.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"

namespace Engine3DRadSpace
{
	struct DLLEXPORT Matrix;

	struct DLLEXPORT Vector4
	{
		/// <summary>
		/// The X component of this 4D vector
		/// </summary>
		float X;
		/// <summary>
		/// The Y component of this 4D vector
		/// </summary>
		float Y;
		/// <summary>
		/// The Z component of this 4D vector
		/// </summary>
		float Z;
		/// <summary>
		/// The W component of this 4D vector
		/// </summary>
		float W;

		/// <summary>
		/// Default constructor
		/// </summary>
		Vector4() = default;
		/// <summary>
		/// Constructs a 4D vector with the given components
		/// </summary>
		/// <param name="x">X componetn</param>
		/// <param name="y">Y component</param>
		/// <param name="z">Z component</param>
		/// <param name="w">W component</param>
		Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

		/// <summary>
		/// Returns the vector lenght
		/// </summary>
		/// <returns></returns>
		float Lenght() const;
		/// <summary>
		/// Normalizez the vector
		/// </summary>
		void Normalize();
		/// <summary>
		/// Converts the given vector to a unit vector
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		static Vector4 Normalize(const Vector4& v);

		/// <summary>
		/// Sums two vectors
		/// </summary>
		/// <param name="v">vectir</param>
		/// <returns></returns>
		Vector4 operator +=(const Vector4& v);
		/// <summary>
		/// Substracts two vectors
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		Vector4 operator -=(const Vector4& v);
		/// <summary>
		/// Multiplies a vector by 1/f
		/// </summary>
		/// <param name="f">scalar</param>
		/// <returns></returns>
		Vector4 operator /=(float f);
		/// <summary>
		/// Multiplies a vector by a scalar
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector4 operator *=(float s);

		/// <summary>
		/// Returns the dot product of the vector with an other vector
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		float Dot(const Vector4& v);
		/// <summary>
		/// Returns the dot product of two vectors
		/// </summary>
		/// <param name="a">vector</param>
		/// <param name="b">vector</param>
		/// <returns></returns>
		static float Dot(const Vector4& a, const Vector4& b);
		/// <summary>
		/// Returns (1,0,0,0)
		/// </summary>
		/// <returns></returns>
		static Vector4 UnitX();
		/// <summary>
		/// Returns (0,1,0,0)
		/// </summary>
		/// <returns></returns>
		static Vector4 UnitY();
		/// <summary>
		/// Returns (0,0,1,0)
		/// </summary>
		/// <returns></returns>
		static Vector4 UnitZ();
		/// <summary>
		/// Returns (0,0,0,1)
		/// </summary>
		/// <returns></returns>
		static Vector4 UnitW();
		/// <summary>
		/// Returns a null vector
		/// </summary>
		/// <returns></returns>
		static Vector4 Zero();
		/// <summary>
		/// Returns (1,1,1,1)
		/// </summary>
		/// <returns></returns>
		static Vector4 One();
	};
	/// <summary>
	/// Sums two vectors
	/// </summary>
	/// <param name="a">vector</param>
	/// <param name="b">vector</param>
	/// <returns></returns>
	Engine3DRadSpace::Vector4 operator+(const Vector4& a, const Vector4& b);
	/// <summary>
	/// Substracts two vectors
	/// </summary>
	/// <param name="a">vector</param>
	/// <param name="b">vector</param>
	/// <returns></returns>
	Engine3DRadSpace::Vector4 operator-(const Vector4& a, const Vector4& b);
	/// <summary>
	/// Multiplies a vector by a scalar
	/// </summary>
	/// <param name="v">vector</param>
	/// <param name="s">scalar</param>
	/// <returns></returns>
	Engine3DRadSpace::Vector4 operator*(const Vector4& v, float s);
	/// <summary>
	/// Divides each vector's component by the given number
	/// </summary>
	/// <param name="v">vector</param>
	/// <param name="f">divizor</param>
	/// <returns></returns>
	Engine3DRadSpace::Vector4 operator/(const Vector4& v, float f);
}