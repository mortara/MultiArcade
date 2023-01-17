#include <Arduino.h>

#ifndef VECTOR2DF_H
#define VECTOR2DF_H

class Vector2DF
{
    public:
        float X;
        float Y;

        Vector2DF();
        Vector2DF(float x, float y);

        void Rotate(float rads);
        Vector2DF GetRotated(float rads);

        float Distance(Vector2DF v2);

        friend bool operator== (const Vector2DF& c1, const Vector2DF& c2)
        {
            return (c1.X == c2.X && c1.Y == c2.Y);
        }

        friend bool operator!= (const Vector2DF& c1, const Vector2DF& c2)
        {
            return (c1.X != c2.X || c1.Y != c2.Y);
        }

        Vector2DF operator + (Vector2DF const &obj)
        {
            return Vector2DF(X + obj.X, Y + obj.Y);  
        }

        Vector2DF operator - (Vector2DF const &obj)
        {
            return Vector2DF(X - obj.X, Y - obj.Y);          
        }

        Vector2DF operator * (Vector2DF const &obj)
        {
            return Vector2DF(X * obj.X, Y * obj.Y);
        }

        Vector2DF operator * (double f)
        {
            return Vector2DF(X * f, Y * f);
        }
};



#endif