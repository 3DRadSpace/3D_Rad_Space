#pragma once
#include "Globals.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

namespace Engine3DRadSpace
{
	struct DLLEXPORT Vector3;

	/// <summary>
	/// Represents a linear transfomation.
	/// </summary>
	struct DLLEXPORT Matrix
	{
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;

		/// <summary>
		/// Constructs a matrix from a array.
		/// </summary>
		/// <param name="f">float array. Size must be greater or equal to 16.</param>
		Matrix(float* f) : M11(f[0]), M12(f[1]), M13(f[2]), M14(f[3]),
			M21(f[4]), M22(f[5]), M23(f[6]), M24(f[7]),
			M31(f[8]), M32(f[9]), M33(f[10]), M34(f[11]),
			M41(f[12]), M42(f[13]), M43(f[14]), M44(f[15]) {};
		/// <summary>
		/// Constructs the identity matrix.
		/// </summary>
		Matrix() : M11(1), M12(0), M13(0), M14(0),
			M21(0), M22(1), M23(0), M24(0),
			M31(0), M32(0), M33(1), M34(0),
			M41(0), M42(0), M43(0), M44(1) {};
		/// <summary>
		/// Constructs a matrix from the given values.
		/// </summary>
		/// <param name="m11"></param>
		/// <param name="m12"></param>
		/// <param name="m13"></param>
		/// <param name="m14"></param>
		/// <param name="m21"></param>
		/// <param name="m22"></param>
		/// <param name="m23"></param>
		/// <param name="m24"></param>
		/// <param name="m31"></param>
		/// <param name="m32"></param>
		/// <param name="m33"></param>
		/// <param name="m34"></param>
		/// <param name="m41"></param>
		/// <param name="m42"></param>
		/// <param name="m43"></param>
		/// <param name="m44"></param>
		Matrix(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44) : M11(m11), M12(m12), M13(m13), M14(m14),
			M21(m21), M22(m22), M23(m23), M24(m24),
			M31(m31), M32(m32), M33(m33), M34(m34),
			M41(m41), M42(m42), M43(m43), M44(m44) {};

		/// <summary>
		/// Creates a diagonal scaling matrix.
		/// </summary>
		/// <param name="scale">Scale multiplier</param>
		/// <returns></returns>
		static Matrix CreateScale(float scale);
		/// <summary>
		/// Creates a diagonal scaling matrix from a 3D vector.
		/// </summary>
		/// <param name="v">Scaling vector</param>
		/// <returns></returns>
		static Matrix CreateScale(const Vector3& v);

		/// <summary>
		/// Creates a translation matrix. Translation matrices can be used to express the position of 3D objects in the game world.
		/// </summary>
		/// <param name="p">Position vector</param>
		/// <returns></returns>
		static Matrix CreateTranslation(const Vector3& p);

		/// <summary>
		/// Creates an Euler rotation around the X axis (pitch)
		/// </summary>
		/// <param name="alpha">X rotation angle in radians</param>
		/// <returns></returns>
		static Matrix CreateRotationX(float alpha);
		/// <summary>
		/// Creates an Euler rotation around the Y axis (yaw)
		/// </summary>
		/// <param name="beta">Y rotation angle in radians</param>
		/// <returns></returns>
		static Matrix CreateRotationY(float beta);
		/// <summary>
		/// Creates an Euler rotation around the Z axis (roll)
		/// </summary>
		/// <param name="gamma">Z rotation angle in radians</param>
		/// <returns></returns>
		static Matrix CreateRotationZ(float gamma);

		/// <summary>
		/// Creates an rotation matrix from a given quaternion
		/// </summary>
		/// <param name="q">Quaternion representing a 3D rotation</param>
		/// <returns></returns>
		static Matrix CreateFromQuaternion(Quaternion q);

		/// <summary>
		/// Creates a look at target matrix. Used for rendering.
		/// </summary>
		/// <param name="camerapos">Camera position in world coordinates</param>
		/// <param name="camera_look_at">Camera target position</param>
		/// <param name="normal">Vector normal to the surface the camera is standing on.</param>
		/// <returns></returns>
		static Matrix CreateLookAt(const Vector3& camerapos, const Vector3& camera_look_at, const Vector3& normal);

		/// <summary>
		/// Creates a projection matrix from a field of view and aspect ratio
		/// </summary>
		/// <param name="fieldOfView">Y's FOV in radians</param>
		/// <param name="aspectRatio">Width divided by heigh</param>
		/// <param name="nearPlaneDistance">The minimum drawing distance</param>
		/// <param name="farPlaneDistance">The maximum drawing distance</param>
		/// <returns></returns>
		static Matrix CreateProjectionFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		/// <summary>
		/// Creates a projection matrix from a screen aspect ratio
		/// </summary>
		/// <param name="screenX">X coordinate of the screen</param>
		/// <param name="screenY">Y coordinate of the screen</param>
		/// <param name="npd">The minimum drawing distance</param>
		/// <param name="dpf">The maximum drawing distance</param>
		/// <returns></returns>
		static Matrix CreateProjectionScreenRatio(float screenX, float screenY, float npd, float dpf);
	};

	/// <summary>
	/// Multiplies two matrices. Geometrically this means composing 2 linear transformations.
	/// Matrix multiplication is not commutative, therefore A * B is not equal to B * A unless for some specific matrices like the identity matrix.
	/// </summary>
	/// <param name="a">The first matrix.</param>
	/// <param name="b">The second matrix.</param>
	/// <returns></returns>
	Matrix operator * (const Matrix& a, const Matrix& b);
}