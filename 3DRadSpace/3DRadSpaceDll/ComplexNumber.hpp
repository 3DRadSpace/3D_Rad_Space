#pragma once
#include "Globals.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a complex number. A number of the form a+bi where a and b are real numbers and where i is the imaginary unit number with the property that i*i = -1.
	/// </summary>
	struct ComplexNumber
	{
		/// <summary>
		/// The real part of the complex number.
		/// </summary>
		float A;
		/// <summary>
		/// The imaginary part of the complex number.
		/// </summary>
		float B;

		/// <summary>
		/// Default constructor. Represents a null value i.e 0.
		/// </summary>
		ComplexNumber() :A(0), B(0) {};
		/// <summary>
		/// Constructs a unit imaginary number from the specified angle theta.
		/// </summary>
		/// <param name="theta">angle in radians</param>
		ComplexNumber(float theta) : A(cos(theta)), B(sin(theta)) {};
		/// <summary>
		/// Constrcuts a imaginary number from the two specified real numbers.
		/// </summary>
		/// <param name="a">The real part</param>
		/// <param name="b">The imaginary part</param>
		ComplexNumber(float a, float b) : A(a), B(b) {};

		/// <summary>
		/// Returns the angle defined by the complex number.
		/// </summary>
		/// <returns></returns>
		float Argument() const;
		/// <summary>
		/// Returns the angle defined by the given complex number.
		/// </summary>
		/// <param name="z">The complex number where the angle is going to be returned</param>
		/// <returns></returns>
		static float Argument(const ComplexNumber& z);
		/// <summary>
		/// Returns the lenght of the vector represented by the complex number.
		/// </summary>
		/// <returns></returns>
		float Lenght() const;
		/// <summary>
		/// Returns the lenght of the vector represented by the given complex number.
		/// </summary>
		/// <param name="z">Complex number</param>
		/// <returns></returns>
		static float Lenght(const ComplexNumber& z);

		/// <summary>
		/// Sums two complex numbers
		/// </summary>
		/// <param name="z">complex number</param>
		/// <returns></returns>
		ComplexNumber operator +=(const ComplexNumber& z);
		/// <summary>
		/// Sums two complex numbers except z is a additive inverse.
		/// </summary>
		/// <param name="z">complex number</param>
		/// <returns></returns>
		ComplexNumber operator -=(const ComplexNumber& z);
		/// <summary>
		/// Negates a complex number.
		/// </summary>
		/// <returns></returns>
		ComplexNumber operator -();

		/// <summary>
		/// Divides a complex numner.
		/// </summary>
		/// <param name="z">complex number</param>
		/// <returns></returns>
		ComplexNumber operator /=(const ComplexNumber& z);
		/// <summary>
		/// Multiplies a complex number.
		/// </summary>
		/// <param name="z"></param>
		/// <returns></returns>
		ComplexNumber operator *=(const ComplexNumber& z);
	};

	/// <summary>
	/// Sums two complex numbers.
	/// </summary>
	/// <param name="a">complex number</param>
	/// <param name="b">complex number</param>
	/// <returns></returns>
	ComplexNumber operator +(const ComplexNumber& a, const ComplexNumber& b);
	/// <summary>
	/// Sums complex number a with the additive inverse b.
	/// </summary>
	/// <param name="a">complex number</param>
	/// <param name="b">complex number</param>
	/// <returns></returns>
	ComplexNumber operator -(const ComplexNumber& a, const ComplexNumber& b);
	/// <summary>
	/// Multiplies two complex numbers.
	/// </summary>
	/// <param name="a">complex number</param>
	/// <param name="b">complex number</param>
	/// <returns></returns>
	ComplexNumber operator *(const ComplexNumber& a, const ComplexNumber& b);
	/// <summary>
	/// Divides two complex numbers.
	/// </summary>
	/// <param name="a">complex number</param>
	/// <param name="b">complex number</param>
	/// <returns></returns>
	ComplexNumber operator /(const ComplexNumber& a, const ComplexNumber& b);
}
