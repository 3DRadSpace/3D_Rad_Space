#include "Matrix.h"

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateScale(float scale)
{
	Matrix m;
    m.M11 = scale;
    m.M22 = scale;
    m.M33 = scale;
    m.M44 = 1;
    return m;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateScale(const Vector3& v)
{
	Matrix m;
    m.M11 = v.X;
    m.M22 = v.Y;
    m.M33 = v.Z;
    m.M44 = 1;
    return m;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateTranslation(const Vector3& p)
{
	Matrix m;
	m.M41 = p.X;
	m.M42 = p.Y;
	m.M43 = p.Z;
	return m;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateRotationX(float alpha)
{
	Matrix result;

	float val1 = std::cos(alpha);
	float val2 = std::sin(alpha);

	result.M22 = val1;
	result.M23 = val2;
	result.M32 = -val2;
	result.M33 = val1;

	return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateRotationY(float beta)
{
	Matrix result;
	
	float val1 = std::cos(beta);
	float val2 = std::sin(beta);

	result.M11 = val1;
	result.M13 = -val2;
	result.M31 = val2;
	result.M33 = val1;

	return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateRotationZ(float gamma)
{
	Matrix result;

	float val1 = std::cos(gamma);
	float val2 = std::sin(gamma);

	result.M11 = val1;
	result.M12 = val2;
	result.M21 = -val2;
	result.M22 = val1;

	return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateFromQuaternion(Quaternion q)
{
	float num9 = q.X * q.X;
	float num8 = q.Y * q.Y;
	float num7 = q.Z * q.Z;
	float num6 = q.X * q.Y;
	float num5 = q.Z * q.W;
	float num4 = q.Z * q.X;
	float num3 = q.Y * q.W;
	float num2 = q.Y * q.Z;
	float num = q.X * q.W;
	Matrix result;
	result.M11 = 1.0f - (2.0f * (num8 + num7));
	result.M12 = 2.0f * (num6 + num5);
	result.M13 = 2.0f * (num4 - num3);
	result.M21 = 2.0f * (num6 - num5);
	result.M22 = 1.0f - (2.0f * (num7 + num9));
	result.M23 = 2.0f * (num2 + num);
	result.M31 = 2.0f * (num4 + num3);
	result.M32 = 2.0f * (num2 - num);
	result.M33 = 1.0f - (2.0f * (num8 + num9));
	return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateLookAt(const Vector3& camerapos, const Vector3& camera_look_at, const Vector3& normal)
{
	Vector3 vector = Vector3::Normalize(camerapos - camera_look_at);
	Vector3 vector2 = Vector3::Normalize(Vector3::Cross(normal, vector));
	Vector3 vector3 = Vector3::Cross(vector, vector2);
	Matrix result;
	result.M11 = vector2.X;
	result.M12 = vector3.X;
	result.M13 = vector.X;
	result.M14 = 0;
	result.M21 = vector2.Y;
	result.M22 = vector3.Y;
	result.M23 = vector.Y;
	result.M24 = 0;
	result.M31 = vector2.Z;
	result.M32 = vector3.Z;
	result.M33 = vector.Z;
	result.M34 = 0;
	result.M41 = -Vector3::Dot(vector2, camerapos);
	result.M42 = -Vector3::Dot(vector3, camerapos);
	result.M43 = -Vector3::Dot(vector, camerapos);
	result.M44 = 1;
	return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateProjectionFOV(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
	if ((fieldOfView <= 0.0f) || (fieldOfView >= 3.141593f))
	{
		throw std::exception("fieldOfView <= 0 or >= PI");
	}
	if (nearPlaneDistance <= 0.0f)
	{
		throw std::exception("nearPlaneDistance <= 0");
	}
	if (farPlaneDistance <= 0.0f)
	{
		throw std::exception("farPlaneDistance <= 0");
	}
	if (nearPlaneDistance >= farPlaneDistance)
	{
		throw std::exception("nearPlaneDistance >= farPlaneDistance");
	}

    float yScale = 1.0f / (float)std::tan((double)fieldOfView * 0.5f);
    float xScale = yScale / aspectRatio;
    //float negFarRange = std::isinf(farPlaneDistance) ? -1.0f : farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	float negFarRange = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    Matrix result;

    result.M11 = xScale;
    result.M12 = result.M13 = result.M14 = 0.0f;
    result.M22 = yScale;
    result.M21 = result.M23 = result.M24 = 0.0f;
    result.M31 = result.M32 = 0.0f;
    result.M33 = negFarRange;
    result.M34 = -1.0f;
    result.M41 = result.M42 = result.M44 = 0.0f;
    result.M43 = nearPlaneDistance * negFarRange;

    return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Matrix::CreateProjectionScreenRatio(float screenX, float screenY, float npd, float fpd)
{
	if (npd <= 0.0f)
	{
		throw std::exception("nearPlaneDistance <= 0");
	}
	if (fpd <= 0.0f)
	{
		throw std::exception("farPlaneDistance <= 0");
	}
	if (npd >= fpd)
	{
		throw std::exception("nearPlaneDistance >= farPlaneDistance");
	}

	float negFarRange = (+std::numeric_limits<float>::infinity() == fpd)  ? -1.0f : fpd / (npd - fpd);

	Matrix result;
	result.M11 = (2.0f * npd) / screenX;
	result.M12 = result.M13 = result.M14 = 0.0f;
	result.M22 = (2.0f * npd) / screenY;
	result.M21 = result.M23 = result.M24 = 0.0f;
	result.M33 = negFarRange;
	result.M31 = result.M32 = 0.0f;
	result.M34 = -1.0f;
	result.M41 = result.M42 = result.M44 = 0.0f;
	result.M43 = npd * negFarRange;

	return result;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::operator*(const Matrix& a, const Matrix& b)
{
	float m11 = (((a.M11 * b.M11) + (a.M12 * b.M21)) + (a.M13 * b.M31)) + (a.M14 * b.M41);
	float m12 = (((a.M11 * b.M12) + (a.M12 * b.M22)) + (a.M13 * b.M32)) + (a.M14 * b.M42);
	float m13 = (((a.M11 * b.M13) + (a.M12 * b.M23)) + (a.M13 * b.M33)) + (a.M14 * b.M43);
	float m14 = (((a.M11 * b.M14) + (a.M12 * b.M24)) + (a.M13 * b.M34)) + (a.M14 * b.M44);
	float m21 = (((a.M21 * b.M11) + (a.M22 * b.M21)) + (a.M23 * b.M31)) + (a.M24 * b.M41);
	float m22 = (((a.M21 * b.M12) + (a.M22 * b.M22)) + (a.M23 * b.M32)) + (a.M24 * b.M42);
	float m23 = (((a.M21 * b.M13) + (a.M22 * b.M23)) + (a.M23 * b.M33)) + (a.M24 * b.M43);
	float m24 = (((a.M21 * b.M14) + (a.M22 * b.M24)) + (a.M23 * b.M34)) + (a.M24 * b.M44);
	float m31 = (((a.M31 * b.M11) + (a.M32 * b.M21)) + (a.M33 * b.M31)) + (a.M34 * b.M41);
	float m32 = (((a.M31 * b.M12) + (a.M32 * b.M22)) + (a.M33 * b.M32)) + (a.M34 * b.M42);
	float m33 = (((a.M31 * b.M13) + (a.M32 * b.M23)) + (a.M33 * b.M33)) + (a.M34 * b.M43);
	float m34 = (((a.M31 * b.M14) + (a.M32 * b.M24)) + (a.M33 * b.M34)) + (a.M34 * b.M44);
	float m41 = (((a.M41 * b.M11) + (a.M42 * b.M21)) + (a.M43 * b.M31)) + (a.M44 * b.M41);
	float m42 = (((a.M41 * b.M12) + (a.M42 * b.M22)) + (a.M43 * b.M32)) + (a.M44 * b.M42);
	float m43 = (((a.M41 * b.M13) + (a.M42 * b.M23)) + (a.M43 * b.M33)) + (a.M44 * b.M43);
	float m44 = (((a.M41 * b.M14) + (a.M42 * b.M24)) + (a.M43 * b.M34)) + (a.M44 * b.M44);

	return Matrix(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}
