#include <Arduino.h>
#include "vector2DF.hpp"

Vector2DF::Vector2DF()
{
    X = 0;
    Y = 0;
}

Vector2DF::Vector2DF(float x, float y)
{
    X = x;
    Y = y;
}

void Vector2DF::Rotate(float radians)
{
    auto c = cos(radians);
    auto s = sin(radians);

    float nx = c * X - s * Y;
    float ny = s * X + c * Y;

    X = nx;
    Y = ny;
}

Vector2DF Vector2DF::GetRotated(float r)
{
    auto c = cos(r);
    auto s = sin(r);

    float nx = c * X - s * Y;
    float ny = s * X + c * Y;

    return Vector2DF(nx,ny);
}

float Vector2DF::Distance(Vector2DF v2)
{
    float d = sqrt((this->X - v2.X) * (this->X - v2.X) + (this->Y - v2.Y) * (this->Y - v2.Y));
    return d;
}

