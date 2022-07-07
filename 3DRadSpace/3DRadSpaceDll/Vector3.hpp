#pragma once
#include <cmath>
#include "Globals.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace Engine3DRadSpace
{
	struct DLLEXPORT Matrix;

	/// <summary>
	/// Represents a 3D vector
	/// </summary>
	struct DLLEXPORT Vector3
	{
		float X, Y, Z;

		/// <summary>
		/// Default constructor
		/// </summary>
		Vector3() = default;
		/// <summary>
		/// Constructs a 3D vector from the given components
		/// </summary>
		/// <param name="x">X component</param>
		/// <param name="y">Y component</param>
		/// <param name="z">Z component</param>
		Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

		/// <summary>
		/// Calulcates the lenght of the vector
		/// </summary>
		/// <returns></returns>
		float Lenght() const;
		/// <summary>
		/// Normalizez the vector
		/// </summary>
		void Normalize();
		/// <summary>
		/// Normalizez the given vector
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		static Vector3 Normalize(const Vector3& v);

		/// <summary>
		/// Calcaulates the dot product
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		float Dot(const Vector3& v);
		/// <summary>
		/// Returns the dot product of two vectors
		/// </summary>
		/// <param name="a">vector</param>
		/// <param name="b">vector</param>
		/// <returns></returns>
		static float Dot(const Vector3& a, const Vector3& b);

		/// <summary>
		/// Returns the cross product
		/// </summary>
		/// <param name="v">vector</param>
		/// <returns></returns>
		Vector3 Cross(const Vector3& v);
		/// <summary>
		/// Returns the cross product of two vectors
		/// </summary>
		/// <param name="a">vector</param>
		/// <param name="b">vector</param>
		/// <returns></returns>
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		/// <summary>
		/// Returns (1,0,0)
		/// </summary>
		/// <returns></returns>
		static Vector3 UnitX();
		/// <summary>
		/// Returns (0,1,0)
		/// </summary>
		/// <returns></returns>
		static Vector3 UnitY();
		/// <summary>
		/// Returns (0,0,1)
		/// </summary>
		/// <returns></returns>
		static Vector3 UnitZ();
		/// <summary>
		/// Returns a null vector
		/// </summary>
		/// <returns></returns>
		static Vector3 Zero();
		/// <summary>
		/// Returns (1,1,1)
		/// </summary>
		/// <returns></returns>
		static Vector3 One();
		/// <summary>
		/// Transforms a vector by a given matrix
		/// </summary>
		/// <param name="v">Vector</param>
		/// <param name="m">Matrix</param>
		/// <returns></returns>
		static Vector3 Transform(const Vector3& v, const Matrix& m);
		/// <summary>
		/// Rotates a vector with the given quaternion
		/// </summary>
		/// <param name="v">vector</param>
		/// <param name="q">quaternion</param>
		/// <returns></returns>
		static Vector3 Transform(const Vector3& v, const Quaternion& q);

	};

	/// <summary>
	/// Sums two vectors
	/// </summary>
	/// <param name="a">vector</param>
	/// <param name="b">vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator +(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Sums two vectors
	/// </summary>
	/// <param name="a">first vector</param>
	/// <param name="b">second vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator +=(Vector3& a, const Vector3& b);

	/// <summary>
	/// Substracts two vectors
	/// </summary>
	/// <param name="a">vector</param>
	/// <param name="b">vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator -(const Vector3& a, const Vector3& b);

	/// <summary>
	/// Flips the given vector vertically and horizontally
	/// </summary>
	/// <param name="a">vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator -(const Vector3& v);

	/// <summary>
	/// Substracts two vectors
	/// </summary>
	/// <param name="a">first vector</param>
	/// <param name="b">second vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator -=(Vector3& a, const Vector3& b);

	/// <summary>
	/// Multiplies a vector by a scalar
	/// </summary>
	/// <param name="f">scalar</param>
	/// <param name="v">vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator *(float f, const Vector3& v);

	/// <summary>
	/// Multiplies a vector by a scalar
	/// </summary>
	/// <param name="v">Vector</param>
	/// <param name="s">scalar</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator *=(Vector3& v, float s);

	/// <summary>
	/// Multiplies the vector by the inverse of the given scalar
	/// </summary>
	/// <param name="s">scalar inverse</param>
	/// <param name="v">vector</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator /(float s, const Vector3& v);

	/// <summary>
	/// Multiplies a vector by scalar of 1/f
	/// </summary>
	/// <param name="v">vector</param>
	/// <param name="f">scalar</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator /=(Vector3& v, float f);

	/// <summary>
	/// Transforms the given vector by the given matrix
	/// </summary>
	/// <param name="v">vector</param>
	/// <param name="m">matrix</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator *(const Vector3& v, const Matrix& m);

	/// <summary>
	/// Transforms the given vector by the given matrix
	/// </summary>
	/// <param name="v">vector</param>
	/// <param name="m">matrix</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator *=(Vector3& v, const Matrix& m);

	/// <summary>
	/// Rotates the vector with the given quaternion
	/// </summary>
	/// <param name="v">vector</param>
	/// <param name="q">quaterinion</param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator *(const Vector3& v, const Quaternion& q);

	/// <summary>
	/// Rotates the vector with the given quaterinon
	/// </summary>
	/// <param name="v"></param>
	/// <param name="q"></param>
	/// <returns></returns>
	Vector3 DLLEXPORT operator *=( Vector3& v, const Quaternion& q);

	bool DLLEXPORT operator ==(const Vector3& a, const Vector3& b);
	bool DLLEXPORT operator !=(const Vector3& a, const Vector3& b);
}