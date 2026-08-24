#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector2;
	struct Quaternion;
	/// <summary>
	///	Represents a row-major 3x3 matrix. Used for 2D affine transformations and 3D rotations.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Matrix3x3
	{
		float M11, M12, M13;
		float M21, M22, M23;
		float M31, M32, M33;

		/// <summary>
		/// Creates a matrix with the specified values. If no values are provided, it creates an identity matrix.
		/// </summary>
		/// <param name="m11">The value for the first row, first column.</param>
		/// <param name="m12">The value for the first row, second column.</param>
		/// <param name="m13">The value for the first row, third column.</param>
		/// <param name="m21">The value for the second row, first column.</param>
		/// <param name="m22">The value for the second row, second column.</param>
		/// <param name="m23">The value for the second row, third column.</param>
		/// <param name="m31">The value for the third row, first column.</param>
		/// <param name="m32">The value for the third row, second column.</param>
		/// <param name="m33">The value for the third row, third column.</param>
		explicit Matrix3x3(	float m11 = 1, float m12 = 0, float m13 = 0,
							float m21 = 0, float m22 = 1, float m23 = 0,
							float m31 = 0, float m32 = 0, float m33 = 1);
		/// <summary>
		///	Creates a matrix from an array of 9 floats.
		/// </summary>
		/// <param name="m"></param>
		explicit Matrix3x3(float m[9]);

		/// <summary>
		/// Creates a 2D translation matrix.
		/// </summary>
		/// <param name="t">The translation vector.</param>
		/// <returns>The resulting translation matrix.</returns>
		static Matrix3x3 CreateTranslation(const Vector2 &t);
		/// <summary>
		/// Creates a 2D scaling matrix.
		/// </summary>
		/// <param name="s">The scaling vector.</param>
		/// <returns>The resulting scaling matrix.</returns>
		static Matrix3x3 CreateScale(const Vector2 &s);
		/// <summary>
		/// Creates a 2D rotation matrix.
		/// </summary>
		/// <param name="theta">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix3x3 CreateRotation2D(float theta);
		/// <summary>
		/// Creates a 2D skewing matrix.
		/// </summary>
		/// <param name="skewing">The skewing vector.</param>
		/// <returns>The resulting skewing matrix.</returns>
		static Matrix3x3 Create2DSkewing(const Vector2& skewing);

		/// <summary>
		/// Creates a rotation matrix around the X-axis.
		/// </summary>
		/// <param name="alpha">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix3x3 CreateRotationX(float alpha);
		/// <summary>
		/// Creates a rotation matrix around the Y-axis.
		/// </summary>
		/// <param name="beta">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix3x3 CreateRotationY(float beta);
		/// <summary>
		/// Creates a rotation matrix around the Z-axis.
		/// </summary>
		/// <param name="gamma">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix3x3 CreateRotationZ(float gamma);

		/// <summary>
		/// Creates a rotation matrix from a quaternion.
		/// </summary>
		/// <param name="q">The quaternion representing the rotation.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix3x3 CreateFromQuaternion(const Quaternion& q);

		/// <summary>
		/// Returns the trace of this matrix.
		/// </summary>
		/// <returns>M11+ M22 + M33</returns>
		float Trace() const noexcept;
		/// <summary>
		/// Returns the determinant of this matrix.
		/// </summary>
		/// <returns>The determinant of the matrix.</returns>
		float Determinant() const noexcept;

		/// <summary>
		/// Returns a reference to the element at the specified index in the matrix, allowing for both reading and writing.
		/// </summary>
		/// <param name="index">Index. between 0 and 8</param>
		/// <returns>A reference to the element at the specified index.</returns>
		float& operator[](unsigned index);

		/// <summary>
		/// Hadamard multiplication (element-wise multiplication) of this matrix with another matrix.
		/// </summary>
		/// <param name="m">The matrix to multiply with.</param>
		/// <returns>The resulting matrix after Hadamard multiplication.</returns>
		Matrix3x3& Hadamard(const Matrix3x3& m);
		/// <summary>
		/// Hadamard multiplication (element-wise multiplication) of two matrices.
		/// </summary>
		/// <param name="a">The first matrix.</param>
		/// <param name="b">The second matrix.</param>
		/// <returns>The resulting matrix after Hadamard multiplication.</returns>
		static Matrix3x3 Hadamard(const Matrix3x3& a, const Matrix3x3& b);
		/// <summary>
		/// Adds this matrix to another matrix and returns the result.
		/// </summary>
		/// <param name="m">The matrix to add.</param>
		/// <returns>The resulting matrix after addition.</returns>
		Matrix3x3 operator+(const Matrix3x3& m) const noexcept;

		/// <summary>
		/// Adds another matrix to this matrix in-place.
		/// </summary>
		/// <param name="m">The matrix to add.</param>
		/// <returns>A reference to this matrix after addition.</returns>
		Matrix3x3& operator+=(const Matrix3x3& m) noexcept;

		/// <summary>
		/// Negates this matrix, returning a matrix with all elements negated.
		/// </summary>
		/// <returns>The resulting negated matrix.</returns>
		Matrix3x3 operator-() const noexcept;
		/// <summary>
		/// Subtracts another matrix from this matrix and returns the result.
		/// </summary>
		/// <param name="m">The matrix to subtract.</param>
		/// <returns>The resulting matrix after subtraction.</returns>
		Matrix3x3 operator-(const Matrix3x3& m) const noexcept;
		/// <summary>
		/// Subtracts another matrix from this matrix in-place.
		/// </summary>
		/// <param name="m">The matrix to subtract.</param>
		/// <returns>A reference to this matrix after subtraction.</returns>
		Matrix3x3& operator-=(const Matrix3x3& m) noexcept;

		/// <summary>
		/// Multiplies this matrix with another matrix (matrix product) and returns the result.
		/// </summary>
		/// <param name="m">The matrix to multiply with.</param>
		/// <returns>The resulting matrix after multiplication.</returns>
		Matrix3x3 operator*(const Matrix3x3& m) const noexcept;
		/// <summary>
		/// Multiplies this matrix with another matrix (matrix product) in-place.
		/// </summary>
		/// <param name="m">The matrix to multiply with.</param>
		/// <returns>A reference to this matrix after multiplication.</returns>
		Matrix3x3& operator*=(const Matrix3x3& m) noexcept;

		/// <summary>
		/// Multiplies this matrix by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar value to multiply with.</param>
		/// <returns>The resulting scaled matrix.</returns>
		Matrix3x3 operator*(float s) const noexcept;
		/// <summary>
		/// Multiplies this matrix by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar value to multiply with.</param>
		/// <returns>A reference to this matrix after scaling.</returns>
		Matrix3x3& operator*=(float s) noexcept;

		/// <summary>
		/// Divides this matrix by a scalar and returns the result.
		/// </summary>
		/// <param name="s">The scalar value to divide by.</param>
		/// <returns>The resulting divided matrix.</returns>
		Matrix3x3 operator/(float s) const;
		/// <summary>
		/// Divides this matrix by a scalar in-place.
		/// </summary>
		/// <param name="s">The scalar value to divide by.</param>
		/// <returns>A reference to this matrix after division.</returns>
		Matrix3x3& operator/=(float s);
	};

	Matrix3x3 E3DRSP_MATH_EXPORT operator *(float s, const Matrix3x3& m) noexcept;
	Matrix3x3 E3DRSP_MATH_EXPORT operator /(float s, const Matrix3x3& m);
}