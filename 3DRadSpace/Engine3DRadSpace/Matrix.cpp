#include "Matrix.hpp"

using namespace Engine3DRadSpace::Math;

Matrix::Matrix(float m[16])
{
	M11 = m[0];
	M12 = m[1];
	M13 = m[2];
	M14 = m[3];

	M21 = m[4];
	M22 = m[5];
	M23 = m[6];
	M24 = m[7];

	M31 = m[8];
	M32 = m[9];
	M33 = m[10];
	M34 = m[11];

	M41 = m[12];
	M42 = m[13];
	M43 = m[14];
	M44 = m[15];
}

Matrix::Matrix(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44):
	M11(m11), M12(m12), M13(m13), M14(m14),
	M21(m21), M22(m22), M23(m23), M24(m24),
	M31(m31), M32(m32), M33(m33), M34(m34),
	M41(m41), M42(m42), M43(m43), M44(m44)
{
}

Matrix Matrix::CreateTranslation(const Vector3 &pos)
{
	return Matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		pos.X, pos.Y, pos.Z, 1
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateScale(const Vector3 &scale)
{
	return Matrix(
		scale.X, 0, 0, 0,
		0, scale.Y, 0, 0,
		0, 0, scale.Z, 0,
		0, 0, 0, 1
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateRotationX(float theta)
{
	return Matrix(
		1, 0, 0, 0,
		0, cos(theta), -sin(theta), 0,
		0, sin(theta), cos(theta), 0,
		0 , 0, 0, 1
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateRotationY(float theta)
{
	return Matrix(
		cos(theta), 0, sin(theta), 0,
		0, 1, 0, 0,
		-sin(theta), 0, cos(theta),0,
		0, 0, 0, 1
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateRotationZ(float theta)
{
	return Matrix(
		cos(theta), -sin(theta), 0, 0,
		sin(theta), cos(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateFromQuaternion(const Quaternion& q)
{
	return Matrix(
		
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateLookAtView(const Vector3 &pos,const Vector3 &look_at,const Vector3 &up_dir)
{
	return Matrix();
}

Matrix Engine3DRadSpace::Math::Matrix::CreatePerspectiveProjection(float aspectRatio, float FOV, float npd, float fpd)
{
	float h = 1.0f / tan(FOV * 0.5f);
	float w = h / aspectRatio;
	float a = fpd / (fpd - npd);
	float b = (-npd * fpd) / (fpd - npd);

	return Matrix(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, a, 1,
		0, 0, b, 0
	);
}

Matrix Engine3DRadSpace::Math::Matrix::CreateOrthographicProjection(const Point &screenSize, float npd, float fpd)
{
	float w = 2.0f / screenSize.X;
	float h = 2.0f / screenSize.Y;
	float a = 1.0f / (fpd - npd);
	float b = -a * npd;

	return Matrix(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, a, 0,
		0, 0, b, 1
	);
}
