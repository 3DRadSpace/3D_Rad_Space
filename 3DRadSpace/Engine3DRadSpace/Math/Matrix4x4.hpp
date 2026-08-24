#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;
	struct Quaternion;
	struct Point;

	/// <summary>
	/// Represents a row-major 4x4 matrix. Used for 3D affine transformations, rotations, and projections.
	/// </summary>
	struct E3DRSP_MATH_EXPORT Matrix4x4
	{
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;

		/// <summary>
		/// Creates a matrix from an array of 16 floats.
		/// </summary>
		/// <param name="m">The array containing the 16 matrix elements in row-major order.</param>
		constexpr explicit Matrix4x4(float m[16]);
		/// <summary>
		/// Creates a matrix with the specified values. If no values are provided, it creates an identity matrix.
		/// </summary>
		/// <param name="m11">The value for the first row, first column.</param>
		/// <param name="m12">The value for the first row, second column.</param>
		/// <param name="m13">The value for the first row, third column.</param>
		/// <param name="m14">The value for the first row, fourth column.</param>
		/// <param name="m21">The value for the second row, first column.</param>
		/// <param name="m22">The value for the second row, second column.</param>
		/// <param name="m23">The value for the second row, third column.</param>
		/// <param name="m24">The value for the second row, fourth column.</param>
		/// <param name="m31">The value for the third row, first column.</param>
		/// <param name="m32">The value for the third row, second column.</param>
		/// <param name="m33">The value for the third row, third column.</param>
		/// <param name="m34">The value for the third row, fourth column.</param>
		/// <param name="m41">The value for the fourth row, first column.</param>
		/// <param name="m42">The value for the fourth row, second column.</param>
		/// <param name="m43">The value for the fourth row, third column.</param>
		/// <param name="m44">The value for the fourth row, fourth column.</param>
		constexpr explicit Matrix4x4(
			float m11 = 1, float m12 = 0, float m13 = 0, float m14 = 0,
			float m21 = 0, float m22 = 1, float m23 = 0, float m24 = 0,
			float m31 = 0, float m32 = 0, float m33 = 1, float m34 = 0,
			float m41 = 0, float m42 = 0, float m43 = 0, float m44 = 1
		);

		/// <summary>
		/// Creates a 3D translation matrix.
		/// </summary>
		/// <param name="pos">The translation vector.</param>
		/// <returns>The resulting translation matrix.</returns>
		static Matrix4x4 CreateTranslation(const Vector3 &pos);
		/// <summary>
		/// Creates a 3D scaling matrix.
		/// </summary>
		/// <param name="scale">The scaling vector.</param>
		/// <returns>The resulting scaling matrix.</returns>
		static Matrix4x4 CreateScale(const Vector3 &scale);

		/// <summary>
		/// Creates a rotation matrix around the X-axis.
		/// </summary>
		/// <param name="theta">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix4x4 CreateRotationX(float theta);
		/// <summary>
		/// Creates a rotation matrix around the Y-axis.
		/// </summary>
		/// <param name="theta">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix4x4 CreateRotationY(float theta);
		/// <summary>
		/// Creates a rotation matrix around the Z-axis.
		/// </summary>
		/// <param name="theta">The rotation angle in radians.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix4x4 CreateRotationZ(float theta);
		/// <summary>
		/// Creates a rotation matrix from a quaternion.
		/// </summary>
		/// <param name="q">The quaternion representing the rotation.</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix4x4 CreateFromQuaternion(const Quaternion& q);
		/// <summary>
		/// Creates a rotation matrix from yaw, pitch, and roll angles.
		/// </summary>
		/// <param name="yaw">The yaw angle in radians (rotation around the Y-axis).</param>
		/// <param name="pitch">The pitch angle in radians (rotation around the X-axis).</param>
		/// <param name="roll">The roll angle in radians (rotation around the Z-axis).</param>
		/// <returns>The resulting rotation matrix.</returns>
		static Matrix4x4 CreateRotationYawPitchRoll(float yaw, float pitch, float roll);

		/// <summary>
		/// Creates a right-hand look at view matrix.
		/// </summary>
		/// <param name="pos">Camera position</param>
		/// <param name="look_at">Camera look direction</param>
		/// <param name="up_dir">Camera normal</param>
		/// <returns>RH View matrix</returns>
		static Matrix4x4 CreateLookAtView(const Vector3 &pos,const Vector3 &look_at,const Vector3 &up_dir);

		/// <summary>
		/// Creates a right-handed perspective projection matrix.
		/// </summary>
		/// <param name="aspectRatio">The aspect ratio (width / height) of the viewport.</param>
		/// <param name="FOV">The vertical field of view in radians.</param>
		/// <param name="npd">The near plane distance.</param>
		/// <param name="fpd">The far plane distance.</param>
		/// <returns>The resulting perspective projection matrix.</returns>
		static Matrix4x4 CreatePerspectiveProjection(float aspectRatio, float FOV, float npd, float fpd);
		/// <summary>
		/// Creates a right-handed orthographic projection matrix.
		/// </summary>
		/// <param name="screenSize">The width and height of the projection view volume.</param>
		/// <param name="npd">The near plane distance.</param>
		/// <param name="fpd">The far plane distance.</param>
		/// <returns>The resulting orthographic projection matrix.</returns>
		static Matrix4x4 CreateOrthographicProjection(const Point &screenSize, float npd, float fpd);

		/// <summary>
		/// Creates a spherical billboard matrix that always faces the camera position.
		/// </summary>
		/// <param name="objectPos">The position of the object.</param>
		/// <param name="cameraPos">The position of the camera.</param>
		/// <param name="cameraUp">The up vector of the camera.</param>
		/// <param name="cameraForward">The forward vector of the camera.</param>
		/// <returns>The resulting billboard matrix.</returns>
		static Matrix4x4 CreateSphericalBillboard(const Vector3 &objectPos,const Vector3 &cameraPos,const Vector3 &cameraUp,const Vector3 &cameraForward);
		/// <summary>
		/// Creates a cylindrical billboard matrix that rotates around a fixed axis to face the camera.
		/// </summary>
		/// <param name="objectPos">The position of the object.</param>
		/// <param name="cameraPos">The position of the camera.</param>
		/// <param name="cameraUp">The up vector of the camera.</param>
		/// <param name="cameraForward">The forward vector of the camera.</param>
		/// <param name="axis">The fixed rotation axis for the billboard.</param>
		/// <param name="objectForward">An optional forward vector for the object, used to resolve ambiguity when the object is aligned with the axis.</param>
		/// <returns>The resulting billboard matrix.</returns>
		static Matrix4x4 CreateCylindricalBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUp, const Vector3& cameraForward, const Vector3& axis, std::optional<Vector3> objectForward);

		/// <summary>
		/// Element-wise (Hadamard) product of two matrices.
		/// </summary>
		/// <param name="a">The first matrix.</param>
		/// <param name="b">The second matrix.</param>
		/// <returns>The resulting matrix after Hadamard multiplication.</returns>
		static Matrix4x4 Hadamard(const Matrix4x4& a, const Matrix4x4& b);
		/// <summary>
		/// Element-wise (Hadamard) multiplication of this matrix with another matrix.
		/// </summary>
		/// <param name="m">The matrix to multiply with.</param>
		/// <returns>A reference to this matrix after Hadamard multiplication.</returns>
		Matrix4x4& Hadamard(const Matrix4x4& m);

		/// <summary>
		/// Adds this matrix to another matrix and returns the result.
		/// </summary>
		/// <param name="m">The matrix to add.</param>
		/// <returns>The resulting matrix after addition.</returns>
		Matrix4x4 operator +(const Matrix4x4& m) const noexcept;
		/// <summary>
		/// Adds another matrix to this matrix in-place.
		/// </summary>
		/// <param name="m">The matrix to add.</param>
		/// <returns>A reference to this matrix after addition.</returns>
		Matrix4x4& operator +=(const Matrix4x4& m) noexcept;

		/// <summary>
		/// Subtracts another matrix from this matrix and returns the result.
		/// </summary>
		/// <param name="m">The matrix to subtract.</param>
		/// <returns>The resulting matrix after subtraction.</returns>
		Matrix4x4 operator -(const Matrix4x4& m) const noexcept;
		/// <summary>
		/// Subtracts another matrix from this matrix in-place.
		/// </summary>
		/// <param name="m">The matrix to subtract.</param>
		/// <returns>A reference to this matrix after subtraction.</returns>
		Matrix4x4& operator -=(const Matrix4x4& m) noexcept;

		/// <summary>
		/// Multiplies this matrix with another matrix (matrix product) and returns the result.
		/// </summary>
		/// <param name="m">The matrix to multiply with.</param>
		/// <returns>The resulting matrix after multiplication.</returns>
		Matrix4x4 operator *(const Matrix4x4& m) const noexcept;
		/// <summary>
		/// Multiplies this matrix with another matrix (matrix product) in-place.
		/// </summary>
		/// <param name="m">The matrix to multiply with.</param>
		/// <returns>A reference to this matrix after multiplication.</returns>
		Matrix4x4& operator *=(const Matrix4x4& m) noexcept;

		/// <summary>
		/// Multiplies this matrix by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply with.</param>
		/// <returns>The resulting scaled matrix.</returns>
		Matrix4x4 operator*(float scalar) const noexcept;
		/// <summary>
		/// Multiplies this matrix by a scalar in-place.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply with.</param>
		/// <returns>A reference to this matrix after scaling.</returns>
		Matrix4x4& operator *=(float scalar) noexcept;

		/// <summary>
		/// Transposes this matrix in-place.
		/// </summary>
		/// <returns>A reference to this matrix after transposition.</returns>
		Matrix4x4& Transpose();
		/// <summary>
		/// Returns the transpose of the specified matrix.
		/// </summary>
		/// <param name="m">The matrix to transpose.</param>
		/// <returns>The transposed matrix.</returns>
		static Matrix4x4 Transpose(const Matrix4x4& m);

		/// <summary>
		/// Inverts this matrix in-place.
		/// </summary>
		/// <returns>A reference to this matrix after inversion.</returns>
		Matrix4x4& Invert();
		/// <summary>
		/// Returns the inverse of the specified matrix.
		/// </summary>
		/// <param name="m">The matrix to invert.</param>
		/// <returns>The inverted matrix.</returns>
		static Matrix4x4 Invert(const Matrix4x4& m);

		/// <summary>
		/// Returns a reference to the element at the specified index in the matrix, allowing for both reading and writing.
		/// </summary>
		/// <param name="index">Index, between 0 and 15.</param>
		/// <returns>A reference to the element at the specified index.</returns>
		float& operator[](unsigned index);

		/// <summary>
		/// Returns the trace of this matrix.
		/// </summary>
		/// <returns>M11 + M22 + M33 + M44</returns>
		float Trace() const noexcept;
		/// <summary>
		/// Returns the determinant of this matrix.
		/// </summary>
		/// <returns>The determinant of the matrix.</returns>
		float Determinant() const noexcept;

		/// <summary>
		/// Returns the forward direction vector encoded in this matrix.
		/// </summary>
		/// <returns>The forward direction vector.</returns>
		Vector3 Forward() const noexcept;
		/// <summary>
		/// Returns the backward direction vector encoded in this matrix.
		/// </summary>
		/// <returns>The backward direction vector.</returns>
		Vector3 Backward() const noexcept;

		/// <summary>
		/// Returns the up direction vector encoded in this matrix.
		/// </summary>
		/// <returns>The up direction vector.</returns>
		Vector3 Up() const noexcept;
		/// <summary>
		/// Returns the down direction vector encoded in this matrix.
		/// </summary>
		/// <returns>The down direction vector.</returns>
		Vector3 Down() const noexcept;

		/// <summary>
		/// Returns the left direction vector encoded in this matrix.
		/// </summary>
		/// <returns>The left direction vector.</returns>
		Vector3 Left() const noexcept;
		/// <summary>
		/// Returns the right direction vector encoded in this matrix.
		/// </summary>
		/// <returns>The right direction vector.</returns>
		Vector3 Right() const noexcept;

		/// <summary>
		/// Returns the translation vector encoded in this matrix.
		/// </summary>
		/// <returns>The translation vector.</returns>
		Vector3 Translation() const noexcept;
	};

	/// <summary>
	/// Multiplies a matrix by a scalar.
	/// </summary>
	/// <param name="scalar">The scalar value to multiply with.</param>
	/// <param name="m">The matrix to multiply.</param>
	/// <returns>The resulting scaled matrix.</returns>
	Matrix4x4 E3DRSP_MATH_EXPORT operator *(float scalar, const Matrix4x4& m) noexcept;
	/// <summary>
	/// Divides a scalar by a matrix, computed as the scalar multiplied by the inverse of the matrix.
	/// </summary>
	/// <param name="f">The scalar value.</param>
	/// <param name="m">The matrix to invert and multiply with.</param>
	/// <returns>The resulting matrix.</returns>
	Matrix4x4 E3DRSP_MATH_EXPORT operator /(float f, const Matrix4x4& m);
}
