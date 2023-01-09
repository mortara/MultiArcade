#include "vector.h"

VectorF::VectorF(float x, floaty)
{
    X = x;
    Y = y;
}

void VectorF::Rotate(float radians)
{
   
    float nx = cosf(radians) * X - sinf(radians) * Y;
    float ny = sinf(radians) * X - cosf(radians) * Y;

    X = nx;
    Y = ny;
}