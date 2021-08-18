#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "Quaternion.h"

struct DLLEXPORT Vector3;

struct DLLEXPORT Matrix
{
	float M11, M12, M13, M14;
	float M21, M22, M23, M24;
	float M31, M32, M33, M34;
	float M41, M42, M43, M44;

	Matrix(float* f) : M11(f[0]),  M12(f[1]),  M13(f[2]),  M14(f[3]),
					   M21(f[4]),  M22(f[5]),  M23(f[6]),  M24(f[7]),
					   M31(f[8]),  M32(f[9]),  M33(f[10]), M34(f[11]),
					   M41(f[12]), M42(f[13]), M43(f[14]), M44(f[15]) {};

	Matrix() : M11(1), M12(0), M13(0), M14(0),
			   M21(0), M22(1), M23(0), M24(0),
			   M31(0), M32(0), M33(1), M34(0),
			   M41(0), M42(0), M43(0), M44(1) {};

	static Matrix CreateScale(float scale);
	static Matrix CreateScale(const Vector3 &v);
	static Matrix CreateTranslation(const Vector3& p);
	Matrix CreateRotationX(float alpha);
	Matrix CreateRotationY(float beta);
	Matrix CreateRotationZ(float gamma);
	Matrix CreateFromQuaternion(Quaternion q);
	static Matrix CreateLookAt(const Vector3& camerapos, const Vector3& camera_look_at, const Vector3& normal);
	static Matrix CreateProjectionFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	Matrix CreateProjectionScreenRatio(float screenX, float screenY, float npd, float dpf);
};

