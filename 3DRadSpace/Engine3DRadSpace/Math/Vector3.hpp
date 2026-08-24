#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	struct Quaternion;
	struct Matrix4x4;
	struct Vector2;

	struct E3DRSP_MATH_EXPORT Vector3
	{
		float X;
		float Y;
		float Z;

		explicit constexpr Vector3(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {};

		explicit constexpr Vector3(std::initializer_list<float> lst) :
			X(lst.size() > 0 ? *(lst.begin()) : 0.0f),
			Y(lst.size() > 1 ? *(lst.begin() + 1) : 0.0f),
			Z(lst.size() > 2 ? *(lst.begin() + 2) : 0.0f)
		{
		};

		static Vector3 Zero();
		static Vector3 UnitX();
		static Vector3 UnitY();
		static Vector3 UnitZ();
		static Vector3 One();

		static Vector3 Up();
		static Vector3 Down();
		static Vector3 Forward();
		static Vector3 Backward();
		static Vector3 Left();
		static Vector3 Right();

		float Length() const;
		float LengthSquared() const;

		Vector3& Normalize();
		static Vector3 Normalize(const Vector3& v);

		Vector3& operator +=(const Vector3& v);
		Vector3 operator +(const Vector3& v) const;
		Vector3& operator -=(const Vector3& v);
		Vector3 operator -(const Vector3& v) const;

		Vector3& operator-();
		Vector3 operator-() const;

		Vector3& operator *=(float s);
		Vector3 operator*(float s) const;

		Vector3& operator /=(float s);
		Vector3 operator /(float s) const;

		Vector3& Cross(const Vector3& v);
		static Vector3 Cross(const Vector3& v1, const Vector3& v2);

		float Dot(const Vector3& v) const;
		static float Dot(const Vector3& a, const Vector3& b);

		Vector3& Transform(const Quaternion& q);
		Vector3& Transform(const Matrix4x4& m);

		static Vector3 Transform(const Vector3& v, const Quaternion& q);
		static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

		//Element-wise product.
		Vector3& Hadamard(const Vector3& v);
		//Element wise product
		static Vector3 Hadamard(const Vector3& a, const Vector3& b);

		Vector2 XX() const noexcept;
		Vector2 XY() const noexcept;
		Vector2 XZ() const noexcept;
		Vector2 YX() const noexcept;
		Vector2 YY() const noexcept;
		Vector2 YZ() const noexcept;
		Vector2 ZX() const noexcept;
		Vector2 ZY() const noexcept;
		Vector2 ZZ() const noexcept;

		auto operator <=>(const Vector3& v) const = default;
	};

	Vector3 E3DRSP_MATH_EXPORT operator *(float s, const Vector3& v);
	Vector3 E3DRSP_MATH_EXPORT operator /(float s, const Vector3& v);
}
