#include "Matrix4x4.hpp"
#include "Matrix3x3.hpp"
#include "Quaternion.hpp"
#include "Point.hpp"

using namespace Engine3DRadSpace::Math;

constexpr Matrix4x4::Matrix4x4(float m[16])
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

constexpr Matrix4x4::Matrix4x4(
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

Matrix4x4 Matrix4x4::CreateTranslation(const Vector3 &pos)
{
	return Matrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		pos.X, pos.Y, pos.Z, 1
	);
}

Matrix4x4 Matrix4x4::CreateScale(const Vector3 &scale)
{
	return Matrix4x4(
		scale.X, 0, 0, 0,
		0, scale.Y, 0, 0,
		0, 0, scale.Z, 0,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::CreateRotationX(float theta)
{
	return Matrix4x4(
		1, 0, 0, 0,
		0, cos(theta), -sin(theta), 0,
		0, sin(theta), cos(theta), 0,
		0 , 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::CreateRotationY(float theta)
{
	return Matrix4x4(
		cos(theta), 0, sin(theta), 0,
		0, 1, 0, 0,
		-sin(theta), 0, cos(theta),0,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::CreateRotationZ(float theta)
{
	return Matrix4x4(
		cos(theta), -sin(theta), 0, 0,
		sin(theta), cos(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::CreateFromQuaternion(const Quaternion& q)
{
	Matrix3x3 qm = Matrix3x3::CreateFromQuaternion(q);

	return Matrix4x4(
		qm.M11, qm.M12, qm.M13, 0.0f,
		qm.M21, qm.M22, qm.M23, 0.0f,
		qm.M31, qm.M32, qm.M33, 0.0f,
		0.0f,   0.0f,   0.0f,   1.0f
	);
}

Matrix4x4 Matrix4x4::CreateRotationYawPitchRoll(float yaw, float pitch, float roll)
{
	return Matrix4x4::CreateFromQuaternion(Quaternion::FromYawPitchRoll(yaw, pitch, roll));
}

Matrix4x4 Matrix4x4::CreateLookAtView(const Vector3 &pos,const Vector3 &look_at,const Vector3 &up_dir)
{
	const Vector3 forward = (pos - look_at).Normalize();
	const Vector3 right = Vector3::Cross(up_dir, forward).Normalize();
	const Vector3 up = Vector3::Cross(forward, right);

	return Matrix4x4(
		right.X, up.X, forward.X, 0,
		right.Y, up.Y, forward.Y, 0,
		right.Z, up.Z, forward.Z, 0,
		-right.Dot(pos), -up.Dot(pos), -forward.Dot(pos), 1
	);
}

Matrix4x4 Matrix4x4::CreatePerspectiveProjection(float aspectRatio, float FOV, float npd, float fpd)
{	
	float h = 1.0f / tan(FOV * 0.5f);
	float w = h / aspectRatio;
	float a = fpd / (npd - fpd);
	float b = npd * a;

	return Matrix4x4(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0
	);
}

Matrix4x4 Matrix4x4::CreateOrthographicProjection(const Point &screenSize, float npd, float fpd)
{
	float w = 2.0f / screenSize.X;
	float h = 2.0f / screenSize.Y;
	float a = 1.0f / (fpd - npd);
	float b = -a * npd;

	return Matrix4x4(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, a, 0,
		0, 0, b, 1
	);
}

Matrix4x4 Matrix4x4::CreateSphericalBillboard(const Vector3 &objectPos,const Vector3 &cameraPos,const Vector3 &cameraUp,const Vector3 &cameraForward)
{
	Matrix4x4 r;

	Vector3 vector;

	vector.X = objectPos.X - cameraPos.X;
	vector.Y = objectPos.Y - cameraPos.Y;
	vector.Z = objectPos.Z - cameraPos.Z;

	float num = vector.LengthSquared();
	if (num < 0.0001f)
	{
		vector = cameraForward;
	}
	else vector *= 1.f / sqrtf(num);

	Vector3 vector3 = Vector3::Cross(cameraUp, vector).Normalize();
	Vector3 vector2 = Vector3::Cross(vector, vector3);
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

Matrix4x4 Matrix4x4::CreateCylindricalBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUp, const Vector3& cameraForward, const Vector3& axis, std::optional<Vector3> objectForward)
{
	Matrix4x4 result;

	float num;
	Vector3 vector;
	Vector3 vector2;
	Vector3 vector3;
	vector2.X = objectPos.X - cameraPos.X;
	vector2.Y = objectPos.Y - cameraPos.Y;
	vector2.Z = objectPos.Z - cameraPos.Z;
	float num2 = vector2.LengthSquared();
	if (num2 < 0.0001f)
	{
		vector2 = cameraForward;
	}
	else
	{
		vector2 /= sqrtf(num2);
	}
	Vector3 vector4 = axis;
	num = Vector3::Dot(axis, vector2);

	if (fabs(num) > 0.9982547f)
	{
		if (objectForward.has_value())
		{
			vector = objectForward.value();
			num = axis.Dot(vector);

			if (fabs(num) > 0.9982547f)
			{
				num = ((axis.X * Vector3::Forward().X) + (axis.Y * Vector3::Forward().Y)) + (axis.Z * Vector3::Forward().Z);
				vector = (fabs(num) > 0.9982547f) ? Vector3::Right() : Vector3::Forward();
			}
		}
		else
		{
			num = ((axis.X * Vector3::Forward().X) + (axis.Y * Vector3::Forward().Y)) + (axis.Z * Vector3::Forward().Z);
			vector = (fabs(num) > 0.9982547f) ? Vector3::Right() : Vector3::Forward();
		}
		vector3 = Vector3::Cross(axis, vector);
		vector3.Normalize();

		vector = Vector3::Cross(vector3, axis);
		vector.Normalize();
	}
	else
	{
		vector3 = Vector3::Cross(axis, vector2);
		vector3.Normalize();

		vector = Vector3::Cross(vector3, vector4);
		vector.Normalize();
	}
	result.M11 = vector3.X;
	result.M12 = vector3.Y;
	result.M13 = vector3.Z;
	result.M14 = 0;
	result.M21 = vector4.X;
	result.M22 = vector4.Y;
	result.M23 = vector4.Z;
	result.M24 = 0;
	result.M31 = vector.X;
	result.M32 = vector.Y;
	result.M33 = vector.Z;
	result.M34 = 0;
	result.M41 = objectPos.X;
	result.M42 = objectPos.Y;
	result.M43 = objectPos.Z;
	result.M44 = 1;

	return result;
}

Matrix4x4 Matrix4x4::Hadamard(const Matrix4x4& a, const Matrix4x4& b)
{
	Matrix4x4 r;
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

Matrix4x4& Matrix4x4::Hadamard(const Matrix4x4& m)
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

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &m) const noexcept
{
	return Matrix4x4(
		M11 + m.M11, M12 + m.M12, M13 + m.M13, M14 + m.M14,	
		M21 + m.M21, M22 + m.M22, M23 + m.M23, M24 + m.M24,	
		M31 + m.M31, M32 + m.M32, M33 + m.M33, M34 + m.M34,	
		M41 + m.M41, M42 + m.M42, M43 + m.M43, M44 + m.M44	
	);
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4 &m) noexcept
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

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &m) const noexcept
{
	return Matrix4x4(
		M11 - m.M11, M12 - m.M12, M13 - m.M13, M14 - m.M14,
		M21 - m.M21, M22 - m.M22, M23 - m.M23, M24 - m.M24,
		M31 - m.M31, M32 - m.M32, M33 - m.M33, M34 - m.M34,
		M41 - m.M41, M42 - m.M42, M43 - m.M43, M44 - m.M44
	);
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4 &m) noexcept
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

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m) const noexcept
{
	Matrix4x4 r;
	r.M11 = M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41;
	r.M12 = M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42;
	r.M13 = M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43;
	r.M14 = M11 * m.M14 + M12 * m.M24 + M13 * m.M34 + M14 * m.M44;

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

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& m) noexcept
{
	Matrix4x4 copy(*this);
	
	this->M11 = copy.M11 * m.M11 + copy.M12 * m.M21 + copy.M13 * m.M31 + copy.M14 * m.M41;
	this->M12 = copy.M11 * m.M12 + copy.M12 * m.M22 + copy.M13 * m.M32 + copy.M14 * m.M42;
	this->M13 = copy.M11 * m.M13 + copy.M12 * m.M23 + copy.M13 * m.M33 + copy.M14 * m.M43;
	this->M14 = copy.M11 * m.M14 + copy.M12 * m.M24 + copy.M13 * m.M34 + copy.M14 * m.M44;

	this->M21 = copy.M21 * m.M11 + copy.M22 * m.M21 + copy.M23 * m.M31 + copy.M24 * m.M41;
	this->M22 = copy.M21 * m.M12 + copy.M22 * m.M22 + copy.M23 * m.M32 + copy.M24 * m.M42;
	this->M23 = copy.M21 * m.M13 + copy.M22 * m.M23 + copy.M23 * m.M33 + copy.M24 * m.M43;
	this->M24 = copy.M21 * m.M14 + copy.M22 * m.M24 + copy.M23 * m.M34 + copy.M24 * m.M44;

	this->M31 = copy.M31 * m.M11 + copy.M32 * m.M21 + copy.M33 * m.M31 + copy.M34 * m.M41;
	this->M32 = copy.M31 * m.M12 + copy.M32 * m.M22 + copy.M33 * m.M32 + copy.M34 * m.M42;
	this->M33 = copy.M31 * m.M13 + copy.M32 * m.M23 + copy.M33 * m.M33 + copy.M34 * m.M43;
	this->M34 = copy.M31 * m.M14 + copy.M32 * m.M24 + copy.M33 * m.M34 + copy.M34 * m.M44;

	this->M41 = copy.M41 * m.M11 + copy.M42 * m.M21 + copy.M43 * m.M31 + copy.M44 * m.M41;
	this->M42 = copy.M41 * m.M12 + copy.M42 * m.M22 + copy.M43 * m.M32 + copy.M44 * m.M42;
	this->M43 = copy.M41 * m.M13 + copy.M42 * m.M23 + copy.M43 * m.M33 + copy.M44 * m.M43;
	this->M44 = copy.M41 * m.M14 + copy.M42 * m.M24 + copy.M43 * m.M34 + copy.M44 * m.M44;
	return *this;
}

Matrix4x4 Matrix4x4::operator*(float scalar) const noexcept
{
	Matrix4x4 m(*this);
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

Matrix4x4& Matrix4x4::operator*=(float scalar) noexcept
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

Matrix4x4& Matrix4x4::Transpose()
{
	const Matrix4x4 copy = *this;
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

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& m)
{
	Matrix4x4 r;

	r.M11 = m.M11;
	r.M22 = m.M22;
	r.M33 = m.M33;
	r.M44 = m.M44;

	r.M12 = m.M21;
	r.M13 = m.M31;
	r.M14 = m.M41;

	r.M21 = m.M12;
	r.M23 = m.M32;
	r.M24 = m.M42;

	r.M31 = m.M13;
	r.M32 = m.M23;
	r.M34 = m.M43;

	r.M41 = m.M14;
	r.M42 = m.M24;
	r.M43 = m.M34;

	return r;
}

Matrix4x4& Matrix4x4::Invert()
{
	//https://github.com/MonoGame/MonoGame/blob/develop/MonoGame.Framework/Matrix.cs

	float num1 = M11;
	float num2 = M12;
	float num3 = M13;
	float num4 = M14;
	float num5 = M21;
	float num6 = M22;
	float num7 = M23;
	float num8 = M24;
	float num9 = M31;
	float num10 = M32;
	float num11 = M33;
	float num12 = M34;
	float num13 = M41;
	float num14 = M42;
	float num15 = M43;
	float num16 = M44;
	float num17 = (float)((double)num11 * (double)num16 - (double)num12 * (double)num15);
	float num18 = (float)((double)num10 * (double)num16 - (double)num12 * (double)num14);
	float num19 = (float)((double)num10 * (double)num15 - (double)num11 * (double)num14);
	float num20 = (float)((double)num9 * (double)num16 - (double)num12 * (double)num13);
	float num21 = (float)((double)num9 * (double)num15 - (double)num11 * (double)num13);
	float num22 = (float)((double)num9 * (double)num14 - (double)num10 * (double)num13);
	float num23 = (float)((double)num6 * (double)num17 - (double)num7 * (double)num18 + (double)num8 * (double)num19);
	float num24 = (float)-((double)num5 * (double)num17 - (double)num7 * (double)num20 + (double)num8 * (double)num21);
	float num25 = (float)((double)num5 * (double)num18 - (double)num6 * (double)num20 + (double)num8 * (double)num22);
	float num26 = (float)-((double)num5 * (double)num19 - (double)num6 * (double)num21 + (double)num7 * (double)num22);
	float num27 = (float)(1.0 / ((double)num1 * (double)num23 + (double)num2 * (double)num24 + (double)num3 * (double)num25 + (double)num4 * (double)num26));

	M11 = num23 * num27;
	M21 = num24 * num27;
	M31 = num25 * num27;
	M41 = num26 * num27;
	M12 = (float)-((double)num2 * (double)num17 - (double)num3 * (double)num18 + (double)num4 * (double)num19) * num27;
	M22 = (float)((double)num1 * (double)num17 - (double)num3 * (double)num20 + (double)num4 * (double)num21) * num27;
	M32 = (float)-((double)num1 * (double)num18 - (double)num2 * (double)num20 + (double)num4 * (double)num22) * num27;
	M42 = (float)((double)num1 * (double)num19 - (double)num2 * (double)num21 + (double)num3 * (double)num22) * num27;
	float num28 = (float)((double)num7 * (double)num16 - (double)num8 * (double)num15);
	float num29 = (float)((double)num6 * (double)num16 - (double)num8 * (double)num14);
	float num30 = (float)((double)num6 * (double)num15 - (double)num7 * (double)num14);
	float num31 = (float)((double)num5 * (double)num16 - (double)num8 * (double)num13);
	float num32 = (float)((double)num5 * (double)num15 - (double)num7 * (double)num13);
	float num33 = (float)((double)num5 * (double)num14 - (double)num6 * (double)num13);
	M13 = (float)((double)num2 * (double)num28 - (double)num3 * (double)num29 + (double)num4 * (double)num30) * num27;
	M23 = (float)-((double)num1 * (double)num28 - (double)num3 * (double)num31 + (double)num4 * (double)num32) * num27;
	M33 = (float)((double)num1 * (double)num29 - (double)num2 * (double)num31 + (double)num4 * (double)num33) * num27;
	M43 = (float)-((double)num1 * (double)num30 - (double)num2 * (double)num32 + (double)num3 * (double)num33) * num27;
	float num34 = (float)((double)num7 * (double)num12 - (double)num8 * (double)num11);
	float num35 = (float)((double)num6 * (double)num12 - (double)num8 * (double)num10);
	float num36 = (float)((double)num6 * (double)num11 - (double)num7 * (double)num10);
	float num37 = (float)((double)num5 * (double)num12 - (double)num8 * (double)num9);
	float num38 = (float)((double)num5 * (double)num11 - (double)num7 * (double)num9);
	float num39 = (float)((double)num5 * (double)num10 - (double)num6 * (double)num9);
	M14 = (float)-((double)num2 * (double)num34 - (double)num3 * (double)num35 + (double)num4 * (double)num36) * num27;
	M24 = (float)((double)num1 * (double)num34 - (double)num3 * (double)num37 + (double)num4 * (double)num38) * num27;
	M34 = (float)-((double)num1 * (double)num35 - (double)num2 * (double)num37 + (double)num4 * (double)num39) * num27;
	M44 = (float)((double)num1 * (double)num36 - (double)num2 * (double)num38 + (double)num3 * (double)num39) * num27;

	return *this;
}

Matrix4x4 Matrix4x4::Invert(const Matrix4x4& m)
{
	auto r = Matrix4x4(m).Invert();
	return r;
}

float& Matrix4x4::operator[](unsigned index)
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

float Matrix4x4::Trace() const noexcept
{
	return M11 + M22 + M33 + M44;
}
 
float Matrix4x4::Determinant() const noexcept
{
	float det1 = Matrix3x3{
		M22, M23, M24,
		M32, M33, M34,
		M42, M43, M44
	}.Determinant();

	float det2 = Matrix3x3{
		M21, M23, M24,
		M31, M33, M34,
		M41, M43, M44
	}.Determinant();

	float det3 = Matrix3x3{
		M21, M22, M24,
		M31, M32, M34,
		M41, M42, M44
	}.Determinant();

	float det4 = Matrix3x3{
		M21, M22, M23,
		M31, M32, M33,
		M41, M42, M43
	}.Determinant();

	return M11 * det1 - M12 * det2 + M13 * det3 - M14 * det4;
}

Vector3 Matrix4x4::Forward() const noexcept
{
	return { -M31, -M32, -M33 };
}

Vector3 Matrix4x4::Backward() const noexcept
{
	return { M31, M32, M33 };
}

Vector3 Matrix4x4::Up() const noexcept
{
	return { M21, M22, M23 };
}

Vector3 Matrix4x4::Down() const noexcept
{
	return { -M21, -M22, -M23 };
}
Vector3 Matrix4x4::Left() const noexcept
{
	return { -M11, -M12, -M13 };
}

Vector3 Matrix4x4::Right() const noexcept
{
	return { M11, M12, M13 };
}

Vector3 Matrix4x4::Translation() const noexcept
{
	return { M41, M42, M43 };
}


Matrix4x4 Engine3DRadSpace::Math::operator*(float scalar, const Matrix4x4& m) noexcept
{
	Matrix4x4 r(m);
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

Matrix4x4 Engine3DRadSpace::Math::operator/(float f, const Matrix4x4& m)
{
	return Matrix4x4(
		f / m.M11, f / m.M12, f / m.M13, f / m.M14,
		f / m.M21, f / m.M22, f / m.M23, f / m.M24,
		f / m.M31, f / m.M32, f / m.M33, f / m.M34,
		f / m.M41, f / m.M42, f / m.M43, f / m.M44
	);
}