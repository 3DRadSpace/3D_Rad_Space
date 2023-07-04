#pragma once
#include "Quaternion.hpp"
#include "Point.hpp"

namespace Engine3DRadSpace::Math
{
	struct Vector3;
	struct Quaternion;

	struct DLLEXPORT Matrix
	{
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;

		explicit Matrix(float m[16]);
		explicit Matrix(
			float m11 = 1, float m12 = 0, float m13 = 0, float m14 = 0,
			float m21 = 0, float m22 = 1, float m23 = 0, float m24 = 0,
			float m31 = 0, float m32 = 0, float m33 = 1, float m34 = 0,
			float m41 = 0, float m42 = 0, float m43 = 0, float m44 = 1);
		
		static Matrix CreateTranslation(const Vector3 &pos);
		static Matrix CreateScale(const Vector3 &scale);

		static Matrix CreateRotationX(float theta);
		static Matrix CreateRotationY(float theta);
		static Matrix CreateRotationZ(float theta);
		static Matrix CreateFromQuaternion(const Quaternion& q);

		static Matrix CreateLookAtView(const Vector3 &pos,const Vector3 &look_at,const Vector3 &up_dir);

		static Matrix CreatePerspectiveProjection(float aspectRatio, float FOV, float npd, float fpd);
		static Matrix CreateOrthographicProjection(const Point &screenSize, float npd, float fpd);

		Matrix operator +(const Matrix &m) const;
		Matrix operator +=(const Matrix &m);

		Matrix operator -(const Matrix &m) const;
		Matrix operator -=(const Matrix &m);

		Matrix operator *(const Matrix& m) const;
		Matrix& operator *=(const Matrix& m);

		Matrix Transpose();

		auto operator <=>(const Matrix& m) const = default;

		float& operator[](unsigned index);

		float Trace() const;
	};
}
