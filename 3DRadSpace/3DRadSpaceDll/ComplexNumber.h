#pragma once
#include "Globals.h"

namespace Engine3DRadSpace
{
	struct ComplexNumber
	{
		float A, B;

		ComplexNumber() :A(0), B(0) {};
		ComplexNumber(float theta) : A(cos(theta)), B(sin(theta)) {};
		ComplexNumber(float a, float b) : A(a), B(b) {};

		float Argument() const;
		static float Argument(const ComplexNumber& z);
		float Lenght() const;
		static float Lenght(const ComplexNumber& z);

		ComplexNumber operator +=(const ComplexNumber& z);
		ComplexNumber operator -=(const ComplexNumber& z);
		ComplexNumber operator -();

		ComplexNumber operator /=(const ComplexNumber& z);
		ComplexNumber operator *=(const ComplexNumber& z);
	};

	ComplexNumber operator +(const ComplexNumber& a, const ComplexNumber& b);
	ComplexNumber operator -(const ComplexNumber& a, const ComplexNumber& b);
	ComplexNumber operator *(const ComplexNumber& a, const ComplexNumber& b);
	ComplexNumber operator /(const ComplexNumber& a, const ComplexNumber& b);
}
