#include "ComplexNumber.h"

float Engine3DRadSpace::ComplexNumber::Argument() const
{
    return atan2(B, A);
}

float Engine3DRadSpace::ComplexNumber::Argument(const ComplexNumber& z)
{
    return atan2(z.B, z.A);
}

float Engine3DRadSpace::ComplexNumber::Lenght() const
{
    return (float)sqrt(pow(this->A, 2) + pow(this->B, 2));
}

float Engine3DRadSpace::ComplexNumber::Lenght(const ComplexNumber& z)
{
    return (float)sqrt(pow(z.A, 2) + pow(z.B, 2));
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::ComplexNumber::operator+=(const ComplexNumber& z)
{
    return ComplexNumber(this->A + z.A , this->B + z.B);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::ComplexNumber::operator-=(const ComplexNumber& z)
{
    return ComplexNumber(this->A - z.A, this->B - z.B);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::ComplexNumber::operator-()
{
    return ComplexNumber(-this->A,-this->B);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::ComplexNumber::operator/=(const ComplexNumber& z)
{
    return ComplexNumber(
        (this->A * z.A + this->B * z.B) / ((float)pow(z.A, 2) + (float)pow(z.B, 2)),
        (this->B * z.A - this->A * z.B) / ((float)pow(z.A, 2) + (float)pow(z.B, 2)));
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::ComplexNumber::operator*=(const ComplexNumber& z)
{
    return ComplexNumber(this->A * z.A - this->B * z.B, this->A * z.B + this->B * z.A);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::operator+(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(a.A + b.A, a.B + b.B);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::operator-(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(a.A - b.A, a.B - b.B);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::operator*(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(a.A * b.A - a.B * b.B, a.A * b.B + a.B * b.A);
}

Engine3DRadSpace::ComplexNumber Engine3DRadSpace::operator/(const ComplexNumber& a, const ComplexNumber& b)
{
    return ComplexNumber(
        (a.A * b.A + a.B * b.B) / ((float)pow(b.A, 2) + (float)pow(b.B, 2)),
        (a.B * b.A - a.A * b.B) / ((float)pow(b.A, 2) + (float)pow(b.B, 2)));
}
