#include "ComplexNumber.h"

float ComplexNumber::Argument() const
{
    return atan2(B, A);
}

float ComplexNumber::Argument(const ComplexNumber& z)
{
    return atan2(z.B, z.A);
}

float ComplexNumber::Lenght() const
{
    return (float)sqrt(pow(this->A, 2) + pow(this->B, 2));
}

float ComplexNumber::Lenght(const ComplexNumber& z)
{
    return (float)sqrt(pow(z.A, 2) + pow(z.B, 2));
}

ComplexNumber ComplexNumber::operator+=(const ComplexNumber& z)
{
    return ComplexNumber(this->A + z.A , this->B + z.B);
}

ComplexNumber ComplexNumber::operator-=(const ComplexNumber& z)
{
    return ComplexNumber(this->A - z.A, this->B - z.B);
}

ComplexNumber ComplexNumber::operator-()
{
    return ComplexNumber(-this->A,-this->B);
}

ComplexNumber ComplexNumber::operator/=(const ComplexNumber& z)
{
    return ComplexNumber(
        (this->A * z.A + this->B * z.B) / ((float)pow(z.A, 2) + (float)pow(z.B, 2)),
        (this->B * z.A - this->A * z.B) / ((float)pow(z.A, 2) + (float)pow(z.B, 2)));
}

ComplexNumber ComplexNumber::operator*=(const ComplexNumber& z)
{
    return ComplexNumber(this->A * z.A - this->B * z.B, this->A * z.B + this->B * z.A);
}

ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(a.A + b.A, a.B + b.B);
}

ComplexNumber operator-(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(a.A - b.A, a.B - b.B);
}

ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(a.A * b.A - a.B * b.B, a.A * b.B + a.B * b.A);
}

ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(
        (a.A * b.A + a.B * b.B) / ((float)pow(b.A, 2) + (float)pow(b.B, 2)),
        (a.B * b.A - a.A * b.B) / ((float)pow(b.A, 2) + (float)pow(b.B, 2)));
}
