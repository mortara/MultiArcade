#include "vector.h"

VectorF::VectorF()
{
    X = 0;
    Y = 0;
}

VectorF::VectorF(float x, float y)
{
    X = x;
    Y = y;
}

void VectorF::Rotate(float radians)
{
    auto c = cos(radians);
    auto s = sin(radians);

    float nx = c * X - s * Y;
    float ny = s * X + c * Y;

    X = nx;
    Y = ny;
}

VectorF VectorF::GetRotated(float r)
{
    auto c = cos(r);
    auto s = sin(r);

    float nx = c * X - s * Y;
    float ny = s * X + c * Y;

    return VectorF(nx,ny);
}

float VectorF::Distance(VectorF v2)
{
    float d = sqrt((this->X - v2.X) * (this->X - v2.X) + (this->Y - v2.Y) * (this->Y - v2.Y));
    return d;
}