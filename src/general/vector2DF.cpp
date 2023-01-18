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

Vector2DF Vector2DF::GetRotated(float r)
{
    auto c = cos(r);
    auto s = sin(r);

    return Vector2DF(c * X - s * Y, s * X + c * Y);
}

float Vector2DF::Length()
{
    return sqrt(this->X * this->X + this->Y * this->Y);
}

float Vector2DF::Distance(Vector2DF v2)
{
    return sqrt((this->X - v2.X) * (this->X - v2.X) + (this->Y - v2.Y) * (this->Y - v2.Y));
}

float Vector2DF::LengthSquared()
{
    return this->X * this->X + this->Y * this->Y;
}

float Vector2DF::DistanceSquared(Vector2DF v2)
{
    return (this->X - v2.X) * (this->X - v2.X) + (this->Y - v2.Y) * (this->Y - v2.Y);
}
