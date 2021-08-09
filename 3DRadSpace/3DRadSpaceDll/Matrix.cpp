#include "Matrix.h"

Matrix Matrix::CreateScale(float scale)
{
    Matrix m;
    m.M11 = scale;
    m.M22 = scale;
    m.M33 = scale;
    m.M44 = 1;
    return m;
}

Matrix Matrix::CreateScale(const Vector3& v)
{
    Matrix m;
    m.M11 = v.x;
    m.M22 = v.y;
    m.M33 = v.z;
    m.M44 = 1;
    return m;
}
