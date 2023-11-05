#include "Matrix.hpp"
#include <DirectXMath.h>

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

Matrix Matrix::CreateScale(const Vector3 &scale)
{
	return Matrix(
		scale.X, 0, 0, 0,
		0, scale.Y, 0, 0,
		0, 0, scale.Z, 0,
		0, 0, 0, 1
	);
}

Matrix Matrix::CreateRotationX(float theta)
{
	return Matrix(
		1, 0, 0, 0,
		0, cos(theta), -sin(theta), 0,
		0, sin(theta), cos(theta), 0,
		0 , 0, 0, 1
	);
}

Matrix Matrix::CreateRotationY(float theta)
{
	return Matrix(
		cos(theta), 0, sin(theta), 0,
		0, 1, 0, 0,
		-sin(theta), 0, cos(theta),0,
		0, 0, 0, 1
	);
}

Matrix Matrix::CreateRotationZ(float theta)
{
	return Matrix(
		cos(theta), -sin(theta), 0, 0,
		sin(theta), cos(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Matrix Matrix::CreateFromQuaternion(const Quaternion& q)
{
	//https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	float sqw = q.W * q.W;
	float sqx = q.X * q.X;
	float sqy = q.Y * q.Y;
	float sqz = q.Z * q.Z;

	Matrix r;

	r.M11 = (sqx - sqy - sqz + sqw);
	r.M22 = (-sqx + sqy - sqz + sqw);
	r.M33 = (-sqx - sqy + sqz + sqw);

	float tmp1 = q.X * q.Y;
	float tmp2 = q.Z * q.W;
	r.M21 = 2.0f * (tmp1 + tmp2);
	r.M12 = 2.0f * (tmp1 - tmp2);

	tmp1 = q.X * q.Z;
	tmp2 = q.Y * q.W;
	r.M31 = 2.0f * (tmp1 - tmp2);
	r.M13 = 2.0f * (tmp1 + tmp2);
	tmp1 = q.Y * q.Z;
	tmp2 = q.X * q.W;
	r.M32 = 2.0f * (tmp1 + tmp2);
	r.M23 = 2.0f * (tmp1 - tmp2);

	return r;
}

Matrix Matrix::CreateLookAtView(const Vector3 &pos,const Vector3 &look_at,const Vector3 &up_dir)
{
	Vector3 forward = (pos - look_at).Normalize();
	Vector3 right = Vector3::Cross(up_dir, forward).Normalize();
	Vector3 up = Vector3::Cross(forward,right);

	return Matrix(
		right.X, up.X, forward.X, 0,
		right.Y, up.Y, forward.Y, 0,
		right.Z, up.Z, forward.Z, 0,
		-right.Dot(pos), -up.Dot(pos), -forward.Dot(pos), 1
	);
}

Matrix Matrix::CreatePerspectiveProjection(float aspectRatio, float FOV, float npd, float fpd)
{
	float h = 1.0f / tan(FOV * 0.5f);
	float w = h / aspectRatio;
	float a = fpd / (npd - fpd);
	float b = (npd * fpd) / (npd - fpd);

	return Matrix(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0
	);
}

Matrix Matrix::CreateOrthographicProjection(const Point &screenSize, float npd, float fpd)
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

Matrix Matrix::CreateSphericalBillboard(Vector3 objectPos, Vector3 cameraPos, Vector3 cameraUp, Vector3 cameraForward)
{
	Matrix r;

	Vector3 vector;

	vector.X = objectPos.X - cameraPos.X;
	vector.Y = objectPos.Y - cameraPos.Y;
	vector.Z = objectPos.Z - cameraPos.Z;

	Vector3 vector2;
	Vector3 vector3;
	float num = vector.LengthSquared();
	if (num < 0.0001f)
	{
		vector = cameraForward;
	}
	else vector *= 1.f / sqrtf(num);

	vector3 = Vector3::Cross(cameraUp, vector).Normalize();
	vector2 = Vector3::Cross(vector, vector3);
	r.M11 = vector3.X;
	r.M12 = vector3.Y;
	r.M13 = vector3.Z;
	r.M14 = 0;
	r.M21 = vector2.X;
	r.M22 = vector2.Y;
	r.M23 = vector2.Z;
	r.M24 = 0;
	r.M31 = objectPos.X - cameraPos.X;
	r.M32 = objectPos.Y - cameraPos.Y;
	r.M33 = objectPos.Z - cameraPos.Z;
	r.M34 = 0;
	r.M41 = objectPos.X;
	r.M42 = objectPos.Y;
	r.M43 = objectPos.Z;
	r.M44 = 1;

	return r;
}

Matrix Matrix::Hadamard(const Matrix& a, const Matrix& b)
{
	Matrix r;
	r.M11 = a.M11 * b.M11;
	r.M12 = a.M12 * b.M12;
	r.M13 = a.M13 * b.M13;
	r.M14 = a.M14 * b.M14;

	r.M21 = a.M21 * b.M21;
	r.M22 = a.M22 * b.M22;
	r.M23 = a.M23 * b.M23;
	r.M24 = a.M24 * b.M24;

	r.M31 = a.M31 * b.M31;
	r.M32 = a.M32 * b.M32;
	r.M33 = a.M33 * b.M33;
	r.M34 = a.M34 * b.M34;

	r.M41 = a.M41 * b.M41;
	r.M42 = a.M42 * b.M42;
	r.M43 = a.M43 * b.M43;
	r.M44 = a.M44 * b.M44;

	return r;
}

Matrix& Matrix::Hadamard(const Matrix& m)
{
	M11 *= m.M11;
	M12 *= m.M12;
	M13 *= m.M13;
	M14 *= m.M14;

	M21 *= m.M21;
	M22 *= m.M22;
	M23 *= m.M23;
	M24 *= m.M24;

	M31 *= m.M31;
	M32 *= m.M32;
	M33 *= m.M33;
	M34 *= m.M34;

	M41 *= m.M41;
	M42 *= m.M42;
	M43 *= m.M43;
	M44 *= m.M44;

	return *this;
}

Matrix Matrix::operator+(const Matrix &m) const
{
	return Matrix(
		M11 + m.M11, M12 + m.M12, M13 + m.M13, M14 + m.M14,	
		M21 + m.M21, M22 + m.M22, M13 + m.M13, M14 + m.M14,	
		M31 + m.M31, M32 + m.M32, M13 + m.M13, M14 + m.M14,	
		M41 + m.M41, M42 + m.M42, M13 + m.M13, M14 + m.M14	
	);
}

Matrix Matrix::operator+=(const Matrix &m)
{
	M11 += m.M11;
	M12 += m.M12;
	M13 += m.M13;
	M14 += m.M14;

	M21 += m.M21;
	M22 += m.M22;
	M23 += m.M23;
	M24 += m.M24;

	M31 += m.M31;
	M32 += m.M32;
	M33 += m.M33;
	M34 += m.M34;

	M41 += m.M41;
	M42 += m.M42;
	M43 += m.M43;
	M44 += m.M44;

	return *this;
}

Matrix Matrix::operator-(const Matrix &m) const
{
	return Matrix(
		M11 - m.M11, M12 - m.M12, M13 - m.M13, M14 - m.M14,
		M21 - m.M21, M22 - m.M22, M13 - m.M13, M14 - m.M14,
		M31 - m.M31, M32 - m.M32, M13 - m.M13, M14 - m.M14,
		M41 - m.M41, M42 - m.M42, M13 - m.M13, M14 - m.M14
	);
}

Matrix Matrix::operator-=(const Matrix &m)
{
	M11 -= m.M11;
	M12 -= m.M12;
	M13 -= m.M13;
	M14 -= m.M14;

	M21 -= m.M21;
	M22 -= m.M22;
	M23 -= m.M23;
	M24 -= m.M24;

	M31 -= m.M31;
	M32 -= m.M32;
	M33 -= m.M33;
	M34 -= m.M34;

	M41 -= m.M41;
	M42 -= m.M42;
	M43 -= m.M43;
	M44 -= m.M44;

	return *this;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	Matrix r;
	r.M11 = M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41;
	r.M12 = M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42;
	r.M13 = M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43;
	r.M14 = M11 * m.M14 + M12 * m.M24 + M13 * m.M34 + M14 * m.M11;

	r.M21 = M21 * m.M11 + M22 * m.M21 + M23 * m.M31 + M24 * m.M41;
	r.M22 = M21 * m.M12 + M22 * m.M22 + M23 * m.M32 + M24 * m.M42;
	r.M23 = M21 * m.M13 + M22 * m.M23 + M23 * m.M33 + M24 * m.M43;
	r.M24 = M21 * m.M14 + M22 * m.M24 + M23 * m.M34 + M24 * m.M44;

	r.M31 = M31 * m.M11 + M32 * m.M21 + M33 * m.M31 + M34 * m.M41;
	r.M32 = M31 * m.M12 + M32 * m.M22 + M33 * m.M32 + M34 * m.M42;
	r.M33 = M31 * m.M13 + M32 * m.M23 + M33 * m.M33 + M34 * m.M43;
	r.M34 = M31 * m.M14 + M32 * m.M24 + M33 * m.M34 + M34 * m.M44;

	r.M41 = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + M44 * m.M41;
	r.M42 = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + M44 * m.M42;
	r.M43 = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + M44 * m.M43;
	r.M44 = M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + M44 * m.M44;
	return r;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	this->M11 = M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41;
	this->M12 = M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42;
	this->M13 = M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43;
	this->M14 = M11 * m.M14 + M12 * m.M24 + M13 * m.M34 + M14 * m.M11;

	this->M21 = M21 * m.M11 + M22 * m.M21 + M23 * m.M31 + M24 * m.M41;
	this->M22 = M21 * m.M12 + M22 * m.M22 + M23 * m.M32 + M24 * m.M42;
	this->M23 = M21 * m.M13 + M22 * m.M23 + M23 * m.M33 + M24 * m.M43;
	this->M24 = M21 * m.M14 + M22 * m.M24 + M23 * m.M34 + M24 * m.M44;

	this->M31 = M31 * m.M11 + M32 * m.M21 + M33 * m.M31 + M34 * m.M41;
	this->M32 = M31 * m.M12 + M32 * m.M22 + M33 * m.M32 + M34 * m.M42;
	this->M33 = M31 * m.M13 + M32 * m.M23 + M33 * m.M33 + M34 * m.M43;
	this->M34 = M31 * m.M14 + M32 * m.M24 + M33 * m.M34 + M34 * m.M44;

	this->M41 = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + M44 * m.M41;
	this->M42 = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + M44 * m.M42;
	this->M43 = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + M44 * m.M43;
	this->M44 = M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + M44 * m.M44;
	return *this;
}

Matrix Matrix::operator*(float scalar) const
{
	Matrix m(*this);
	m.M11 *= scalar;
	m.M12 *= scalar;
	m.M13 *= scalar;
	m.M14 *= scalar;

	m.M21 *= scalar;
	m.M22 *= scalar;
	m.M23 *= scalar;
	m.M24 *= scalar;

	m.M31 *= scalar;
	m.M32 *= scalar;
	m.M33 *= scalar;
	m.M34 *= scalar;

	m.M41 *= scalar;
	m.M42 *= scalar;
	m.M43 *= scalar;
	m.M44 *= scalar;

	return m;
}

Matrix& Matrix::operator*=(float scalar)
{
	M11 *= scalar;
	M12 *= scalar;
	M13 *= scalar;
	M14 *= scalar;

	M21 *= scalar;
	M22 *= scalar;
	M23 *= scalar;
	M24 *= scalar;

	M31 *= scalar;
	M32 *= scalar;
	M33 *= scalar;
	M34 *= scalar;

	M41 *= scalar;
	M42 *= scalar;
	M43 *= scalar;
	M44 *= scalar;

	return *this;
}

Matrix Matrix::Transpose()
{
	const Matrix copy = *this;
	// M[i][j] = M[j][i]. Skip i=j. O(n^2 - n) = O(n^2)
	M12 = copy.M21;
	M13 = copy.M31;
	M14 = copy.M41;

	M21 = copy.M12;
	M23 = copy.M32;
	M24 = copy.M42;

	M31 = copy.M13;
	M32 = copy.M23;
	M34 = copy.M43;

	M41 = copy.M14;
	M42 = copy.M24;
	M43 = copy.M34;

	return *this;
}

float& Matrix::operator[](unsigned index)
{
	switch (index)
	{
		case 0: return M11;
		case 1: return M12;
		case 2: return M13;
		case 3: return M14;
		case 4: return M21;
		case 5: return M22;
		case 6: return M23;
		case 7: return M24;
		case 8: return M31;
		case 9: return M32;
		case 10: return M33;
		case 11: return M34;
		case 12: return M41;
		case 13: return M42;
		case 14: return M43;
		case 15: return M44;
		default:
			throw std::out_of_range("Out of matrix range! [0-15]");
	}
}

float Matrix::Trace() const
{
	return M11 + M22 + M33 + M44;
}

Vector3 Matrix::Forward() const
{
	return { -M31, -M32, -M33 };
}

Vector3 Matrix::Backward() const
{
	return { M31, M32, M33 };
}

Vector3 Matrix::Up() const
{
	return { M21, M22, M23 };
}

Vector3 Matrix::Down() const
{
	return { -M21, -M22, -M23 };
}
Vector3 Matrix::Left() const
{
	return { -M11, -M12, -M13 };
}

Vector3 Matrix::Right() const
{
	return { M11, M12, M13 };
}

Vector3 Matrix::Translation() const
{
	return { M41, M42, M43 };
}


Matrix Engine3DRadSpace::Math::operator*(float scalar, const Matrix& m)
{
	Matrix r(m);
	r.M11 *= scalar;
	r.M12 *= scalar;
	r.M13 *= scalar;
	r.M14 *= scalar;

	r.M21 *= scalar;
	r.M22 *= scalar;
	r.M23 *= scalar;
	r.M24 *= scalar;

	r.M31 *= scalar;
	r.M32 *= scalar;
	r.M33 *= scalar;
	r.M34 *= scalar;

	r.M41 *= scalar;
	r.M42 *= scalar;
	r.M43 *= scalar;
	r.M44 *= scalar;

	return r;
}

Matrix Engine3DRadSpace::Math::operator/(float f, const Matrix& m)
{
	Matrix r(m);
	r.M11 /= f;
	r.M12 /= f;
	r.M13 /= f;
	r.M14 /= f;

	r.M21 /= f;
	r.M22 /= f;
	r.M23 /= f;
	r.M24 /= f;

	r.M31 /= f;
	r.M32 /= f;
	r.M33 /= f;
	r.M34 /= f;

	r.M41 /= f;
	r.M42 /= f;
	r.M43 /= f;
	r.M44 /= f;

	return r;
}