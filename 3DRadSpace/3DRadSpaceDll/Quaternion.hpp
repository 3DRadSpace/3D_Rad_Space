#pragma once
#include "Globals.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents an efficient method to compute and store 3D rotations.
	/// </summary>
	struct DLLEXPORT Quaternion
	{
		/// <summary>
		/// The X component of the quaternion
		/// </summary>
		float X;
		/// <summary>
		/// The Y component of the quaternion
		/// </summary>
		float Y;
		/// <summary>
		/// The Z component of the quaternion
		/// </summary>
		float Z;
		/// <summary>
		/// The W component of the quaternion
		/// </summary>
		float W;

		/// <summary>
		/// Constructs the identity quaternion.
		/// </summary>
		Quaternion() : X(0), Y(0), Z(0), W(1) {};
		/// <summary>
		/// Constructs a quaternion from the given values.
		/// </summary>
		/// <param name="x">X component</param>
		/// <param name="y">Y component</param>
		/// <param name="z">Z component</param>
		/// <param name="w">W component</param>
		Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {};

		/// <summary>
		/// Creates a quaternion from the given Euler rotation 
		/// </summary>
		/// <param name="yaw">Yaw (Y angle)</param>
		/// <param name="pitch">Pitch (X angle)</param>
		/// <param name="roll">Roll (Z angle)</param>
		/// <returns></returns>
		static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	};
	/// <summary>
	/// Composes two rotations.
	/// </summary>
	/// <param name="q1">quaternion</param>
	/// <param name="q2">quaternion</param>
	/// <returns></returns>
	Quaternion DLLEXPORT operator *(const Quaternion& q1, const Quaternion& q2);
	Quaternion DLLEXPORT operator *=( Quaternion& q1, const Quaternion& q2);

	bool DLLEXPORT operator ==(const Quaternion &q1, const Quaternion& q2);
	bool DLLEXPORT operator !=(const Quaternion& q1, const Quaternion& q2);
}

